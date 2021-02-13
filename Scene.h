//
// Created by root on 29.08.19.
//

#ifndef INC_2DENGINE_SCENE_H
#define INC_2DENGINE_SCENE_H

#include "Window.h"
class Scene {

public:
    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;
    virtual void OnActivate() = 0;
    virtual void OnDeactivate() = 0;

    virtual void ProcessInput() {};
    virtual void Update(float deltaTime){};
    virtual void LateUpdate ( float delatTime) {};
    virtual void Draw(Window& window) {};

};


#endif //INC_2DENGINE_SCENE_H
