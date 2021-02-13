//
// Created by root on 23.08.19.
//

#include "Game.h"


Game::Game()
        : window("2DGameEngine")
{
     gui =  std::make_shared<tgui::GuiSFML>();
     gui->setTarget(*window.getWindowHandle());

     window.setGui(gui);
     std::shared_ptr<SceneSplashScreen> splashScreen =
             std::make_shared<SceneSplashScreen>(workingDir,sceneStateMachine,window,textureAllocator);
     std::shared_ptr<SceneGame> gameScene =
             std::make_shared<SceneGame>(workingDir,textureAllocator,window,gui.get());
     unsigned int splashScreenID= sceneStateMachine.Add(splashScreen);
     unsigned int gameSceneID = sceneStateMachine.Add(gameScene);
     splashScreen->SetSwitchToScene(gameSceneID);

     sceneStateMachine.SwitchTo(splashScreenID);

     deltaTime = clock.restart().asSeconds();
}
void Game::Update(float deltaTime) {

    window.Update();
    sceneStateMachine.Update(deltaTime);


}

void Game::LateUpdate() {
    sceneStateMachine.LateUpdate(deltaTime);
}

void Game::Draw() {
    window.BeginDraw();
    sceneStateMachine.Draw(window);
    window.EndDraw();

}

bool Game::IsRunning() const {
    return window.isOpen();
}

void Game::calculateDeltaTime() {
    deltaTime  = clock.restart().asSeconds();

}

void Game::CaptureInput() {
     sceneStateMachine.ProcessInput();

}
