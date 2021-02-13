//
// Created by root on 10.09.19.
//

#include "C_ProjectileAttack.h"
#include "Object.h"
#include "C_RemoveObjectOnCollisionEnter.h"

std::unordered_map<FacingDirection, sf::IntRect,EnumClassHash> C_ProjectileAttack::textureDirectionBindings = {};
std::unordered_map<FacingDirection, sf::Vector2f, EnumClassHash> C_ProjectileAttack::offsetDirectionBindings = {};
std::unordered_map<FacingDirection, sf::Vector2f, EnumClassHash>
        C_ProjectileAttack::velocityDirectionBindings = {};

C_ProjectileAttack::C_ProjectileAttack(Object *owner) : Component(owner) ,projectileVelocity(40.f){

}

void C_ProjectileAttack::Awake() {
    animation = owner->GetComponent<C_Animation>() ;
    direction = owner->GetComponent<C_Direction>();
}

void C_ProjectileAttack::Update(float deltaTime) {
    if (owner->context->input->IsKeyDown(Input::Key::E))
    {

        animation->SetAnimationState(AnimationState::Projectile);
    }
    else if (owner->context->input->IsKeyUp(Input::Key::E))
    {
        animation->SetAnimationState(AnimationState::Idle);
    }
}



void C_ProjectileAttack::Start() {
    projectileTextureID =
            owner->context->textureAllocator->Add(owner->context->workingDir->Get()
                                    + "LPC/Weapons/arrow.png");

    textureDirectionBindings.emplace(FacingDirection::Up, sf::IntRect(0, 0, 64, 64));
    textureDirectionBindings.emplace(FacingDirection::Left, sf::IntRect(64, 0, 64, 64));
    textureDirectionBindings.emplace(FacingDirection::Down, sf::IntRect(128, 0, 64, 64));
    textureDirectionBindings.emplace(FacingDirection::Right, sf::IntRect(192, 0, 64, 64));
    offsetDirectionBindings.emplace(FacingDirection::Up,
                                    sf::Vector2f(0,-80.0));
    offsetDirectionBindings.emplace(FacingDirection::Left,
                                    sf::Vector2f(-40.f, 3.f));
    offsetDirectionBindings.emplace(FacingDirection::Down,
                                    sf::Vector2f(-3.f, -75.f));
    offsetDirectionBindings.emplace(FacingDirection::Right,
                                    sf::Vector2f(40.f, 3.f));

    velocityDirectionBindings.emplace(FacingDirection::Up,
                                      sf::Vector2f(0.f, -1.f));
    velocityDirectionBindings.emplace(FacingDirection::Left,
                                      sf::Vector2f(-1.f, 0.f));
    velocityDirectionBindings.emplace(FacingDirection::Down,
                                      sf::Vector2f(0.f, 1.f));
    velocityDirectionBindings.emplace(FacingDirection::Right,
                                      sf::Vector2f(1.f, 0.f));

    animation->AddAnimationAction(
            AnimationState::Projectile,
            FacingDirection::Up,
            9,
            std::bind(&C_ProjectileAttack::SpawnProjectile,this));

    animation->AddAnimationAction(
            AnimationState::Projectile,
            FacingDirection::Left,
            9,
            std::bind(&C_ProjectileAttack::SpawnProjectile,this));

    animation->AddAnimationAction(
            AnimationState::Projectile,
            FacingDirection::Down,
            9,
            std::bind(&C_ProjectileAttack::SpawnProjectile,this));

    animation->AddAnimationAction(
            AnimationState::Projectile,
            FacingDirection::Right,
            9,
            std::bind(&C_ProjectileAttack::SpawnProjectile,this));

}

void C_ProjectileAttack::SpawnProjectile() {
    FacingDirection faceDir = direction->Get();
    std::shared_ptr<Object> projectile = std::make_shared<Object>(owner->context);


    projectile->transform->SetPosition(owner->transform->GetPosition()+ offsetDirectionBindings.at(faceDir));

    FacingDirection currentDir = direction->Get();

    auto projSprite = projectile->AddComponent<C_Sprite>();
    projSprite->Load(projectileTextureID);
    projSprite->SetDrawLayer(DrawLayer::Entities);
    projSprite->SetSortOrder(100);
    projSprite->SetTextureRect(textureDirectionBindings.at(direction->Get()));
    auto velocity = projectile->AddComponent<C_Velocity>();
    velocity->Set(velocityDirectionBindings.at(faceDir)* projectileVelocity);

    auto collider = projectile->AddComponent<C_BoxCollider>();





    sf::Vector2f pos = sf::Vector2f(owner->transform->GetPosition()+ offsetDirectionBindings.at(faceDir));
    collider->setBodyDef(Util::sf_to_b2(pos.x/Util::SCALE,pos.y/Util::SCALE));
    collider->setBodyType("Dynamic");
    collider->setBodyShape("Box",32,32);
    collider->setFixtureDef(1.0f,0.7f);

    //this crashes cause there is no body
    //extend BoxCollider:
    // save a arbitray float value, and a flag ApplyForceOnSpawn
    // function ApplyForceOnSpawn(b2Vec2) which applies specified force
    // when object is created and body pointer is valid
    //b2Vec2 vel = collider->getBody()->GetLinearVelocity();
    float desiredVel = 10;
    if ( faceDir == FacingDirection::Up)
    {
        float velChange = desiredVel ;
        float force = -1 * (velChange / (1.f/60.0f));
        collider->ApplyForceAtSpawn(b2Vec2(0,force));
        //x-Coord = 0;
    }
    if ( faceDir == FacingDirection::Down)
    {
        //x-Coord = 0;
        float velChange = desiredVel ;
        float force =  (velChange / (1.f/60.0f));
        collider->ApplyForceAtSpawn(b2Vec2(0,force));


    }
    if ( faceDir == FacingDirection::Left)
    {
        float velChange = desiredVel ;
        float force = -1 * (velChange / (1.f/60.0f));
        collider->ApplyForceAtSpawn(b2Vec2(force,0));
        //Y-Coord = 0;
    }
    if ( faceDir == FacingDirection::Right)
    {
        float velChange = desiredVel;
        float force = ( velChange / (1.f/60.0f));
        collider->ApplyForceAtSpawn(b2Vec2(force,0));

        //Y-Coord = 0;
    }

   // projectile->AddComponent<C_RemoveObjectOnCollisionEnter>();
    projectile->setType(ObjectType::Projectile);
    owner->context->objects->Add(projectile);

}
