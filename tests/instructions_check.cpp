//
// Created by a_mod on 26.06.2018.
//

#include "unit_framework.h"

#include "../header/State.h"
#include "../header/InstructionSet.h"

using namespace vm2;

int unit_readRegisterN(){
    return 0;
}

int unit_writeRegisterN(){
    return 0;
}

int unit_push(){
    std::vector<uint8_t> code ({0xd1, 0x0, 0x0, 0x0, 0x03, 0x01});
    State* state = new State(code);
    InstructionSet instructionSet = InstructionSet();

    instructionSet.get(code[0]).call(state);

    ASSERT_EQUAL(state->readIp(), 0x01);
    ASSERT_EQUAL(state->getStack().peek().isGood(), true);
    ASSERT_EQUAL(state->getStack().pop().get(), 3);

    delete(state);
    return 0;
}

int unit_remove(){
    std::vector<uint8_t> code ({0xd1, 0, 0, 0, 3, 0xd1, 0, 0, 0, 4, 0xd2, 0x01});
    InstructionSet instructionSet = InstructionSet();

    State* state = new vm2::State(code);
    instructionSet.get(state->readIp()).call(state);
    instructionSet.get(state->readIp()).call(state);
    instructionSet.get(state->readIp()).call(state);

    ASSERT_EQUAL(state->readIp(), 0x01);
    ASSERT_EQUAL(state->getStack().peek().isGood(), true);
    ASSERT_EQUAL(state->getStack().pop().get(), 3);

    delete(state);
    return 0;
}

int main(){
    register_test(unit_readRegisterN);
    register_test(unit_writeRegisterN);
    register_test(unit_push);
    register_test(unit_remove);
    start_unit_test();
    end_unit_test();
}