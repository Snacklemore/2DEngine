//
// Created by root on 25.08.19.
//

#ifndef INC_2DENGINE_BITMASK_H
#define INC_2DENGINE_BITMASK_H


#include <cstdint>

class BitMask {
public:
    BitMask();
    BitMask(uint32_t bits);

    void SetMask(BitMask& other);
    uint32_t GetMask() const;
    bool GetBit(int pos) const;
    //sets bit at pos to 0 or 1
    void SetBit(int pos, bool on);
    //sets bit at pos to 1
    void SetBit(int pos);
    void ClearBit(int pos);
    //sets all bits to 0
    void Clear();

private:
    uint32_t bits;


};


#endif //INC_2DENGINE_BITMASK_H
