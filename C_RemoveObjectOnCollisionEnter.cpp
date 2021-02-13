//
// Created by root on 11.09.19.
//

#include "C_RemoveObjectOnCollisionEnter.h"
#include "Object.h"
#include "Debug.h"

C_RemoveObjectOnCollisionEnter::C_RemoveObjectOnCollisionEnter(Object *owner) : Component(owner) {

}

void C_RemoveObjectOnCollisionEnter::OnCollisionEnter(std::shared_ptr<C_BoxCollider> other) {
    owner->QueueForRemoval();
}

void C_RemoveObjectOnCollisionEnter::OnCollisionExit(std::shared_ptr<C_BoxCollider> other) {
    Debug::Log("OnCollisionExit is called");
}



