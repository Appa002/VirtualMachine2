//
// Created by a_mod on 28.06.2018.
//

#ifndef VM2_0_IINSTRUCTION_H
#define VM2_0_IINSTRUCTION_H

#include "Instruction.h"

namespace vm2{
    class IInstruction {
    public:
        IInstruction() = default;

    private:
    public:
        virtual void operator()(vm2::State* state) = 0;
        virtual void call(vm2::State* state) = 0;
    };
}


#endif //VM2_0_IINSTRUCTION_H
