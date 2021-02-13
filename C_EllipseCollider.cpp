//
// Created by root on 20.09.20.
//

#include "C_EllipseCollider.h"

C_EllipseCollider::C_EllipseCollider(Object *owner) : C_Collider(owner),offset(sf::Vector2f(0.f,0.f)) {
    bodyAddedToWorld = false;
    applyForceAtSpawn = false;
}

void C_EllipseCollider::SetOffset(const sf::Vector2f &offset) {
    this->offset = offset;
}

void C_EllipseCollider::SetOffset(float x, float y) {
    offset.x = x;
    offset.y = y;

}

void C_EllipseCollider::ApplyForceAtSpawn(b2Vec2 force) {

}

void C_EllipseCollider::SetSize(const sf::Vector2f &size) {


}

void C_EllipseCollider::SetSize(float width, float height) {
    INNER_RADIUSy = height;
    OUTER_RADIUSx = width;
}

std::shared_ptr<b2BodyDef> C_EllipseCollider::setBodyDef(b2Vec2 pos) {
    BodyDef = std::make_shared<b2BodyDef>();
    BodyDef->position = pos;
    return BodyDef;
}

void C_EllipseCollider::setBodyPosition(b2Vec2 vec) {
    BodyDef->position = vec;
}

void C_EllipseCollider::setBodyType(std::string type) {
    if(type == "Static")
    {
        BodyDef->type = b2_staticBody;
    } else if (type == "Dynamic")
    {
        BodyDef->type = b2_dynamicBody;
    }
}

void C_EllipseCollider::setBodyShape( ) {
    ChainShape = std::make_shared<b2ChainShape>();
    std::vector<b2Vec2> vertices;
    for (int idx = 0;idx < DIVISIONS; idx++)
    {
        float angle = ((m_pi*2)/DIVISIONS)*idx;
        float xPos,yPos;
       // float radius = pow((double)OUTER_RADIUSx,2.f) * (1.0- pow((double)INNER_RADIUSy,2.f))/ 1.0-pow(INNER_RADIUSy,2.f)*pow(cos(angle),2.f);
        //radius = sqrt(radius);
        xPos = OUTER_RADIUSx* cosf(angle);
        yPos = INNER_RADIUSy * sinf(angle);
        vertices.push_back(b2Vec2(xPos,yPos));

    }
    vertices.push_back(vertices[0]);


    ChainShape->CreateChain(&vertices[0],vertices.size());

}

void C_EllipseCollider::setFixtureDef(float density, float friction) {
    FixtureDef = std::make_shared<b2FixtureDef>();
    FixtureDef->density = density;
    FixtureDef->friction = friction;
    FixtureDef->shape = ChainShape.get();

}

std::shared_ptr<b2Body> C_EllipseCollider::createFixture() {
    return std::shared_ptr<b2Body>();

}

void C_EllipseCollider::setBody(b2Body *body) {
 Body = body;
}

b2Body *C_EllipseCollider::getBody() {
    return Body;
}

std::shared_ptr<b2BodyDef> C_EllipseCollider::getBodyDef() {
    return BodyDef;
}

std::shared_ptr<b2FixtureDef> C_EllipseCollider::getFixtureDef() {
    return FixtureDef;
}

bool C_EllipseCollider::ApplyForceToBodyAtSpawn() {
    return applyForceAtSpawn;
}

b2Vec2 C_EllipseCollider::GetForce() {
    return Force;
}
