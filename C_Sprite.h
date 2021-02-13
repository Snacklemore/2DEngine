//
// Created by root on 30.08.19.
//

#ifndef INC_2DENGINE_C_SPRITE_H
#define INC_2DENGINE_C_SPRITE_H

#include "Component.h"
#include "ResourceAllocator.h"
#include "C_Drawable.h"
#include "Texture.h"


class C_Sprite : public Component, public C_Drawable {
    friend class SpriteBatch;
public:
    C_Sprite(Object *owner);
    void Load(int id);
    void Load(const std::string& filePath);
    void SetTextureRect(int x,int y, int width,int height);
    void SetTextureRect(const sf::IntRect& rect);
    void Draw(Window& window) override;
    void SetScale(float x,float y);
    void LateUpdate(float deltaTime) override;
    void Update(float deltaTime) override;
    bool ContinueToDraw() const override;

    sf::Sprite* getSprite()
    {
        return &sprite;
    }
    Texture m_subtexture;
    sf::Color m_color;
private:
    sf::Sprite sprite;

    int currentTextureID;


};


#endif //INC_2DENGINE_C_SPRITE_H
