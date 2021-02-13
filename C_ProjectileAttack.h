//
// Created by root on 10.09.19.
//

#ifndef INC_2DENGINE_C_PROJECTILEATTACK_H
#define INC_2DENGINE_C_PROJECTILEATTACK_H

#include "Component.h"
#include "C_Animation.h"
#include "Input.h"
#include "ObjectCollection.h"
#include "WorkingDirectory.h"

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};
class C_ProjectileAttack : public Component{
public:
    C_ProjectileAttack(Object* owner);
    void Awake() override;
    void Update(float deltaTime) override;

    void Start() override;



private:
    //direction of the spritetexture
    static std::unordered_map<FacingDirection ,sf::IntRect,EnumClassHash> textureDirectionBindings;
    void SpawnProjectile();
    std::shared_ptr<C_Animation> animation;
    int projectileTextureID;
    std::shared_ptr<C_Direction> direction;
    //position of the spawned projectile relative to player
    static std::unordered_map<FacingDirection ,sf::Vector2f,EnumClassHash> offsetDirectionBindings;
    //either 1 or -1 to let it fly in correct direction, need to get rid of this
    static std::unordered_map<FacingDirection, sf::Vector2f, EnumClassHash> velocityDirectionBindings;
    //replace with box2d object velocity
    float projectileVelocity;
};


#endif //INC_2DENGINE_C_PROJECTILEATTACK_H
