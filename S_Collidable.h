//
// Created by root on 06.09.19.
//

#ifndef INC_2DENGINE_S_COLLIDABLE_H
#define INC_2DENGINE_S_COLLIDABLE_H
#include <vector>
#include <memory>
#include <unordered_set>
#include <set>
#include "Utilities.h"
#include "Object.h"

#include "BitMask.h"
#include "ComponentPairHash.h"
#include "PhysicsDebugRenderer.h"
#include "Box2DContactListener.h"
#include "C_EllipseCollider.h"
#include "RayCastCallback.h"

//collidable system
/*
 * Instantiate physics world here
 * 1. Everytime something gets added to the collidable system we need to add it to the world
 * 2. Step forward world by fixed timestep in update
 * rework of ObjectCollection
 * rework of C_KeyboardMovement
 * --need to implement movement by a force applied to the
 * --player fixture.
 * rework of C_Direction
 * rework of C_RemoveOnCollison
 * rework of C_Velocity
 * rework of C_MovementAnimation
 * rework of C_KeyboardMovement
 * need to display and update the sprite positions in S_Collidable Update()
 * 2 types of collider, static, dynamic
 * rework of TilemapParser to add static and dynamic collider
 * creation and deletion of bodys must be after stepping
 * batch body to be removed, batch bodys to be spawned
 * (must use box2d collision filter)
 *https://www.iforce2d.net/b2dtut/collision-filtering
 * boxCollider still needs the layer, but as bitmask
 * every physics object gets a category bit (eg. "player").
 *
 *
 * Preserve old class structure
 * Get "rid" of collision handling inside BoxCollider
 * and make BoxCollider wrap a box2d body.
 * --with a pointer to bodyDef and appropriate getter-setter
b2Vec2 Gravity(0.f,9.8f);
b2World World(Gravity);

 since we need to add and remove bodies when world is not stepping
 we need a way to be sure it isnt.
 -->add a flag to C_BoxCollider which tells us if the object has been added
 then we still dont have a way to detemine whether the world is stepping just now
 -->add a flag to S_Collidable bool stepping and set it true everytime step starts
 and false if ending

*/
class S_Collidable {
public:
    std::shared_ptr<b2World> getPhysicsWorld()
    {
        return physicsWorld;
    }
    RayCastCallback RayCastb2World(b2Vec2 p1,  b2Vec2  p2);
    S_Collidable();
    void Add(std::vector<std::shared_ptr<Object>>& objects);
    void ProcessRemovals();
    void Update();
    b2Body* addToWorld(b2BodyDef *bodyDef);
    void SetDbgRenderer(sf::RenderWindow *window);
private:

    bool isStepping();
    std::shared_ptr<Box2DContactListener> listener;
    bool stepping;
    std::map<CollisionLayer ,BitMask> collisionLayers;
    std::unordered_set<std::pair<std::shared_ptr<C_BoxCollider>, std::shared_ptr<C_BoxCollider>>, ComponentPairHash> objectsColliding;
    // no map needed here anymore, change to a vector of C_BoxCollider
    std::vector<std::shared_ptr<C_BoxCollider>> BoxCollidables;
    std::vector<std::shared_ptr<C_EllipseCollider>> EllipseCollidables;

    b2Vec2 Gravity;
    std::shared_ptr<b2World> physicsWorld;
    std::shared_ptr<PhysicsDebugRenderer> dbgRenderer;



};


#endif //INC_2DENGINE_S_COLLIDABLE_H
