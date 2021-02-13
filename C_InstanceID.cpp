//
// Created by root on 06.09.19.
//

#include "C_InstanceID.h"

unsigned int C_InstanceID::count = 0;
C_InstanceID::C_InstanceID(Object *owner) :Component(owner),id(count++) {

}

C_InstanceID::~C_InstanceID() {

}

unsigned int C_InstanceID::Get() const {
    return id;

}
