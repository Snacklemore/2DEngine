//
// Created by root on 13.05.20.
//

#ifndef INC_2DENGINE_TEXTURE_H
#define INC_2DENGINE_TEXTURE_H


#include <SFML/Graphics/Text.hpp>

struct Texture {
    Texture(sf::Texture* texture = NULL,sf::IntRect rect = sf::IntRect());

    const sf::Texture* m_texture;
    sf::IntRect m_rect;


};



#endif //INC_2DENGINE_TEXTURE_H
