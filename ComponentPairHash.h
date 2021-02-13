//
// Created by root on 11.09.19.
//

#ifndef INC_2DENGINE_COMPONENTPAIRHASH_H
#define INC_2DENGINE_COMPONENTPAIRHASH_H


#include <cstddef>

struct ComponentPairHash {

    template <typename T>
    std::size_t operator()(T t) const
    {
        std::size_t x = t.first->owner->instanceID->Get();
        std::size_t y = t.second->owner->instanceID->Get();

        return (x>=y) ? (x * x + x + y) : (y * y + y +x);
    }

};


#endif //INC_2DENGINE_COMPONENTPAIRHASH_H
