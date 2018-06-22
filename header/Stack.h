//
// Created by a_mod on 22.06.2018.
//

#ifndef VM2_0_STACK_H
#define VM2_0_STACK_H

#include <vector>
#include <cstdint>

namespace vm2{
    class Stack {
    public:
        Stack();
        ~Stack();

    private:
        std::vector<uint32_t>* data;

    public:
        void push(uint32_t value);
        uint32_t pop();

        void write(size_t index, uint32_t value);
        uint32_t read(size_t index);
    };
}



#endif //VM2_0_STACK_H
