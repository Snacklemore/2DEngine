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
