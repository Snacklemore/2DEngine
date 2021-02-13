//
// Created by root on 06.09.19.
//

#ifndef INC_2DENGINE_C_INSTANCEID_H
#define INC_2DENGINE_C_INSTANCEID_H

#include "Component.h"
class C_InstanceID: public Component {
public:
    C_InstanceID(Object* owner);
    ~C_InstanceID();

    unsigned int Get() const;

private:
    static unsigned int count;
    unsigned int id;

};


#endif //INC_2DENGINE_C_INSTANCEID_H
