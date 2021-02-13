//
// Created by root on 06.09.19.
//

#ifndef INC_2DENGINE_S_DRAWABLE_H
#define INC_2DENGINE_S_DRAWABLE_H


#include <vector>
#include "Object.h"
#include "SpriteBatch.h"

class S_Drawable {
public:
    void Add(std::vector<std::shared_ptr<Object>>& object);
    void ProcessRemovals();
    void Draw(Window& window);

private:
    void Add(std::shared_ptr<Object> object);
    void Sort();
    static bool LayerSort(std::shared_ptr<C_Drawable> a, std::shared_ptr<C_Drawable> b);
    std::map<DrawLayer ,std::vector<std::shared_ptr<C_Drawable>>> drawables;

    moony::SpriteBatch batch;


};


#endif //INC_2DENGINE_S_DRAWABLE_H
