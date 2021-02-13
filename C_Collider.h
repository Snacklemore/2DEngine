//
// Created by root on 06.09.19.
//

#ifndef INC_2DENGINE_C_COLLIDER_H
#define INC_2DENGINE_C_COLLIDER_H

#include <memory>
#include <SFML/Graphics.hpp>

#include "Component.h"

enum class CollisionLayer
{
    Default = 0x0001,
    Player = 0x0002,
    Tile = 0x0004,
    Projectile = 0x0008,
    NPC = 0x0010
};

struct Manifold
{
    bool colliding = false;
    const sf::FloatRect* other;
};
class C_Collider :public Component{
public:
    C_Collider(Object* owner);
    ~C_Collider();


    CollisionLayer  GetLayer() const;
    void SetLayer(CollisionLayer layer);

private:
    CollisionLayer layer;

};


#endif //INC_2DENGINE_C_COLLIDER_H
