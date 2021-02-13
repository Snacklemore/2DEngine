//
// Created by Nico on 13.02.2021.
//

#ifndef INC_2DENGINE_C_RAYCASTER_H
#define INC_2DENGINE_C_RAYCASTER_H

#include "Component.h"
#include "Object.h"
#include "ObjectCollection.h"
#include "C_Animation.h"


class C_RayCaster :public Component {
public:
    C_RayCaster(Object *owner);
    void Update(float deltaTime) override ;
    void LateUpdate(float deltaTime) override ;
    void Awake() override ;
    void Start() ;
};


#endif //INC_2DENGINE_C_RAYCASTER_H
