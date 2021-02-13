//
// Created by root on 05.09.19.
//

#include "Utilities.h"
sf::Vector2f Util::b2_to_sf(b2Vec2 vect, float scale)
{
    return sf::Vector2f(vect.x*scale,vect.y*scale);
}

sf::Vector2f Util::b2_to_sf(float x, float y, float scale)
{
    return sf::Vector2f(x*scale,y*scale);
}

b2Color Util::sf_to_b2(const sf::Color &color)
{
    return b2Color(color.r / 255,color.g/255,color.b/255);
}

b2Vec2 Util::sf_to_b2(const sf::Vector2f &vect, float scale) {
    return b2Vec2(vect.x/scale,vect.y/scale);

}

b2Vec2 Util::sf_to_b2(float x, float y, float scale) {
    return b2Vec2(x/ scale,y/scale);
}


sf::Color Util::transparent_color(sf::Color color, int transparency) {
    return sf::Color();
}

void Util::centerOrigin(sf::Sprite &sprite) {
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(std::floor(bounds.width/2.f),std::floor(bounds.height/2.f));
}

void Util::centerOrigin(sf::Text &text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.width/2.f),std::floor(bounds.height / 2));
}

sf::Color Util::b2_to_sf(const b2Color &color, int transparency) {
    return sf::Color(color.r * 255,color.g*255,color.b*255,transparency);
}

float Util::randomFloat(float lo, float hi) {
    float r = (float)(std::rand() & (RAND_MAX));
    r /= RAND_MAX;
    r = (hi -lo) * r+lo;
    return r;
}

float Util::distance(sf::Vector2f p1, sf::Vector2f p2) {
    float d =sqrtf((float)(p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
    return d;
}
