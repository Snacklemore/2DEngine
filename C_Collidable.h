//
// Created by root on 10.09.19.
//

#ifndef INC_2DENGINE_C_COLLIDABLE_H
#define INC_2DENGINE_C_COLLIDABLE_H

#include <memory>
#include "C_BoxCollider.h"
class C_Collidable {
public:
    virtual void OnCollisionEnter(std::shared_ptr<C_BoxCollider> other){};
    virtual void OnCollisionStay(std::shared_ptr<C_BoxCollider> other){};
    virtual void OnCollisionExit(std::shared_ptr<C_BoxCollider> other) {};


};


#endif //INC_2DENGINE_C_COLLIDABLE_H
