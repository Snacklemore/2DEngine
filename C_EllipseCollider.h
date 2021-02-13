//
// Created by root on 20.09.20.
//

#ifndef INC_2DENGINE_C_ELLIPSECOLLIDER_H
#define INC_2DENGINE_C_ELLIPSECOLLIDER_H

#include "Component.h"
#include <cmath>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>


#include <Box2D/Dynamics/b2Fixture.h>
#include "C_Collider.h"
#include "Utilities.h"

class C_EllipseCollider : public C_Collider{
public:
    C_EllipseCollider(Object* owner);
    void SetOffset(const sf::Vector2f& offset);
    void SetOffset(float x, float y);

    void ApplyForceAtSpawn(b2Vec2 force);
    void SetSize(const sf::Vector2f& size);
    void SetSize(float width, float height);

    //create a bodyDefinition
    std::shared_ptr<b2BodyDef> setBodyDef(b2Vec2 pos);
    //set BodyDef position
    void setBodyPosition(b2Vec2 vec);
    //set body type eg "dynamic", "static", "kinematic"
    void setBodyType(std::string type);
    //set body shape, eg "Box","Circle",hx,hy is size.
    void setBodyShape();
    //create bodyFixture, and set attributes
    void setFixtureDef(float density, float friction);
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
    std::shared_ptr<b2ChainShape> ChainShape;
    std::shared_ptr<b2FixtureDef> FixtureDef;
    b2Body* Body;
    float INNER_RADIUSy ;
    float OUTER_RADIUSx;
    uint32 DIVISIONS = 10;
    bool bodyAddedToWorld;
    sf::Vector2f offset;
    b2Vec2 Force;
    double m_pi = 3.14159265359;
    bool applyForceAtSpawn;

};


#endif //INC_2DENGINE_C_ELLIPSECOLLIDER_H
