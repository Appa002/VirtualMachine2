//
// Created by a_mod on 22.06.2018.
//

#include <iostream>
#include "../header/InstructionSet.h"
#include "../header/SpecialInstructionImplementation.h"


vm2::InstructionSet::InstructionSet() {
    // Register readRegister0...readRegister9 instruction
    for(uint8_t i = 0; i < 10; i++){
        instructionMap.operator[]((uint8_t)0xa0 + i) = vm2::ReadNthRegisterInstruction(i);
    }

    // Register setRegister0...setRegister9 instruction
    for(uint8_t i = 0; i < 10; i++){
        instructionMap.operator[]((uint8_t)0xb0 + i) = vm2::SetNthRegisterInstruction(i);
    }

    instructionMap.insert(std::pair<uint8_t, vm2::Instruction>(0xd1, op_push));
    instructionMap.insert(std::pair<uint8_t, vm2::Instruction>(0xd2, op_remove));
}

vm2::Instruction vm2::InstructionSet::get(uint8_t opt) {
    if(instructionMap.find(opt) == instructionMap.cend())
        throw std::runtime_error("Unknown opt code");
    return instructionMap.at(opt);
}

/// Instructions

void vm2::InstructionSet::op_push(vm2::State *state) {
    uint32_t value = state->peekIp(1);
    value = value << 8 | state->peekIp(2);
    value = value << 16 | state->peekIp(3);
    value = value << 31 | state->peekIp(4);

    state->getStack().push(value, 0xd1);
    state->iterateIp(5);
}

void vm2::InstructionSet::op_remove(vm2::State *state) {
    state->getStack().pop();
    state->iterateIp();
}

///