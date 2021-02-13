//
// Created by root on 08.09.19.
//

#ifndef INC_2DENGINE_C_CAMERA_H
#define INC_2DENGINE_C_CAMERA_H

#include "Component.h"
#include "Object.h"

class C_Camera :public Component{
public:
    C_Camera(Object* owner);
    void LateUpdate(float deltaTime) override;

private:



};


#endif //INC_2DENGINE_C_CAMERA_H


