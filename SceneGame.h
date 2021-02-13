//
// Created by root on 29.08.19.
//

#ifndef INC_2DENGINE_SCENEGAME_H
#define INC_2DENGINE_SCENEGAME_H


#include "Scene.h"
#include "WorkingDirectory.h"
#include "Input.h"
#include "Object.h"
#include "C_Sprite.h"
#include "C_KeyboardMovement.h"
#include "ResourceAllocator.h"
#include "ObjectCollection.h"
#include "C_Animation.h"
#include "TileMapParser.h"
#include "C_Camera.h"
#include "C_ProjectileAttack.h"
#include "C_Velocity.h"
#include "C_MovementAnimation.h"
#include "C_Direction.h"
#include "S_LightSystem.h"
#include "C_RayCaster.h"

class SceneGame : public Scene {
public:
    SceneGame(WorkingDirectory& workingDir,ResourceAllocator<sf::Texture>& textureAllocator, Window& window,  tgui::GuiSFML *gui);
    void OnCreate() override ;
    void OnDestroy() override ;
    void OnActivate() override;
    void OnDeactivate() override;
    void ProcessInput() override;
    void Update(float deltaTime) override;
    void Draw(Window& window) override;
    void LateUpdate(float deltaTime) override;
    void AddAnimationComponent(std::shared_ptr<Object> object, const int textureID);
    void CreatePlayer();
    void CreateFriend();
private:
    tgui::GuiSFML *gui;
    std::shared_ptr<Object> _player;
    TileMapParser mapParser;
    ObjectCollection objects;
    //std::shared_ptr<Object> player;
    ResourceAllocator<sf::Texture>& textureAllocator;
    WorkingDirectory& workingDir;
    Input input;
    Window &window;
    SharedContext context;
    std::shared_ptr<S_LightSystem>  sLightSystem;
};


#endif //INC_2DENGINE_SCENEGAME_H
