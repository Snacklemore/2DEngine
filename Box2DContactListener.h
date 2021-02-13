//
// Created by root on 03.05.20.
//

#ifndef INC_2DENGINE_BOX2DCONTACTLISTENER_H
#define INC_2DENGINE_BOX2DCONTACTLISTENER_H


#include "Component.h"
#include "C_Collidable.h"
#include "Object.h"
class Box2DContactListener : public b2ContactListener{

    void BeginContact(b2Contact* contact);

    // Called when two fixtures cease to touch
    void EndContact(b2Contact* contact) ;

};


#endif //INC_2DENGINE_BOX2DCONTACTLISTENER_H
