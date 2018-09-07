//
// Created by a_mod on 29.06.2018.
//

#include <cstdint>
#include <cmath>
#include <iostream>
#include "../header/maths.h"

uint32_t vm2::maths::manualSignedAdding(uint32_t a, uint32_t b) {
    bool isAPositive = (a & (uint32_t)1 << 31) == 0;
    bool isBPositive = (b & (uint32_t)1 << 31) == 0;
    bool sinageDiffers = isAPositive != isBPositive;

    if(!sinageDiffers){
        if(isAPositive)
            return (a + b) & 0xffffffff >> 1;
        else
            return manualSignedSubtracting(a, b & 0xffffffff >> 1);
    }else{
        if(isAPositive)
            return manualSignedSubtracting(a, b & 0xffffffff >> 1);
        else
            return manualSignedSubtracting(b, a & 0xffffffff >> 1);
    }
}

uint32_t vm2::maths::manualSignedSubtracting(uint32_t a, uint32_t b) {
    bool isAPositive = (a & (uint32_t)1 << 31) == 0;
    bool isBPositive = (b & (uint32_t)1 << 31) == 0;
    bool sinageDiffers = isAPositive != isBPositive;

    if(!sinageDiffers){
        if(!isAPositive)
            return manualSignedAdding(a, b & 0xffffffff >> 1);
        else{
            if(a > b || a == b)
                return (a - b) & 0xffffffff >> 1;
            else if (a < b)
                return (b - a) | (uint32_t)1 << 31;
        }
    }else{
        if(!isAPositive)
            return (a + b) | (uint32_t)1 << 31;
        else
            return (a + b) & 0xffffffff >> 1;
    }
}

uint32_t vm2::maths::manualSignedMultiplication(uint32_t a, uint32_t b){
    bool isAPositive = (a & (uint32_t)1 << 31) == 0;
    bool isBPositive = (b & (uint32_t)1 << 31) == 0;
    bool sinageDiffers = isAPositive != isBPositive;
    uint32_t aValue = a & 0xffffffff >> 1;
    uint32_t bValue = b & 0xffffffff >> 1;

    uint32_t value = aValue * bValue;
    if(sinageDiffers)
        value = value | (uint32_t)1 << 31;
    else
        value = value & 0xffffffff >> 1;
    return value;
}

uint32_t vm2::maths::manualSignedDivision(uint32_t a, uint32_t b){
    bool isAPositive = (a & (uint32_t)1 << 31) == 0;
    bool isBPositive = (b & (uint32_t)1 << 31) == 0;
    bool sinageDiffers = isAPositive != isBPositive;
    uint32_t aValue = a & 0xffffffff >> 1;
    uint32_t bValue = b & 0xffffffff >> 1;

    uint32_t value = aValue / bValue;
    if(sinageDiffers)
        value = value | (uint32_t)1 << 31;
    else
        value = value & 0xffffffff >> 1;
    return value;
}


uint32_t vm2::maths::transformToIEEE754Float(float num) {
    static_assert(std::numeric_limits<float>::is_iec559,
              "This code requires IEEE-754 floats");

    // TODO: Make work for compilers not using IEEE 754 Floating point representation.
    return *(uint32_t*)&num;
}
