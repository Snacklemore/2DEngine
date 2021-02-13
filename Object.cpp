//
// Created by root on 29.08.19.
//

#include "Object.h"

void Object::Awake() {
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Awake();
    }

}

void Object::Start() {
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Start();
    }

}

void Object::Update(float deltaTime) {
    for ( const auto& component : components)
    {
        component->Update(deltaTime);
    }

}

void Object::LateUpdate(float deltaTime) {
    for ( const auto& component : components)
    {
        component->LateUpdate(deltaTime);
    }

}

void Object::Draw(Window &window) {
    drawable->Draw(window);

}

Object::Object(SharedContext* context):context(context), queuedForRemoval(false),queuedForRemovalInCollection(false) {
    transform = AddComponent<C_Transform>();
    instanceID = AddComponent<C_InstanceID>();

}

void Object::QueueForRemoval() {
    queuedForRemoval = true;
}

bool Object::isQueuedForRemoval() {
    return queuedForRemoval;
}

std::shared_ptr<C_Drawable> Object::GetDrawable() {
    return drawable;
}

void Object::OnCollisionEnter(std::shared_ptr<C_BoxCollider> other) {
    for (auto& component : collidables)
    {
        component->OnCollisionEnter(other);
    }
}

void Object::OnCollisionStay(std::shared_ptr<C_BoxCollider> other) {
    for (auto& component : collidables)
    {
        component->OnCollisionStay(other);
    }
}

void Object::OnCollisionExit(std::shared_ptr<C_BoxCollider> other) {
    for (auto& component : collidables)
    {
        component->OnCollisionExit(other);
    }
}

void Object::setType(ObjectType type) {
    _type = type;
}

ObjectType Object::getType() {
    return _type;
}

void Object::QueueForRemovalInCollection() {
    queuedForRemovalInCollection = true;

}

bool Object::isQueuedForRemovalInCollection() {
    return queuedForRemovalInCollection;
}
