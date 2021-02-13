//
// Created by root on 29.08.19.
//

#ifndef INC_2DENGINE_OBJECT_H
#define INC_2DENGINE_OBJECT_H


#include "Window.h"
#include <vector>
#include "Component.h"
#include "C_Transform.h"
#include "C_Drawable.h"
#include "C_InstanceID.h"
#include "SharedContext.h"
#include "C_Collidable.h"

#include <memory>


enum class ObjectType{
    Player,Projectile,Tile,Lightobject,UserInterface,InterActable
};
class Object {
public:
    Object(SharedContext* context);
    std::shared_ptr<C_InstanceID> instanceID;
    std::shared_ptr<C_Transform> transform;
    //Called when object created
    void Awake() ;
    void OnCollisionEnter(std::shared_ptr<C_BoxCollider> other);
    void OnCollisionStay(std::shared_ptr<C_BoxCollider> other);
    void OnCollisionExit(std::shared_ptr<C_BoxCollider> other);
    //Calles after Awake() to init vars
    void Start() ;
    SharedContext* context;
    bool isQueuedForRemoval();
    bool isQueuedForRemovalInCollection() ;

    void QueueForRemoval();
    void QueueForRemovalInCollection();
    void setType(ObjectType type);
    ObjectType getType();
    void Update(float deltaTime) ;

    void LateUpdate(float deltaTime) ;

    void Draw(Window& window);

    template <typename T> std::shared_ptr<T> AddComponent()
    {

        for (auto& existingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(existingComponent))
            {
                return std::dynamic_pointer_cast<T>(existingComponent);
            }
        }
        std::shared_ptr<T> newComponent = std::make_shared<T>(this);
        components.push_back(newComponent);

        if (std::dynamic_pointer_cast<C_Drawable>(newComponent))
        {
            drawable = std::dynamic_pointer_cast<C_Drawable>(newComponent);
        }
        if ( std::dynamic_pointer_cast<C_Collidable>(newComponent))
        {
            collidables.push_back(std::dynamic_pointer_cast<C_Collidable>(newComponent));
        }


        return newComponent;
    };
    template <typename T> std::shared_ptr<T> GetComponent()
    {

        for (auto &existingComponent : components)
        {
            if ( std::dynamic_pointer_cast<T>(existingComponent))
            {
                return std::dynamic_pointer_cast<T>(existingComponent);

            }
        }
        return nullptr;
    };
    std::shared_ptr<C_Drawable> GetDrawable();

private:
    ObjectType _type;

    std::shared_ptr<C_Drawable> drawable;
    bool queuedForRemoval;
    bool queuedForRemovalInCollection ;
    std::vector<std::shared_ptr<C_Collidable>> collidables;
    std::vector<std::shared_ptr<Component>> components;
};


#endif //INC_2DENGINE_OBJECT_H
