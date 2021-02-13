//
// Created by root on 06.09.19.
//

#ifndef INC_2DENGINE_QUADTREE_H
#define INC_2DENGINE_QUADTREE_H

#include <memory>
#include <vector>

#include "C_BoxCollider.h"
#include "Object.h"


class Quadtree {
public:
    void DrawDebug();
    Quadtree();
    Quadtree(int maxObjects,int maxLevels,int level,sf::FloatRect bounds, Quadtree*parent);

    void Insert(std::shared_ptr<C_BoxCollider> object);

    void UpdatePosition(std::shared_ptr<C_BoxCollider> object);
    void Remove(std::shared_ptr<C_BoxCollider> object);

    void Clear();

    std::vector<std::shared_ptr<C_BoxCollider>> Search(const sf::FloatRect& area);

    const sf::FloatRect& GetBounds() const;

private:
    void Search(const sf::FloatRect& area, std::vector<std::shared_ptr<C_BoxCollider>>&overlappingObjects);
    int GetChildIndexForObject(const sf::FloatRect& objectBounds);
    void Split();

    static const int thisTree = -1;
    static const int childNE = 0;
    static const int childNW = 1;
    static const int childSW = 2;
    static const int childSE = 3;

    int maxObjects;
    int maxLevels;

    Quadtree* parent;
    std::shared_ptr<Quadtree> children[4];

    std::vector<std::shared_ptr<C_BoxCollider>> objects;
    int level;

     sf::FloatRect bounds;

};


#endif //INC_2DENGINE_QUADTREE_H
