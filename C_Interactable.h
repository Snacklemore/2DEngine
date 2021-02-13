//
// Created by Nico on 23.09.2020.
//

#ifndef INC_2DENGINE_C_INTERACTABLE_H
#define INC_2DENGINE_C_INTERACTABLE_H
#include "Component.h"
#include "Object.h"
#include "ObjectCollection.h"
#include "C_Animation.h"


class C_Interactable:public Component {
public:
    C_Interactable(Object *owner);
    void Update(float deltaTime) override ;
    void LateUpdate(float deltaTime) override ;
    void Awake() override ;
    void Start() ;
private:
    bool playerIsNear;

};


#endif //INC_2DENGINE_C_INTERACTABLE_H
