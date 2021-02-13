//
// Created by root on 06.05.20.
//

#ifndef INC_2DENGINE_S_LIGHTSYSTEM_H
#define INC_2DENGINE_S_LIGHTSYSTEM_H
#include <vector>
#include <memory>
#include <unordered_set>
#include <set>
#include <ltbl/lighting/LightSystem.h>
#include "Utilities.h"
#include "Object.h"

class S_LightSystem {
    using objLightPair = std::pair<std::shared_ptr<ltbl::LightPointEmission>,std::shared_ptr<Object>> ;
public:
 S_LightSystem(Window &window);

 std::shared_ptr<ltbl::LightPointEmission> AddLight(std::shared_ptr<Object> obj);
 std::shared_ptr<ltbl::LightPointEmission> AddLight(sf::Vector2f pos);
 void removeLight(Object obj);
 objLightPair attachLightToObject(std::shared_ptr<ltbl::LightPointEmission> &light, std::shared_ptr<Object> obj);
 void draw();
 void update();
 void setColor(sf::Color color,std::shared_ptr<ltbl::LightPointEmission> light);
 void setPosition(sf::Vector2f pos , std::shared_ptr<ltbl::LightPointEmission> light);
 void setTexture(sf::Texture Tex,std::shared_ptr<ltbl::LightPointEmission> light);
 void setLocalCastCenter(sf::Vector2f pos,std::shared_ptr<ltbl::LightPointEmission> light);
private:
    sf::Shader unshadowShader;
    sf::Shader lightOverShapeShader;
    sf::Texture penumbraTexture;
    sf::Texture pointLightTexture;
    sf::Texture directionLightTexture;
    std::shared_ptr<ltbl::LightSystem> ls;
    bool isInstanced = false;
    Window *window;
    std::shared_ptr<ltbl::LightPointEmission> PlayerPointLight;
    //map to store lights attached to objects
    //Vector of ObjectLightPairs
    std::vector<objLightPair> objectPointLights;

};


#endif //INC_2DENGINE_S_LIGHTSYSTEM_H
