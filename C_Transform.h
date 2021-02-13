//
// Created by root on 30.08.19.
//

#ifndef INC_2DENGINE_C_TRANSFORM_H
#define INC_2DENGINE_C_TRANSFORM_H


#include "Component.h"

class C_Transform :public Component{
public:
    C_Transform(Object* owner);
    void SetPosition(float x , float y);
    void SetPosition(sf::Vector2f pos);

    void AddPosition(float x, float y);
    void AddPosition(sf::Vector2f pos);

     void SetX(float x);
     void SetY(float y);
     void AddX(float x);
     void AddY(float y);
     void setStatic(bool isStatic);
     bool isStatic() const;
     const  sf::Vector2f& GetPosition() const;
    const sf::Vector2f& GetPreviousFramePosition() const;

private:
    bool isStaticTransform;
    sf::Vector2f position;
    sf::Vector2f previousFramePosition;
};


#endif //INC_2DENGINE_C_TRANSFORM_H
