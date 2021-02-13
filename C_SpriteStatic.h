//
// Created by root on 30.08.19.
//

#ifndef INC_2DENGINE_C_SPRITESTATIC_H
#define INC_2DENGINE_C_SPRITESTATIC_H

#include "Component.h"
#include "ResourceAllocator.h"
#include "C_Drawable.h"

class C_SpriteStatic : public Component, public C_Drawable {
public:
    C_SpriteStatic(Object *owner);
    void Load(int id);
    void Load(const std::string& filePath);
    void SetTextureRect(int x,int y, int width,int height);
    void SetTextureRect(const sf::IntRect& rect);
    void Draw(Window& window) override;
    void SetScale(float x,float y);
    void setPosition();
    bool ContinueToDraw() const override;

private:
    sf::Sprite sprite;
    int currentTextureID;
};


#endif //INC_2DENGINE_C_SPRITESTATIC_H
