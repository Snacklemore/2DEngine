//
// Created by root on 12.09.19.
//

#ifndef INC_2DENGINE_RAYCAST_H
#define INC_2DENGINE_RAYCAST_H

#include "Object.h"
#include "S_Collidable.h"

struct RaycastResult{
    Object* collision;
};

class Raycast {
public:
    Raycast(Quadtree& collisions);
    RaycastResult Cast(const sf::Vector2f& from,const sf::Vector2f to);

private:
    sf::FloatRect BuildRect(const sf::Vector2f& lineOne,const sf::Vector2f& lineTwo);

    std::vector<sf::Vector2f> BuildLinePoints(const sf::Vector2f& from, const sf::Vector2f& to);
    Quadtree& collisions;
};


#endif //INC_2DENGINE_RAYCAST_H
