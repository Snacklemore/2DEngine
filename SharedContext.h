//
// Created by root on 10.09.19.
//

#ifndef INC_2DENGINE_SHAREDCONTEXT_H
#define INC_2DENGINE_SHAREDCONTEXT_H

#include "Input.h"
#include "WorkingDirectory.h"
#include "ResourceAllocator.h"
#include "Window.h"



class S_LightSystem;
class ObjectCollection;

struct SharedContext {
    Input* input;
    ObjectCollection* objects;
    WorkingDirectory* workingDir;
    S_LightSystem* lightSytstem;
    ResourceAllocator<sf::Texture>* textureAllocator;
    Window *window;
    tgui::GuiSFML  *gui;

};


#endif //INC_2DENGINE_SHAREDCONTEXT_H
