//
// Created by a_mod on 29.06.2018.
//

#ifndef VM2_0_MATHS_H
#define VM2_0_MATHS_H

#include <cstdint>

namespace vm2::maths{
    uint32_t manualSignedAdding(uint32_t a, uint32_t b);
    uint32_t manualSignedSubtracting(uint32_t a, uint32_t b);
    uint32_t manualSignedMultiplication(uint32_t a, uint32_t b);
    uint32_t manualSignedDivision(uint32_t a, uint32_t b);

    float readIEEE754Float(uint32_t num);
}

#endif //VM2_0_MATHS_H
