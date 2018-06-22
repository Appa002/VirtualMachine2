//
// Created by a_mod on 22.06.2018.
//

#include <iostream>
#include "../header/InstructionSet.h"

vm2::InstructionSet::InstructionSet() {
    instructionMap->operator[]('a') = hello;
}


vm2::InstructionSet::~InstructionSet() {
    delete instructionMap;
}

vm2::instruction_t vm2::InstructionSet::get(uint8_t opt) {
    if(instructionMap->find(opt) == instructionMap->cend())
        throw std::runtime_error("Unknown opt code");
    return instructionMap->at(opt);
}

void vm2::InstructionSet::hello(vm2::State *state) {
    std::cout << "Hello, World!" << std::endl;
    state->iterateIp();
}



