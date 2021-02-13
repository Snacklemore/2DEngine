//
// Created by root on 10.09.19.
//

#ifndef INC_2DENGINE_C_VELOCITY_H
#define INC_2DENGINE_C_VELOCITY_H

#include <math.h>

#include <Box2D/Dynamics/b2World.h>
#include "ObjectCollection.h"
#include "Component.h"
//scrap this for box2d
class C_Velocity: public Component {
public:
    C_Velocity(Object* owner);

    void Update(float deltaTime) override;

    void Set(const sf::Vector2f& vel);
    void Set(float x,float y);
    sf::Vector2f Get();

private:
    std::shared_ptr<b2World> physicsWorld;
    void ClampVelocity();
    sf::Vector2f velocity;
    sf::Vector2f maxVelocity;

};


#endif //INC_2DENGINE_C_VELOCITY_H
