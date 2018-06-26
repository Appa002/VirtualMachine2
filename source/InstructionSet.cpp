//
// Created by a_mod on 22.06.2018.
//

#include <iostream>
#include "../header/InstructionSet.h"
#include "../header/SpecialInstructionImplementation.h"


vm2::InstructionSet::InstructionSet() {
    // Register readRegister0...readRegister9 instruction
    for(uint8_t i = 0; i < 10; i++){
        instructionMap->operator[]((uint8_t)0xa0 + i) = vm2::ReadNthRegisterInstruction(i);
    }

    // Register setRegister0...setRegister9 instruction
    for(uint8_t i = 0; i < 10; i++){
        instructionMap->operator[]((uint8_t)0xb0 + i) = vm2::SetNthRegisterInstruction(i);
    }
}


vm2::InstructionSet::~InstructionSet() {
    delete instructionMap;
}

vm2::Instruction vm2::InstructionSet::get(uint8_t opt) {
    if(instructionMap->find(opt) == instructionMap->cend())
        throw std::runtime_error("Unknown opt code");
    return instructionMap->at(opt);
}

