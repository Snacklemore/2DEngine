//
// Created by root on 12.09.19.
//

#include "Raycast.h"

Raycast::Raycast(Quadtree &collisions) : collisions(collisions){

}

RaycastResult Raycast::Cast(const sf::Vector2f &from, const sf::Vector2f to) {
    //Build empty raycast result
    RaycastResult result;
    result.collision = nullptr;


    //Check if from and to are the same
    if (from == to )
        return result;
    // create rect that encompasses line
    sf::FloatRect collisionArea = BuildRect(from,to);

    //Retrieve entities from collision system within the area

    std::vector<std::shared_ptr<C_BoxCollider>> entities = collisions.Search(collisionArea);

    //if no entities return empty

    if (entities.size() == 0)
        return result;

    //create stepped line from first to second point

    std::vector<sf::Vector2f> linePoints = BuildLinePoints(from,to);

    //For each point check if intersecting with every entity
    for (auto& p : linePoints)
    {
        for (auto&e: entities)
        {
            sf::FloatRect entityRect = e->GetCollidable();
            if(entityRect.contains(p))
            {
                result.collision = e->owner;
                return result;
            }
        }
    }
    return result;
}

sf::FloatRect Raycast::BuildRect(const sf::Vector2f &lineOne, const sf::Vector2f &lineTwo) {
    float left,top,width,height;

    if (lineOne.x < lineTwo.x)
    {
        left = lineOne.x;
        width = lineTwo.x -lineOne.x;

    }
    else
    {
        left = lineTwo.x;
        width = lineOne.x - lineTwo.x;
    }

    if(lineOne.y < lineTwo.y)
    {
        top = lineOne.y;
        height = lineTwo.y - lineOne.y;
    }
    else
    {
        top = lineTwo.y;
        height = lineOne.y - lineTwo.y;
    }

    return sf::FloatRect(left, top, width, height);

}

std::vector<sf::Vector2f> Raycast::BuildLinePoints(const sf::Vector2f &from, const sf::Vector2f &to) {
// TODO: it would be preferable to calculate in
    // advance the size of "result" and to use a fixed-size array
    // instead of a list.
    std::vector<sf::Vector2f> result;

    sf::Vector2f diff = to - from;
    int steps = 0;

    float absDiffX = abs(diff.x);
    float absDiffY = abs(diff.y);

    if (absDiffX > absDiffY)
    {
        steps = absDiffX;
    }
    else
    {
        steps = absDiffY;
    }

    float xStep = diff.x / (float)steps;
    float yStep = diff.y / (float)steps;

    float newX = from.x;
    float newY = from.y;

    for (int i = 0; i <= steps; i++)
    {
        result.push_back(sf::Vector2f(newX, newY));

        newX += xStep;
        newY += yStep;
    }

    return result;
}
