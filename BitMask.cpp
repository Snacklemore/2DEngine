//
// Created by root on 25.08.19.
//

#include "BitMask.h"

BitMask::BitMask() : bits(0){

}

void BitMask::SetMask(BitMask &other) {
    bits = other.GetMask();

}

uint32_t BitMask::GetMask() const {
    return bits;
}

bool BitMask::GetBit(int pos) const {
    return (bits & (1 << pos)) != 0;}

void BitMask::SetBit(int pos, bool on) {
    if (on)
        SetBit(pos);
    else
        ClearBit(pos);
}

void BitMask::SetBit(int pos) {
    bits = bits | 1 << pos;

}

void BitMask::ClearBit(int pos) {
    bits = bits & ~(1 << pos);

}

void BitMask::Clear() {
    bits = 0;

}

BitMask::BitMask(uint32_t bits):bits(bits) {

}
