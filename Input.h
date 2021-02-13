//
// Created by root on 27.08.19.
//

#ifndef INC_2DENGINE_INPUT_H
#define INC_2DENGINE_INPUT_H


#include "BitMask.h"

class Input {
public:
    Input();
    enum class Key
    {
        None=0,
        Left =1,
        Right =2,
        Up = 3,
        Down = 4,
        Esc =5,
        U = 6,
        O = 7,
        E = 8,
        F = 9,
    };
    void Update();
    void Lock();
    void Unlock();
    bool IsKeyPressed(Key keycode);
    bool IsKeyDown(Key keycode);
    bool IsKeyUp(Key keycode);

private:
    BitMask thisFrameKeys;
    BitMask lastFrameKeys;
    bool isLocked;
};


#endif //INC_2DENGINE_INPUT_H
