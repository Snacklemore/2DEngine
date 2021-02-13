//
// Created by root on 29.08.19.
//

#ifndef INC_2DENGINE_SCENESTATEMACHINE_H
#define INC_2DENGINE_SCENESTATEMACHINE_H


#include <memory>
#include <unordered_map>
#include "Scene.h"
#include "Window.h"

class SceneStateMachine {
public:
    SceneStateMachine();
    void ProcessInput();
    void Update(float deltaTime) ;
    void LateUpdate(float deltaTime);
    void Draw(Window& window);

    unsigned int Add(std::shared_ptr<Scene> scene);
    void SwitchTo(unsigned int id);
    void Removes(unsigned int id);
private:
    std::unordered_map<unsigned int, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> curScene;
    unsigned int insertedSceneID;

};


#endif //INC_2DENGINE_SCENESTATEMACHINE_H
