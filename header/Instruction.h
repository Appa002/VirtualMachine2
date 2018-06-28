//
// Created by a_mod on 26.06.2018.
//

#ifndef VM2_0_INSTRUCTION_H
#define VM2_0_INSTRUCTION_H

#include <functional>
#include "State.h"
#include "IInstruction.h"

namespace vm2{
    class Instruction : public IInstruction{
    public:
        Instruction() = default;
        Instruction(std::function<void(vm2::State*)> func);
        Instruction(void(* func)(vm2::State*));
    private:
        std::function<void(vm2::State*)> func;

    public:
        void operator()(vm2::State* state) override;
        void call(vm2::State* state) override;
    };
}


#endif //VM2_0_INSTRUCTION_H
