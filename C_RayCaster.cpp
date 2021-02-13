//
// Created by Nico on 13.02.2021.
//

#include "C_RayCaster.h"

C_RayCaster::C_RayCaster(Object *owner) : Component(owner) {


}

void C_RayCaster::Update(float deltaTime) {
    sf::Vector2f PlayerPos = owner->context->objects->GetPlayer()->transform->GetPosition();
    //  std::cout << "PlayerPos:" << PlayerPos.x << "::" <<PlayerPos.y << std::endl;
    sf::Vector2f InterActablePos = owner->transform->GetPosition();
    auto animation  =  owner->context->objects->GetPlayer()->GetComponent<C_Animation>();
    if(owner->context->input->IsKeyDown(Input::Key::F))
    {
        if  (animation->GetCurrentDiection()  ==  FacingDirection::Up)
        {
            sf::Vector2f target  = PlayerPos;
            target.y  = target.y  -50.f;
            Debug::DrawLine(PlayerPos,target);
            b2Vec2 pp =  Util::sf_to_b2(target);
            //Ray should be cast in orientation of player
            std::cout << "RayCasting!"  << std::endl;

            RayCastCallback cb = owner->context->objects->getCollidableSystem()->RayCastb2World(Util::sf_to_b2(PlayerPos,30.f),Util::sf_to_b2(target, 30.f) );
            if (cb.m_fixture)
                std::cout << "target hit"  << std::endl;


        }
        if  (animation->GetCurrentDiection()  ==  FacingDirection::Down)
        {

        }
        if  (animation->GetCurrentDiection()  ==  FacingDirection::Left)
        {

        }
        if  (animation->GetCurrentDiection()  ==  FacingDirection::Right)
        {

        }

    }
}

void C_RayCaster::LateUpdate(float deltaTime) {
    Component::LateUpdate(deltaTime);
}

void C_RayCaster::Awake() {
    Component::Awake();
}

void C_RayCaster::Start() {
    Component::Start();
}
