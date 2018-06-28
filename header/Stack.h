//
// Created by a_mod on 22.06.2018.
//

#ifndef VM2_0_STACK_H
#define VM2_0_STACK_H

#include <vector>
#include <cstdint>

#include "StackObject.h"

namespace vm2{
    class Stack {
    public:
        Stack();
        ~Stack() = default;

    private:
        std::vector<vm2::StackObject>* data;

    public:
        void push(uint32_t value, uint8_t opcode);
        void push(StackObject& stackObject);
        void push(StackObject&& stackObject);

        StackObject peek();
        StackObject pop();

        void write(size_t index, StackObject value);
        StackObject read(size_t index);
    };
}



#endif //VM2_0_STACK_H
