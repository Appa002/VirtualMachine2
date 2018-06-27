//
// Created by a_mod on 27.06.2018.
//

#ifndef VM2_0_STACKOBJECT_H
#define VM2_0_STACKOBJECT_H

#include <cstdint>

namespace vm2 {
    class StackObject {
    public:
        StackObject();
        StackObject(uint32_t val, uint8_t opcode);
        ~StackObject() = default;
    private:
        uint32_t value;
        uint8_t opcode;
        bool good;

    public:
        uint32_t get();
        void set(uint32_t val, uint8_t opcode);
        bool isGood();
        void makeBad();

    };
}


#endif //VM2_0_STACKOBJECT_H
