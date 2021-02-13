//
// Created by root on 31.08.19.
//

#ifndef INC_2DENGINE_C_KEYBOARDMOVEMENT_H
#define INC_2DENGINE_C_KEYBOARDMOVEMENT_H


#include "Component.h"
#include "Input.h"
#include "C_Animation.h"
#include "C_Velocity.h"

class C_KeyboardMovement : public Component{
public:
    C_KeyboardMovement(Object *owner);
    void Awake() override;
    void SetMovementSpeed(float moveSpeed);
    void Lock();
    void Unlock();
    void Update(float deltaTime) override;

private:
    //replace velocity with box2d object pointer or getter or remove

    std::shared_ptr<C_Velocity> velocity;
    float moveSpeed;
    std::shared_ptr<C_Animation> animation;
    bool isLocked;


};


#endif //INC_2DENGINE_C_KEYBOARDMOVEMENT_H
