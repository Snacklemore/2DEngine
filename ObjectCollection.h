//
// Created by root on 01.09.19.
//

#ifndef INC_2DENGINE_OBJECTCOLLECTION_H
#define INC_2DENGINE_OBJECTCOLLECTION_H


#include <vector>

#include "Object.h"
#include "S_Drawable.h"
#include "S_Collidable.h"
#include "SharedContext.h"


class ObjectCollection {
public:
    void Add(std::shared_ptr<Object> object);
    void Add(std::vector<std::shared_ptr<Object>> &otherObjects);
    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw(Window &window);
    S_Collidable * getCollidableSystem();
    void ProcessRemovals();
    void ProcessNewObjects();
    void SetPlayer(std::shared_ptr<Object>& player);
    std::shared_ptr<Object>& GetPlayer();



private:
    S_Collidable collidables;

    S_Drawable drawables;
public:
    const std::vector<std::shared_ptr<Object>> &getTerrainTiles() const;
    void DEBUG_deletefirstObject()
    {
        objects[0]->QueueForRemoval();
    }
    void ProcessTerrainTiles(std::vector<std::shared_ptr<Object>> tVec);
private:
    std::vector<std::shared_ptr<Object>> terrainTiles;
    std::vector<std::shared_ptr<Object>> ColliderTiles;

private:

    std::shared_ptr<Object> player;
    std::shared_ptr<Object> keepAlivePtr;
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Object>> unusedObjects;


    std::vector<std::shared_ptr<Object>> newObjects;

};


#endif //INC_2DENGINE_OBJECTCOLLECTION_H
