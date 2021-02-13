//
// Created by root on 23.08.19.
//

#ifndef INC_2DENGINE_GAME_H
#define INC_2DENGINE_GAME_H

#include "WorkingDirectory.h"
#include <TGUI/TGUI.hpp>
#include "Window.h"
#include "Input.h"
#include "SceneStateMachine.h"
#include "SceneSplashScreen.h"
#include "SceneGame.h"
#include "C_Sprite.h"

class Game {
public:
    void CaptureInput();
    Game();
    void Update(float deltaTime);
    void LateUpdate();
    void Draw();
    bool IsRunning() const;
    void calculateDeltaTime();

private:
    std::shared_ptr<tgui::GuiSFML> gui;
    Window window;
    Input input;
    WorkingDirectory workingDir;
    ResourceAllocator<sf::Texture> textureAllocator;
    sf::Clock clock;
    float deltaTime;
    SceneStateMachine sceneStateMachine;


};


#endif //INC_2DENGINE_GAME_H
