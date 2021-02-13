//
// Created by root on 06.09.19.
//

#ifndef INC_2DENGINE_C_DRAWABLE_H
#define INC_2DENGINE_C_DRAWABLE_H


#include <SFML/Graphics.hpp>

#include <memory>

#include "Component.h"


enum class DrawLayer
{
    Default,Background,Foreground,BehindPlayer,Entities,InfrontPlayer

};
class C_Drawable  {
public:
    C_Drawable();
    virtual ~C_Drawable();
    virtual void Draw(Window& window) =0;
    void SetSortOrder(int order);
    int GetSortOrder() const;
    virtual bool ContinueToDraw() const = 0;

    //delegate this to sprite


    void SetDrawLayer(DrawLayer drawLayer);
    DrawLayer GetDrawLayer() const;

private:

    int sortOrder;
    DrawLayer layer;
};


#endif //INC_2DENGINE_C_DRAWABLE_H
