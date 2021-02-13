//
// Created by Nico on 23.09.2020.
//

#include "C_Interactable.h"

C_Interactable::C_Interactable(Object *owner) : Component(owner) {
 playerIsNear = false;
}
//maybe the raycast shouldnt be called  from  the interactable
//-->  multiple  interactables would trigger  multiple raycasts
//should be called from  the playerObject  if F (interaction button)  is getting  pressed
//so maybe a Component  for the playerobject, C_RayCaster

void C_Interactable::Update(float deltaTime) {

    //check if player is near
    //if near check if F is getting pressed
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



   // std::cout << "InterActablePos:" << InterActablePos.x << "::" <<InterActablePos.y << std::endl;
    /*
    float distance = Util::distance(PlayerPos,InterActablePos);
    playerIsNear = distance < 40;
    if(playerIsNear && owner->context->input->IsKeyDown(Input::Key::F) )
    {
        auto chatbox = tgui::ChatBox::create();
        chatbox->setSize(300, 100);
        chatbox->setTextSize(18);
        chatbox->setPosition(420, 310);
        chatbox->setLinesStartFromTop();
        chatbox->addLine(" Hey, this is TGUI!", tgui::Color::Green);
        chatbox->setFocused(true);
        tgui::ChatBoxRenderer *chatboxRenderer  =  chatbox->getRenderer();
        owner->context->gui->add(chatbox, "DialogBox");

    } else if( owner->context->input->IsKeyDown(Input::Key::F)          )
    {
        auto  box = owner->context->gui->get("DialogBox");
        owner->context->gui->remove(box);

        std::cout << "Close Dialog Box" << distance << std::endl;
    }*/


    //std::cout << "DistanceToInteractable:" << distance << std::endl;

}

void C_Interactable::LateUpdate(float deltaTime) {
    Component::LateUpdate(deltaTime);
}

void C_Interactable::Awake() {
    Component::Awake();
}

void C_Interactable::Start() {
    Component::Start();
}
