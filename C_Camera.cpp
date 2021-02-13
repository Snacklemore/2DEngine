//
// Created by root on 08.09.19.
//

#include "C_Camera.h"

C_Camera::C_Camera(Object *owner) : Component(owner) {

}

void C_Camera::LateUpdate(float deltaTime) {


    const sf::Vector2f& targetPos = owner->transform->GetPosition();
    //view.setCenter(targetPos.x, targetPos.y);
    sf::View view = owner->context->window->GetView();
    sf::Vector2f viewCenter = owner->context->window->GetView().getCenter();
    sf::Vector2f offset = targetPos - viewCenter;
    view.move(offset);
   // owner->context->window->getWindowHandle()->setView(view);


    owner->context->window->SetView(view);

}

