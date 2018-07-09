//
// Created by a_mod on 29.06.2018.
//

#include <cstdint>
#include <cmath>
#include <iostream>
#include "../header/maths.h"

class FloatParts{
public:
    explicit FloatParts(uint32_t num) : sign(num >> 31), exponent((num << 1) >> 24), mantissa((num << 9) >> 9) {}

public:
    const uint32_t sign : 1;
    const uint32_t exponent : 8;
    const uint32_t mantissa : 23;
};

uint32_t readNthBit(uint32_t value, uint32_t n){
    value = value >> n;
    value = value & (uint32_t)1;
    return value;
}


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

float vm2::maths::readIEEE754Float(uint32_t num){
    FloatParts parts(num);
    const uint32_t bias = 127;

    /* Calculates the fraction given by the mantissa.
     * */
    double fraction = 0;
    for(uint32_t i = 0; i < 23; i++){
        fraction += readNthBit(num, 22 - i) / pow(2, i + 1);
    }
    /*LaTex of below equation:
     * \( value=(-1)^{sign}*(fraction + 1)*2^{exponent - bias} \)
     * where: sign is the signage of the float
     *        mantissa is the mantissa of the float
     *        exponent is the exponent of the float
     *        bias is a constant, here for single-precision float 127*/

    double value = pow(-1, parts.sign) * (1 + fraction) * pow(2, (int32_t)parts.exponent - (int32_t)bias);


    return static_cast<float>(value);
}

uint32_t vm2::maths::transformToIEEE754Float(float num) {
    static_assert(std::numeric_limits<float>::is_iec559,
              "This code requires IEEE-754 floats");

    // TODO: Make work for compilers not using IEEE 754 Floating point representation.
    return *(uint32_t*)&num;
}
