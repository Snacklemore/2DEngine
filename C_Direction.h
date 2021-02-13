//
// Created by root on 10.09.19.
//

#ifndef INC_2DENGINE_C_DIRECTION_H
#define INC_2DENGINE_C_DIRECTION_H

#include <memory>
#include "Component.h"
#include "Animation.h"
#include "C_Velocity.h"

class C_Direction :public Component{
public:
    C_Direction(Object *owner);
    void Awake() override;
    FacingDirection Get();

private:
    std::shared_ptr<C_Velocity> velocity;
    FacingDirection currentDir;

};


#endif //INC_2DENGINE_C_DIRECTION_H
