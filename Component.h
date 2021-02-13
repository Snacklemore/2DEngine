//
// Created by root on 29.08.19.
//

#ifndef INC_2DENGINE_COMPONENT_H
#define INC_2DENGINE_COMPONENT_H

#include "Window.h"


class Object;

class Component {
public:
    Component(Object* owner) : owner(owner){

    }
    virtual void Awake() {};
    virtual void Start() {};
    virtual void Update(float deltaTime) {};
    virtual void LateUpdate(float deltaTime){};
    Object *owner;

protected:

};


#endif //INC_2DENGINE_COMPONENT_H
