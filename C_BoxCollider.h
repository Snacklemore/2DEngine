//
// Created by root on 06.09.19.
//

#ifndef INC_2DENGINE_C_BOXCOLLIDER_H
#define INC_2DENGINE_C_BOXCOLLIDER_H

#include "Component.h"
#include <math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "C_Collider.h"
#include "Utilities.h"

//let this class wrap a Box2d Rect as a collider, and a dynamic and static body
class C_BoxCollider: public C_Collider {
public:
    C_BoxCollider(Object* owner);





    void SetOffset(const sf::Vector2f& offset);
    void SetOffset(float x, float y);

    void ApplyForceAtSpawn(b2Vec2 force);
    void SetSize(const sf::Vector2f& size);
    void SetSize(float width, float height);

    ///Start building upon here(deleting deprecated content later)

    //create a bodyDefinition
    std::shared_ptr<b2BodyDef> setBodyDef(b2Vec2 pos);
    //set BodyDef position
    void setBodyPosition(b2Vec2 vec);
    //set body type eg "dynamic", "static", "kinematic"
    void setBodyType(std::string type);
    //set body shape, eg "Box","Circle",hx,hy is size.
    void setBodyShape(std::string shape,float hx, float hy);
    //create bodyFixture, and set attributes
    void setFixtureDef(float density, float friction);
    //attach fixture to body
    //(to create a fixture we need pointer to the b2Body.
    // we get that pointer by creating a Body in the world with the
    //world.CreateBody(&bodyDef) call.
    // so return the bodyDef when created to be able to add it to the world inside
    //S_Collidable
    //we set the b2Body pointer in this and can now call createFixture to
    // init the object completetly )
    std::shared_ptr<b2Body> createFixture();
    void setBody(b2Body *body);
    b2Body *getBody();
    std::shared_ptr<b2BodyDef> getBodyDef();
    std::shared_ptr<b2FixtureDef> getFixtureDef();
    bool isAdded()
    {
        return bodyAddedToWorld;
    }
    void setAddedToWorld(bool j)
    {
        bodyAddedToWorld = j;
    }
    bool ApplyForceToBodyAtSpawn();
    b2Vec2 GetForce();




private:

    //body definition
    std::shared_ptr<b2BodyDef> BodyDef;
    std::shared_ptr<b2PolygonShape> PolygonShape;
    std::shared_ptr<b2FixtureDef> FixtureDef;
    b2Body* Body;
    bool bodyAddedToWorld;
    sf::FloatRect AABB;
    sf::Vector2f offset;
    b2Vec2 Force;
    bool applyForceAtSpawn;

};


#endif //INC_2DENGINE_C_BOXCOLLIDER_H
