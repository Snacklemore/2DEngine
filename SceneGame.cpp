//
// Created by root on 29.08.19.
//

#include "SceneGame.h"
#include "Debug.h"



SceneGame::SceneGame(WorkingDirectory &workingDir,ResourceAllocator<sf::Texture>& textureAllocator,Window& window, tgui::GuiSFML *gui) :workingDir(workingDir),textureAllocator(textureAllocator),mapParser(textureAllocator,context),window(window){
    this->gui =  gui;
}

void SceneGame::OnCreate() {
    sLightSystem = std::make_shared<S_LightSystem>(window);


    context.input = &input;
    context.objects = &objects;
    context.workingDir = &workingDir;
    context.textureAllocator = &textureAllocator;
    context.window = &window;
    context.lightSytstem = sLightSystem.get();
    context.gui = gui;
    objects.getCollidableSystem()->SetDbgRenderer(window.getWindowHandle());
    CreatePlayer();
    sLightSystem->AddLight(_player);
    //UserInterface->createDialogBox(500,50,955,680);




    //CreateFriend();

    // You will need to play around with this offset until the
    // level is in a suitable position based on the current window size.
    // This works for 1920 * 1080.
    // In future we will remove this hardcoded offset when
    // we add the ability to change resolutions.
    //sf::Vector2i mapOffset(-50, 0);
    sf::Vector2i mapOffset(0, 0);
    std::vector<std::shared_ptr<Object>> levelTiles =
            mapParser.Parse(workingDir.Get() + "test.tmx", mapOffset);

    objects.Add(levelTiles);
}

void SceneGame::OnDestroy() {

}

void SceneGame::ProcessInput() {
    input.Update();
}

void SceneGame::Update(float deltaTime) {
    objects.ProcessRemovals();
    objects.ProcessNewObjects();

    objects.Update(deltaTime);
    if ( context.input->IsKeyPressed(Input::Key::Esc))
    {
       context.window->getWindowHandle()->close();
    }

    sLightSystem->update();




    Debug::HandleCameraZoom(window,input);

}

void SceneGame::Draw(Window &window) {
    objects.Draw(window);


    sLightSystem->draw();
    gui->draw();
    objects.getCollidableSystem()->getPhysicsWorld()->DrawDebugData();
    Debug::Draw(window);
}

void SceneGame::OnDeactivate() {

}

void SceneGame::OnActivate() {

}

void SceneGame::LateUpdate(float deltaTime) {
    objects.LateUpdate(deltaTime);

}

void SceneGame::AddAnimationComponent(std::shared_ptr<Object> object, const int textureID) {
    auto animation = object->AddComponent<C_Animation>();

    const unsigned int frameWidth =  64;
    const unsigned int frameHeight = 64;

    const FacingDirection directions[4] = {FacingDirection::Up, FacingDirection::Left, FacingDirection::Down, FacingDirection::Right};

    /*******************
     * Idle Animations *
     *******************/
    const bool idleAnimationLooped = false;

    unsigned int idleYFramePos = 512;

    std::unordered_map<FacingDirection, std::shared_ptr<Animation>> idleAnimations;

    for (int i = 0; i < 4; i++)
    {
        std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>();

        idleAnimation->AddFrame(textureID, 0, idleYFramePos, frameWidth, frameHeight, 0.f, idleAnimationLooped);

        idleAnimations.insert(std::make_pair(directions[i], idleAnimation));

        idleYFramePos += frameHeight;
    }

    animation->AddAnimation(AnimationState::Idle, idleAnimations);


    /**********************
     * Walking Animations *
     **********************/
    const bool walkAnimationLooped = true;
    const int walkingFrameCount = 9;
    const float delayBetweenWalkingFramesSecs = 0.1f;

    unsigned int walkingYFramePos = 512;

    std::unordered_map<FacingDirection, std::shared_ptr<Animation>> walkingAnimations;

    for (int i = 0; i < 4; i++)
    {
        std::shared_ptr<Animation> walkingAnimation = std::make_shared<Animation>();
        for (int i = 0; i < walkingFrameCount; i++)
        {
            walkingAnimation->AddFrame(textureID, i * frameWidth, walkingYFramePos, frameWidth, frameHeight, delayBetweenWalkingFramesSecs, walkAnimationLooped);
        }

        walkingAnimations.insert(std::make_pair(directions[i], walkingAnimation));

        walkingYFramePos += frameHeight;
    }

    animation->AddAnimation(AnimationState::Walk, walkingAnimations);


    /*************************
     * Projectile Animations *
     *************************/

    const bool projectileAnimationLooped = true;
    const int projectileFrameCount = 10;
    const float delayBetweenProjectileFramesSecs = 0.08f;

    std::unordered_map<FacingDirection, std::shared_ptr<Animation>> projectileAnimations;

    unsigned int projFrameYPos = 1024;

    for (int i = 0; i < 4; i++)
    {
        std::shared_ptr<Animation> projAnimation = std::make_shared<Animation>();
        for (int i = 0; i < projectileFrameCount; i++)
        {
            projAnimation->AddFrame(textureID, i * frameWidth, projFrameYPos, frameWidth, frameHeight, delayBetweenProjectileFramesSecs, projectileAnimationLooped);
        }
        projectileAnimations.insert(std::make_pair(directions[i], projAnimation));

        projFrameYPos += frameHeight;
    }

    animation->AddAnimation(AnimationState::Projectile, projectileAnimations);
}

void SceneGame::CreatePlayer() {
    std::shared_ptr<Object> player = std::make_shared<Object>(&context);
    player->setType(ObjectType::Player);
    player->transform->SetPosition(1900, 1200);

    auto sprite = player->AddComponent<C_Sprite>();
    sprite->SetDrawLayer(DrawLayer::Entities);
    sprite->SetSortOrder(4);
    std::cout <<  "SortOrder:  " << sprite->GetSortOrder() << std::endl;

    player->AddComponent<C_KeyboardMovement>();

    auto animation = player->AddComponent<C_Animation>();

    int playerTextureID = textureAllocator.Add(workingDir.Get()
                                               + "Player.png");

    AddAnimationComponent(player,playerTextureID);
    //instead C_BoxCollider we will use C_EllipseCollider
    auto collider = player->AddComponent<C_EllipseCollider>();
    collider->SetSize(0.5,1);
    collider->setBodyDef(Util::sf_to_b2(player->transform->GetPosition().x/Util::SCALE,player->transform->GetPosition().y/Util::SCALE));
    collider->setBodyType("Dynamic");
    collider->setBodyShape();

    collider->setFixtureDef(1.0,0.7);


    /*
     * collider->setBodyDef(Util::sf_to_b2(tileObject->transform->GetPosition().x/Util::SCALE,tileObject->transform->GetPosition().y/Util::SCALE));
                collider->setBodyType("Static");
                collider->setBodyShape("Box",height,width);
                collider->setFixtureDef(1.0f,0.7f);
     *
     *
     * */
    player->AddComponent<C_Camera>();
    player->AddComponent<C_ProjectileAttack>();
    player->AddComponent<C_Velocity>();
    player->AddComponent<C_MovementAnimation>();
    player->AddComponent<C_Direction>();

    objects.SetPlayer(player);
    objects.Add(player);
    _player = player;

}

void SceneGame::CreateFriend() {
    std::shared_ptr<Object> npc = std::make_shared<Object>(&context);

    npc->transform->SetPosition(160, 700);

    auto sprite = npc->AddComponent<C_Sprite>();
    sprite->SetDrawLayer(DrawLayer::Entities);

    const int textureID = textureAllocator.Add(workingDir.Get() + "Skeleton.png");

    AddAnimationComponent(npc, textureID);

    auto collider = npc->AddComponent<C_BoxCollider>();
    collider->SetSize(64 * 0.4f, 64 * 0.5f);
    collider->SetOffset(0.f, 14.f);
    collider->SetLayer(CollisionLayer::NPC);

    npc->AddComponent<C_Velocity>();
    npc->AddComponent<C_MovementAnimation>();
    npc->AddComponent<C_Direction>();

    objects.Add(npc);
}

