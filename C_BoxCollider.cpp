//
// Created by root on 06.09.19.
//

#include "C_BoxCollider.h"
#include "Object.h"

C_BoxCollider::C_BoxCollider(Object *owner) : C_Collider(owner),offset(sf::Vector2f(0.f,0.f)) {
    bodyAddedToWorld = false;
    applyForceAtSpawn = false;
}













void C_BoxCollider::SetOffset(const sf::Vector2f &offset) {
    this->offset = offset;
}

void C_BoxCollider::SetOffset(float x, float y) {
    offset.x = x;
    offset.y = y;
}

void C_BoxCollider::SetSize(const sf::Vector2f &size) {
    AABB.width = size.x;
    AABB.height = size.y;

}

void C_BoxCollider::SetSize(float width, float height) {
    AABB.width = width;
    AABB.height = height;
}



std::shared_ptr<b2BodyDef> C_BoxCollider::setBodyDef(b2Vec2 pos) {


    BodyDef = std::make_shared<b2BodyDef>();
    BodyDef->position = pos;
    return  BodyDef;

}

void C_BoxCollider::setBodyPosition(b2Vec2 vec) {
    BodyDef->position = vec;
}

void C_BoxCollider::setBodyType(std::string type) {
    if(type == "Static")
    {
        BodyDef->type = b2_staticBody;
    } else if (type == "Dynamic")
    {
        BodyDef->type = b2_dynamicBody;
    }
}

void C_BoxCollider::setBodyShape(std::string shape, float hx, float hy) {
    if(shape == "Circle")
    {

    } else if (shape == "Box")
    {
        PolygonShape = std::make_shared<b2PolygonShape>();
        //32px in a sprite are 16distance units in box2d
        //so we take the x and y and divide by 2, then scale
        PolygonShape->SetAsBox((hx/2.f)/Util::SCALE,(hy/2.f)/Util::SCALE);
    }
}

void C_BoxCollider::setFixtureDef(float density, float friction) {
    FixtureDef = std::make_shared<b2FixtureDef>();
    FixtureDef->density = density;
    FixtureDef->friction = friction;
    FixtureDef->shape = PolygonShape.get();
    //b2Body* Body = world.CreateBody(&BodyDef;

}

std::shared_ptr<b2Body> C_BoxCollider::createFixture() {

}

void C_BoxCollider::setBody( b2Body *body) {
 Body = body;
}

b2Body* C_BoxCollider::getBody() {
    return Body;
}

std::shared_ptr<b2BodyDef> C_BoxCollider::getBodyDef() {
    return BodyDef;
}

std::shared_ptr<b2FixtureDef>  C_BoxCollider::getFixtureDef() {
    return FixtureDef;
}

void C_BoxCollider::ApplyForceAtSpawn(b2Vec2 force) {
    applyForceAtSpawn = true;
    Force = force;
}

bool C_BoxCollider::ApplyForceToBodyAtSpawn() {
    return  applyForceAtSpawn;
}

b2Vec2 C_BoxCollider::GetForce() {
    return Force;
}
