//
// Created by a_mod on 26.06.2018.
//

#include "../header/SpecialInstructionImplementation.h"

vm2::ReadNthRegisterInstruction::ReadNthRegisterInstruction(int n) : n(n) {}

vm2::Instruction vm2::ReadNthRegisterInstruction::operator()(vm2::State* state){
    uint32_t storedValue = state->readRegister(n);
    state->getStack().push(storedValue);
    return *this;
}

///////////////////////////////////////////////////////

vm2::SetNthRegisterInstruction::SetNthRegisterInstruction(int n) : n(n){}

vm2::Instruction vm2::SetNthRegisterInstruction::operator()(vm2::State *state) {
    uint32_t valueToWrite = state->getStack().pop();
    state->setRegister((uint32_t)n, valueToWrite);
    return *this;
}
