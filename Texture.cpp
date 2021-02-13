//
// Created by root on 13.05.20.
//

#include "Texture.h"
Texture::Texture(sf::Texture *texture, sf::IntRect rect) {
    m_texture = texture;
    m_rect = rect;
}