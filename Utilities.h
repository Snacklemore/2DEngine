//
// Created by root on 05.09.19.
//

#ifndef INC_2DENGINE_UTILITIES_H
#define INC_2DENGINE_UTILITIES_H


#include <string>
#include <SFML/Graphics/Color.hpp>
#include <Box2D/Box2D.h>

#include <SFML/System/Time.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>

class Utilities {

public:
    static inline bool IsInteger(const std::string &s)
    {
        if (s.empty()
                || ((isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
        {
            return false;
        }
        char *p;
        strtol(s.c_str(),&p,10);
        return (*p == 0);
    }



};
namespace Util

{
    sf::Color b2_to_sf(const b2Color& color,int transparency = 255);
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);
    const float SCALE             = 30.f;
    const float GRAVITY           = 9.8f;
    float randomFloat(float lo,float hi);
    sf::Vector2f b2_to_sf(b2Vec2 vect,float scale = 1.f);
    sf::Vector2f b2_to_sf(float x, float y, float scale = 1.f);
    b2Color     sf_to_b2(const sf::Color& color);
    b2Vec2      sf_to_b2(const sf::Vector2f& vect,float scale = 1.f);
    b2Vec2      sf_to_b2(float x,float y, float scale = 1.f);
    float distance(sf::Vector2f p1, sf::Vector2f p2);
    sf::Color transparent_color(sf::Color color, int transparency = 255);

    void centerOrigin(sf::Sprite& sprite);
    void centerOrigin(sf::Text& text);

}


#endif //INC_2DENGINE_UTILITIES_H
