//
// Created by root on 30.08.19.
//

#include "C_SpriteStatic.h"
#include "Object.h"


C_SpriteStatic::C_SpriteStatic(Object *owner) : Component(owner) ,currentTextureID(-1){

}
void C_SpriteStatic::Load(const std::string &filePath) {
    if ( owner->context->textureAllocator)
    {
        int textureID = owner->context->textureAllocator->Add(filePath);

        if (textureID >= 0 && textureID != currentTextureID)
        {
            currentTextureID = textureID;
            std::shared_ptr<sf::Texture> texture = owner->context->textureAllocator->Get(textureID);
            sprite.setTexture(*texture);
        }
    }
}

void C_SpriteStatic::Draw(Window& window)
{
    window.Draw(sprite);

}





void C_SpriteStatic::Load(int id) {

    if(id >= 0 && id != currentTextureID)
    {
        currentTextureID = id;
        std::shared_ptr<sf::Texture> texture = owner->context->textureAllocator->Get(id);
        sprite.setTexture(*texture);
    }

}

void C_SpriteStatic::SetTextureRect(int x, int y, int width, int height) {
    sprite.setTextureRect(sf::IntRect(x,y,width,height));
}

void C_SpriteStatic::SetTextureRect(const sf::IntRect &rect) {
    sprite.setTextureRect(rect);
}

void C_SpriteStatic::SetScale(float x,float y) {
    sprite.setScale(x,y);


}

bool C_SpriteStatic::ContinueToDraw() const {
    return !owner->isQueuedForRemoval();
}

void C_SpriteStatic::setPosition() {
    sf::Vector2f pos = owner->transform->GetPosition();
    const sf::IntRect& spriteBounds = sprite.getTextureRect();
    const sf::Vector2f& spriteScale = sprite.getScale();
    sprite.setPosition(
            pos.x -((abs(spriteBounds.width)* 0.5f) * spriteScale.x),
            pos.y -((abs(spriteBounds.height) * 0.5f) * spriteScale.y)
    );


}
