//
// Created by root on 06.09.19.
//

#include "S_Collidable.h"
#include "Debug.h"
#include "C_EllipseCollider.h"

S_Collidable::S_Collidable() {
    //preserve this, as it could prove useful
    stepping = false;
    listener = std::make_shared<Box2DContactListener>();

    BitMask defaultCollisions;
    defaultCollisions.SetBit((int) CollisionLayer::Default);

    collisionLayers.insert(std::make_pair(CollisionLayer::Default,defaultCollisions));

    collisionLayers.insert(std::make_pair(CollisionLayer::Tile,BitMask(0)));

    BitMask playerCollisions;

    playerCollisions.SetBit((int) CollisionLayer::Default);
    playerCollisions.SetBit((int) CollisionLayer::Tile);
    playerCollisions.SetBit((int) CollisionLayer::NPC);

    BitMask projectileCollisions;
    projectileCollisions.SetBit((int) CollisionLayer::Tile);

    collisionLayers.insert(std::make_pair(CollisionLayer::Projectile,projectileCollisions));

    collisionLayers.insert(std::make_pair(CollisionLayer::Player,playerCollisions));
    //init physics world here
    //set gravity
    Gravity = b2Vec2(0.f,0.f);
    physicsWorld = std::make_shared<b2World>(Gravity);
    physicsWorld->SetContactListener(listener.get());



}
void S_Collidable::SetDbgRenderer(sf::RenderWindow *window) {
    dbgRenderer = std::make_shared<PhysicsDebugRenderer>(window);
    if ( physicsWorld)
    {
        physicsWorld->SetDebugDraw(dbgRenderer.get());
        dbgRenderer->SetFlags(b2Draw::e_shapeBit);

    }

}


void S_Collidable::Add(std::vector<std::shared_ptr<Object>> &objects) {
    for (auto o :objects )
    {

        std::shared_ptr<C_EllipseCollider> Collider;
        if (o->getType() == ObjectType::Player)
            Collider = o->GetComponent<C_EllipseCollider>();

        auto collider = o->GetComponent<C_BoxCollider>();
        if (Collider)
        {
            b2Body* Body = addToWorld(Collider->getBodyDef().get());
            Body->CreateFixture(Collider->getFixtureDef().get());
            Collider->setAddedToWorld(true);


            Collider->setBody(Body);
            Collider->getBody()->SetUserData(collider.get());
            Collider->getBody()->SetFixedRotation(true);
            //Check for force to apply
            if (Collider->ApplyForceToBodyAtSpawn())
            {

                b2Vec2 force = collider->GetForce();
                Collider->getBody()->SetLinearDamping(0);
                Collider->getBody()->ApplyForce(force,Collider->getBody()->GetWorldCenter(),true);
            }
            //body now added to physicsworld
            EllipseCollidables.push_back(Collider);
        }
        if (collider)
        {

            b2Body* Body = addToWorld(collider->getBodyDef().get());
            Body->CreateFixture(collider->getFixtureDef().get());
            collider->setAddedToWorld(true);


            collider->setBody(Body);
            collider->getBody()->SetUserData(collider.get());
            collider->getBody()->SetFixedRotation(true);
            //Check for force to apply
            if (collider->ApplyForceToBodyAtSpawn())
            {

                b2Vec2 force = collider->GetForce();
                collider->getBody()->SetLinearDamping(0);
                collider->getBody()->ApplyForce(force,collider->getBody()->GetWorldCenter(),true);
            }
            //body now added to physicsworld

            BoxCollidables.push_back(collider);
            if (o->transform->isStatic())
            {
                //call special remove function here which removes it only from
                //the collection
                o->QueueForRemovalInCollection();
            }

        }
    }
}

void S_Collidable::ProcessRemovals() {
    //Remove physics object right after call to step!
    //make sure world is not stepping while removing!!
    //(this is called inside objectCollection, when ProcessRemovals is called)
    //inside objectCollection its not possible to determine if the world is
    //stepping, so either use a bool to check before calling, or call this
    //every world step after Step()
    //****
    //since ObjectCollection::ProcessRemovals is called every update
    //there should be no problem in calling this inside update after world stepping
    /*we need to remove the object, NOT the collider itself
     * so when removing something, the Object gets flaged as
     * QueuedForRemoval.

     * */
    auto objIterator = BoxCollidables.begin();
    while (objIterator != BoxCollidables.end())
    {
        auto obj = *objIterator;

        if(obj->owner->isQueuedForRemoval())
        {

            obj->getBody()->GetWorld()->DestroyBody(obj->getBody());
            //this is the last step
            objIterator = BoxCollidables.erase(objIterator);



        }
        else{
            ++objIterator;
        }


    }

}

void S_Collidable::Update() {

    //should split BoxCollidables in BoxCollidablesStatic and BoxCollidablesDynamic

    for (auto& obj : BoxCollidables)
    {
        //get box2D data from obj
        if( obj->getBody()->GetType() == b2_dynamicBody)
        {
            sf::Vector2f pos =Util::b2_to_sf(obj->getBody()->GetPosition().x*Util::SCALE,obj->getBody()->GetPosition().y*Util::SCALE);
            //(add check to see this pos is correct)
            // float rot = obj->owner->transform->GetRotation();
            //set object transform to new position
            obj->getBody()->SetLinearDamping(2);
            obj->getBody()->SetAngularDamping(2);
            obj->owner->transform->SetPosition(pos);
            if ( obj->owner->getType() == ObjectType::Projectile)
                obj->getBody()->SetLinearDamping(0);
        }



        //obj->owner->transform->SetRotation(float)




    }
    for (auto& obj : EllipseCollidables)
    {
        //get box2D data from obj
        if( obj->getBody()->GetType() == b2_dynamicBody)
        {
            sf::Vector2f pos =Util::b2_to_sf(obj->getBody()->GetPosition().x*Util::SCALE,obj->getBody()->GetPosition().y*Util::SCALE);
            //(add check to see this pos is correct)
            // float rot = obj->owner->transform->GetRotation();
            //set object transform to new position
            obj->getBody()->SetLinearDamping(2);
            obj->getBody()->SetAngularDamping(2);
            obj->owner->transform->SetPosition(pos);
            if ( obj->owner->getType() == ObjectType::Projectile)
                obj->getBody()->SetLinearDamping(0);
        }



        //obj->owner->transform->SetRotation(float)




    }

    stepping = true;
    physicsWorld->Step(1.0f/30.f,8,3);
    stepping = false;
    //physicsWorld->DrawDebugData();
    //remove objects here
    ProcessRemovals();
}

b2Body *S_Collidable::addToWorld(b2BodyDef *bodyDef) {
    b2Body* rtnBody = physicsWorld->CreateBody(bodyDef);

    return rtnBody;
}

bool S_Collidable::isStepping() {
    return stepping;
}

RayCastCallback S_Collidable::RayCastb2World(b2Vec2 pos1, b2Vec2  pos2) {
    RayCastCallback callback;
    physicsWorld->RayCast(&callback, pos1,pos2 );
    return callback;
}










