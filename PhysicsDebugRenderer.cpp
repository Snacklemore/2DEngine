//
// Created by root on 29.04.20.
//

#include "PhysicsDebugRenderer.h"

PhysicsDebugRenderer::PhysicsDebugRenderer(sf::RenderWindow *window, const float &thickness, const int &transparancy)
        : renderWindow(window),thickness (thickness),transparency(transparancy) {

}

void PhysicsDebugRenderer::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {


}

void PhysicsDebugRenderer::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    sf::ConvexShape poly;
    poly.setOutlineThickness(thickness);
    poly.setOutlineColor(Util::b2_to_sf(color));
    poly.setFillColor(Util::b2_to_sf(color,transparency));

    poly.setPointCount(vertexCount);
    for (int32 i = 0;i < vertexCount;i++)
    {
        poly.setPoint(i,Util::b2_to_sf(vertices[i],Util::SCALE));
    }
    if (renderWindow)
        renderWindow->draw(poly);

}

void PhysicsDebugRenderer::DrawCircle(const b2Vec2 &center, float radius, const b2Color &color) {

    sf::CircleShape circle(radius * Util::SCALE);
    circle.setOrigin( radius *Util::SCALE,radius* Util::SCALE);
    circle.setPosition(Util::b2_to_sf(center,Util::SCALE));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(1.0f);
    circle.setOutlineColor(Util::b2_to_sf(color));

    if (renderWindow)
        renderWindow->draw(circle);
}

void PhysicsDebugRenderer::DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color) {
    sf::CircleShape circle(radius *Util::SCALE);
    circle.setOrigin( radius *Util::SCALE,radius* Util::SCALE);
    circle.setPosition(Util::b2_to_sf(center,Util::SCALE));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(1.0f);
    circle.setOutlineColor(Util::b2_to_sf(color));

    b2Vec2 endPoint = center + radius *axis;
    sf::Vertex line[2] =
            {
            sf::Vertex(Util::b2_to_sf(center,Util::SCALE),Util::b2_to_sf(color)),
            sf::Vertex(Util::b2_to_sf(endPoint,Util::SCALE),Util::b2_to_sf(color))
            };
    if (renderWindow)
    {
        renderWindow->draw(circle);
        renderWindow->draw(line,2,sf::Lines);
    }

}

void PhysicsDebugRenderer::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
sf::Vertex line[] =
	{
		sf::Vertex(Util::b2_to_sf(p1,Util::SCALE), Util::b2_to_sf(color)),
		sf::Vertex(Util::b2_to_sf(p2,Util::SCALE), Util::b2_to_sf(color))
	};

    renderWindow->draw(line, 2, sf::Lines);
}

void PhysicsDebugRenderer::DrawTransform(const b2Transform &xf) {

}

void PhysicsDebugRenderer::DrawPoint(const b2Vec2 &p, float size, const b2Color &color) {

}

void PhysicsDebugRenderer::DrawAABB(b2AABB *aabb, const b2Color &color) {

}
