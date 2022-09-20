//
// Created by a_mod on 29.06.2018.
//

#ifndef VM2_0_MATHS_H
#define VM2_0_MATHS_H

#include <cstdint>

namespace  vm2::maths::detail{
    class FloatParts{
    public:
        explicit FloatParts(uint32_t num) : sign(num >> 31), exponent((num << 1) >> 24), mantissa((num << 9) >> 9) {}

    public:
        const uint32_t sign : 1;
        const uint32_t exponent : 8;
        const uint32_t mantissa : 23;
    };
}

namespace vm2::maths{
    uint32_t manualSignedAdding(uint32_t a, uint32_t b);
    uint32_t manualSignedSubtracting(uint32_t a, uint32_t b);
    uint32_t manualSignedMultiplication(uint32_t a, uint32_t b);
    uint32_t manualSignedDivision(uint32_t a, uint32_t b);

    template <typename T = float>
    auto readIEEE754Float(uint32_t num) -> typename std::enable_if<std::numeric_limits<T>::is_iec559, float>::type
    {
    return *(float*)&num;
    }

    template <typename T = float>
    auto readIEEE754Float(uint32_t num) -> typename std::enable_if<!std::numeric_limits<T>::is_iec559, float>::type{
        auto readNthBit = [](uint32_t value, uint32_t n) -> uint32_t {
            value = value >> n;
            value = value & (uint32_t)1;
            return value;
        };

        detail::FloatParts parts(num);
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
    };

    uint32_t transformToIEEE754Float(float num);

}

#endif //VM2_0_MATHS_H
