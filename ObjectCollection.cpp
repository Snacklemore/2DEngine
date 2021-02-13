//
// Created by root on 01.09.19.
//

#include "ObjectCollection.h"
#include "Debug.h"

//need to rework this to work with box2d collidable system
void ObjectCollection::Add(std::shared_ptr<Object> object) {
    newObjects.push_back(object);
}

void ObjectCollection::ProcessTerrainTiles(std::vector<std::shared_ptr<Object>> tVec) {
    std::vector<std::shared_ptr<Object>> saved_tVec = tVec;
}


void ObjectCollection::Update(float deltaTime) {

    for (const auto& o : objects)
    {

        o->Update(deltaTime);

    }
    //std::cout << "ObjectsUpdated:" << objects.size() << std::endl;
    //box2d collidables update here
    //call worldstep at this position
    collidables.Update();
}

void ObjectCollection::LateUpdate(float deltaTime) {
    for (const auto& o : objects)
    {
        o->LateUpdate(deltaTime);
    }


}

void ObjectCollection::Draw(Window &window) {

    drawables.Draw(window);
}


void ObjectCollection::ProcessNewObjects() {
    if (newObjects.size() > 0)
    {
        for (const auto& o : newObjects)
        {
            o->Awake();
            o->Start();
        }




        //All objects are getting inserted into objects !!
        objects.insert(objects.end(), newObjects.begin(), newObjects.end());
        //Flag objects added to subsystems to be removed from the Collection
        //since updating them is job for said subsystems
        //Rework of removing objects (partially )needed:
        //CollidableSystem is checking objects for removal, no need to call
        //ProcessRemovals() in CollectionSystem
        drawables.Add(newObjects);


        collidables.Add(newObjects);


        newObjects.clear();
    }

}
S_Collidable * ObjectCollection::getCollidableSystem() {
    return &collidables;
}

void ObjectCollection::ProcessRemovals() {
    bool removed = false;
    auto objIterator = objects.begin();
    while (objIterator != objects.end())
    {
        auto obj = *objIterator;

        if (obj->isQueuedForRemovalInCollection())
        {
            //need to store the unused objects somewhere i guess

            unusedObjects.push_back(obj);
           // keepAlivePtr = *objIterator;
            objIterator = objects.erase(objIterator);
            //std::cout << "Removed static Object" << std::endl;

            continue;
        }
        if(obj->isQueuedForRemoval())
        {
            //keeping alive the last object deleted
            //need a better way, because two or more deleted objects in one frame
            //means one object is gone when deleting the C_Collider component
            //(need to delete Objects "from the back" beginning with the C_BoxCollider
            // and deleting the body from the physicsworld)
            keepAlivePtr = *objIterator;
            objIterator = objects.erase(objIterator);

            removed = true;

        }
        else{
            ++objIterator;
        }




    }



}

void ObjectCollection::Add(std::vector<std::shared_ptr<Object>> &otherObjects) {
    newObjects.insert(newObjects.end(),otherObjects.begin(),otherObjects.end());
}




void ObjectCollection::SetPlayer(std::shared_ptr<Object>& player) {
    this->player = player;
}

std::shared_ptr<Object> &ObjectCollection::GetPlayer() {
    return player;
}

const std::vector<std::shared_ptr<Object>> &ObjectCollection::getTerrainTiles() const {
    return terrainTiles;
}

