//
// Created by root on 31.08.19.
//

#include "C_KeyboardMovement.h"
#include "Object.h"

C_KeyboardMovement::C_KeyboardMovement(Object *owner) :
                                        Component(owner),moveSpeed(100),isLocked(false)
                                        {

                                        }


void C_KeyboardMovement::SetMovementSpeed(float moveSpeed)
{
    this->moveSpeed = moveSpeed;
}
void C_KeyboardMovement::Update(float deltaTime) {
    if (isLocked)
        return;

    //return;
    b2Body *body;
    if (owner->getType() == ObjectType::Player)
        body = owner->GetComponent<C_EllipseCollider>()->getBody();
    else
         body = owner->GetComponent<C_BoxCollider>()->getBody();
    b2Vec2 vel = body->GetLinearVelocity();
    float desiredVel = 0;



    if(animation->GetAnimationState() == AnimationState::Projectile)
    {
        body->SetLinearVelocity(b2Vec2(0,0));
        return;
        /*desiredVel = 0;
        float velChange = desiredVel - vel.x;
        float force = body->GetMass() * velChange / (1.f/60.0);
        body->ApplyForce(b2Vec2(force,0),body->GetWorldCenter(),true);
        return;*/
    }


    //apply force to the left
    if(owner->context->input->IsKeyPressed(Input::Key::Left))
    {
        desiredVel = -2.0;
        float velChange = desiredVel - vel.x;
        float force  = body->GetMass() * velChange;
        body->ApplyLinearImpulse(b2Vec2(force,0),body->GetWorldCenter(),true);

    }
    else if(owner->context->input->IsKeyPressed(Input::Key::Right))
    {
        desiredVel = 2.0;
        float velChange = desiredVel - vel.x;
        float force  = body->GetMass() * velChange;
        body->ApplyLinearImpulse(b2Vec2(force,0),body->GetWorldCenter(),true);

    }


    if(owner->context->input->IsKeyPressed(Input::Key::Up))
    {
        desiredVel = -2.0;
        float velChange = desiredVel - vel.y;
        float force  = body->GetMass() * velChange;
        body->ApplyLinearImpulse(b2Vec2(0,force),body->GetWorldCenter(),true);

    }
    else if(owner->context->input->IsKeyPressed(Input::Key::Down))
    {
        desiredVel = 2.0;
        float velChange = desiredVel - vel.y;
        float force  = body->GetMass() * velChange;
        body->ApplyLinearImpulse(b2Vec2(0,force),body->GetWorldCenter(),true);

    }




}

void C_KeyboardMovement::Awake() {
    velocity = owner->GetComponent<C_Velocity>();
    animation = owner->GetComponent<C_Animation>();
}

void C_KeyboardMovement::Unlock() {
    isLocked = false;
}

void C_KeyboardMovement::Lock() {
    isLocked = true;

}
