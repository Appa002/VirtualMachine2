//
// Created by a_mod on 26.06.2018.
//

#ifndef VM2_0_SPECIALINSTRUCTIONIMPLEMENTATION_H
#define VM2_0_SPECIALINSTRUCTIONIMPLEMENTATION_H

#include "Instruction.h"
#include "State.h"
#include "Stack.h"

namespace vm2 {
    class ReadNthRegisterInstruction : public Instruction {
    public:
        ReadNthRegisterInstruction() = delete;

        ReadNthRegisterInstruction(int n);

    private:
        int n = 0;

    public:
        Instruction operator()(vm2::State *state) override;
    };

    ///////////////////////////////////////////////////////
    class SetNthRegisterInstruction : public Instruction {
    public:
        SetNthRegisterInstruction() = delete;

        SetNthRegisterInstruction(int n);

    private:
        const int n = 0;

    public:
        Instruction operator()(vm2::State *state) override;
    };
}

#endif //VM2_0_SPECIALINSTRUCTIONIMPLEMENTATION_H
