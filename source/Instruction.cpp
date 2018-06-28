//
// Created by a_mod on 26.06.2018.
//

#include "../header/Instruction.h"

vm2::Instruction::Instruction(std::function<void(vm2::State*)> func) {
    this->func = func;
}

vm2::Instruction::Instruction(void (*func)(vm2::State *)) {
    this->func = std::function<void(vm2::State*)>(func);
}

vm2::Instruction vm2::Instruction::operator()(vm2::State *state) {
    this->func(state);
    return *this;
}

vm2::Instruction vm2::Instruction::call(vm2::State* state) {
    return this->operator()(state);
}

