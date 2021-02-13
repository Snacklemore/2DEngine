//
// Created by root on 10.09.19.
//

#include "C_Velocity.h"


C_Velocity::C_Velocity(Object *owner) : Component(owner),maxVelocity(500.f,500.f),physicsWorld(owner->context->objects->getCollidableSystem()->getPhysicsWorld()) {
}

void C_Velocity::Update(float deltaTime) {

}

void C_Velocity::Set(const sf::Vector2f &vel) {
    velocity = vel;
    //ClampVelocity();
}

void C_Velocity::Set(float x, float y) {
    velocity.x = x;
    velocity.y = y;

    //ClampVelocity();
}

 sf::Vector2f C_Velocity::Get()  {

     auto box = owner->GetComponent<C_BoxCollider>();
     auto ellipse = owner->GetComponent<C_EllipseCollider>();
     b2Vec2 b2Vec;
     if (box)
         b2Vec = box->getBody()->GetLinearVelocity();
     if(ellipse)
         b2Vec = ellipse->getBody()->GetLinearVelocity();

     return  Util::b2_to_sf(b2Vec);
}

void C_Velocity::ClampVelocity() {
    if (fabs(velocity.x) > maxVelocity.x)
    {
        if (velocity.x > 0.f)
        {
            velocity.x = maxVelocity.x;
        } else
        {
            velocity.x = -maxVelocity.x;
        }
    }
    if (fabs(velocity.y) > maxVelocity.y)
    {
        if (velocity.y > 0.f)
        {
            velocity.y = maxVelocity.y;
        }
        else
        {
            velocity.y = -maxVelocity.y;
        }
    }
}
