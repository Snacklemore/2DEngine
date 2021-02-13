//
// Created by root on 06.05.20.
//

#include "S_LightSystem.h"
using objLightPair = std::pair<std::shared_ptr<ltbl::LightPointEmission>,std::shared_ptr<Object>> ;
S_LightSystem::S_LightSystem(Window &_window) {
    window = &_window;
    ls = std::make_shared<ltbl::LightSystem>();
    unshadowShader.loadFromFile("resources/unshadowShader.vert", "resources/unshadowShader.frag");
    lightOverShapeShader.loadFromFile("resources/lightOverShapeShader.vert", "resources/lightOverShapeShader.frag");
    penumbraTexture.loadFromFile("resources/penumbraTexture.png");
    penumbraTexture.setSmooth(true);
    pointLightTexture.loadFromFile("resources/pointLightTexture.png");
    pointLightTexture.setSmooth(true);
    directionLightTexture.loadFromFile("resources/directionLightTexture.png");
    ls->create(ltbl::rectFromBounds(sf::Vector2f(0.0f,0.0f),sf::Vector2f(1000.0f,1000.0f)),window->getWindowHandle()->getSize(),penumbraTexture,unshadowShader,lightOverShapeShader);

}

std::shared_ptr<ltbl::LightPointEmission> S_LightSystem::AddLight(std::shared_ptr<Object> obj) {
     std::shared_ptr<ltbl::LightPointEmission> light = std::make_shared<ltbl::LightPointEmission>();
     light->_emissionSprite.setOrigin(sf::Vector2f(pointLightTexture.getSize().x *0.5,pointLightTexture.getSize().y * 0.5));
     light->_emissionSprite.setTexture(pointLightTexture);
     light->_emissionSprite.setScale(sf::Vector2f(30.0,30.0));
     light->_emissionSprite.setColor(sf::Color(255,127,80));
     light->_emissionSprite.setPosition(sf::Vector2f(0,0));

     objLightPair objLightPair = attachLightToObject(light,obj);
     objectPointLights.emplace_back(objLightPair);
     ls->addLight(light);
     return light;


}





void S_LightSystem::removeLight(Object obj) {
    //TODO

}

void S_LightSystem::draw() {
    sf::Sprite spr;
    ls->render(window->GetView(),unshadowShader,lightOverShapeShader);
    spr.setTexture(ls->getLightingTexture());
    sf::View view = window->GetView();
    sf::RenderStates lightRenderStates;
    lightRenderStates.blendMode = sf::BlendMultiply;
    window->getWindowHandle()->setView(window->getWindowHandle()->getDefaultView());
    window->getWindowHandle()->draw(spr,lightRenderStates);
    window->getWindowHandle()->setView(view);




}

void S_LightSystem::update() {
    for ( objLightPair &lightObject : objectPointLights)
    {
        //get object
        std::shared_ptr<Object> obj = lightObject.second;
        //get light
        std::shared_ptr<ltbl::LightPointEmission> light = lightObject.first;
        //set position of light to position of object
        sf::Vector2f pos = obj->GetComponent<C_Transform>()->GetPosition();
        light->_emissionSprite.setPosition(pos);

    }

}

objLightPair S_LightSystem::attachLightToObject(std::shared_ptr<ltbl::LightPointEmission> &light, std::shared_ptr<Object> obj) {
    objLightPair objLight  = std::make_pair(light,obj);
    return objLight;

}

void S_LightSystem::setColor(sf::Color color, std::shared_ptr<ltbl::LightPointEmission> light) {
    light->_emissionSprite.setColor(color);
}

void S_LightSystem::setPosition(sf::Vector2f pos, std::shared_ptr<ltbl::LightPointEmission> light) {
    light->_emissionSprite.setPosition(pos);
}

void S_LightSystem::setTexture(sf::Texture Tex,std::shared_ptr<ltbl::LightPointEmission> light) {
    light->_emissionSprite.setTexture(Tex);
}

void S_LightSystem::setLocalCastCenter(sf::Vector2f pos,std::shared_ptr<ltbl::LightPointEmission> light) {
    light->_localCastCenter = pos;
}

std::shared_ptr<ltbl::LightPointEmission> S_LightSystem::AddLight(sf::Vector2f pos) {
    std::shared_ptr<ltbl::LightPointEmission> light = std::make_shared<ltbl::LightPointEmission>();
    light->_emissionSprite.setOrigin(sf::Vector2f(pointLightTexture.getSize().x *0.5,pointLightTexture.getSize().y * 0.5));
    light->_emissionSprite.setTexture(pointLightTexture);
    light->_emissionSprite.setScale(sf::Vector2f(3.0,3.0));
    light->_emissionSprite.setColor(sf::Color(255,127,80));
    light->_emissionSprite.setPosition( pos);

    //objLightPair objLightPair = attachLightToObject(light,obj);
    //objectPointLights.emplace_back(objLightPair);
    ls->addLight(light);
    return light;
}
