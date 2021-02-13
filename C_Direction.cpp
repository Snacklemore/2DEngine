//
// Created by root on 10.09.19.
//

#include "C_Direction.h"
#include "Object.h"

C_Direction::C_Direction(Object *owner) : Component(owner) ,currentDir(FacingDirection::Down){

}

void C_Direction::Awake() {
    //scrap the velocity component
    velocity = owner->GetComponent<C_Velocity>();
}
//this needs to be reworked too for box2d
//get velocity from box2d object and set direction
//get Velocity workingy by retrieving data from box2d
FacingDirection C_Direction::Get() {
    sf::Vector2f currentVel = velocity->Get();
    if (currentVel.x != 0.f || currentVel.y != 0.f)
    {
        float velXAbs = fabs(currentVel.x);
        float velYAbs = fabs(currentVel.y);

        if (velXAbs > velYAbs)
        {
            if (currentVel.x < 0)
            {
                currentDir = FacingDirection::Left;

            } else
            {
                currentDir = FacingDirection::Right;
            }
        } else
        {
            if(currentVel.y < 0)
            {
                currentDir = FacingDirection::Up;
            }
            else
            {
                currentDir = FacingDirection::Down;
            }
        }
    }
    return currentDir;
}
