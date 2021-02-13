//
// Created by root on 03.05.20.
//

#include "Box2DContactListener.h"
#include "C_EllipseCollider.h"

void Box2DContactListener::BeginContact(b2Contact *contact) {
    //flag the object for removal here
    //need to check which object is the arrow
    bool BodyAIsArrow = false;
    bool BodyAIsPlayer = false;
    bool BodyBisArrow = false;
    bool BodyBIsPlayer = false;
    void* userdataA = contact->GetFixtureA()->GetBody()->GetUserData();
    C_BoxCollider* colliderABox = static_cast<C_BoxCollider *>(userdataA);
    C_EllipseCollider* colliderAEllipse = static_cast<C_EllipseCollider*>(userdataA);
    if (colliderABox)
    {
        if (colliderABox->owner->getType() == ObjectType::Projectile)
            BodyAIsArrow = true;
    }
    if(colliderAEllipse)
    {
        BodyAIsPlayer = true;
    }

    void *userdataB = contact->GetFixtureB()->GetBody()->GetUserData();
    C_BoxCollider *colliderBBox = static_cast<C_BoxCollider *>(userdataB);
    C_EllipseCollider *colliderBEllipse = static_cast<C_EllipseCollider *>(userdataB);

    if(colliderBBox)
    {
        if(colliderBBox->owner->getType() == ObjectType::Projectile)
            BodyBisArrow = true;
    }
    if(colliderBEllipse)
    {
        BodyBIsPlayer = true;
    }
    if ( BodyAIsArrow && BodyBIsPlayer)
        return;
    if ( BodyBIsPlayer && BodyAIsArrow)
        return;


    if (BodyBisArrow && !BodyAIsPlayer)
        colliderBBox->owner->QueueForRemoval();
    if (BodyAIsArrow && !BodyBIsPlayer)
        colliderABox->owner->QueueForRemoval();





}
void Box2DContactListener::EndContact(b2Contact *contact) {
    b2ContactListener::EndContact(contact);
}
