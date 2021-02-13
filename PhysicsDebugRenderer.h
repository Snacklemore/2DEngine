//
// Created by root on 29.04.20.
//

#ifndef INC_2DENGINE_PHYSICSDEBUGRENDERER_H
#define INC_2DENGINE_PHYSICSDEBUGRENDERER_H
#include "Utilities.h"
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
struct b2AABB;
class PhysicsDebugRenderer: public b2Draw {
public:
    PhysicsDebugRenderer(sf::RenderWindow* window,const float& thickness = -2.f,const int& transparancy = 50);
    void DrawPolygon(const b2Vec2* vertices,int32 vertexCount,const b2Color &color);
    void DrawSolidPolygon(const b2Vec2* vertices,int32 vertexCount,const b2Color &color);
    void DrawCircle(const b2Vec2& center,float radius,const b2Color& color);
    void DrawSolidCircle(const b2Vec2& center,float radius,const b2Vec2& axis,const b2Color& color);
    void DrawSegment(const b2Vec2& p1,const b2Vec2& p2,const b2Color& color);
    void DrawTransform(const b2Transform& xf);
    void DrawPoint(const b2Vec2& p, float size,const b2Color& color);
    void DrawAABB(b2AABB* aabb, const b2Color& color);
private:
    sf::RenderWindow *renderWindow;
    float thickness;
    int transparency;

};


#endif //INC_2DENGINE_PHYSICSDEBUGRENDERER_H
