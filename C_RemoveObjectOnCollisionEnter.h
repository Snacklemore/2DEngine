//
// Created by root on 11.09.19.
//

#ifndef INC_2DENGINE_C_REMOVEOBJECTONCOLLISIONENTER_H
#define INC_2DENGINE_C_REMOVEOBJECTONCOLLISIONENTER_H

#include "Component.h"
#include "C_Collidable.h"
#include "ObjectCollection.h"
//scrap this and use collision callback from box2d
class C_RemoveObjectOnCollisionEnter : public Component,public C_Collidable{
public:
    C_RemoveObjectOnCollisionEnter(Object* owner) ;

    void OnCollisionEnter(std::shared_ptr<C_BoxCollider> other) override;
    void OnCollisionExit(std::shared_ptr<C_BoxCollider> other) override;
};


#endif //INC_2DENGINE_C_REMOVEOBJECTONCOLLISIONENTER_H
