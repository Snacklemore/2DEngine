//
// Created by root on 10.09.19.
//

#ifndef INC_2DENGINE_C_MOVEMENTANIMATION_H
#define INC_2DENGINE_C_MOVEMENTANIMATION_H
#include "Component.h"
#include "C_Velocity.h"
#include "C_Animation.h"

class C_MovementAnimation: public Component {
public:
    C_MovementAnimation(Object* owner);

    void Awake() override;

    void Update(float deltaTime) override;

private:
    std::shared_ptr<C_Velocity> velocity;
    std::shared_ptr<C_Animation> animation;

};


#endif //INC_2DENGINE_C_MOVEMENTANIMATION_H
