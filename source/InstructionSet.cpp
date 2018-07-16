//
// Created by a_mod on 22.06.2018.
//

#include <iostream>
#include <cmath>
#include "../header/InstructionSet.h"
#include "../header/SpecialInstructionImplementation.h"
#include "../header/maths.h"


vm2::InstructionSet::InstructionSet() {
    instructionMapArray.fill(nullptr);

    // Register readRegister0...readRegister9 instruction
    for(uint8_t i = 0; i < 10; i++){
        instructionMapArray.at(0xa0 + i) = new vm2::ReadNthRegisterInstruction(i);
    }

    // Register setRegister0...setRegister9 instruction
    for(uint8_t i = 0; i < 10; i++){
        instructionMapArray.at(0xb0 + i) = new vm2::SetNthRegisterInstruction(i);
    }

    instructionMapArray.at(0xc0) = new Instruction(op_setSize);
    instructionMapArray.at(0xc1) = new Instruction(op_move);
    instructionMapArray.at(0xc2) = new Instruction(op_read);
    instructionMapArray.at(0xc3) = new Instruction(op_alloc);

    instructionMapArray.at(0xd0) = new Instruction(op_push);
    instructionMapArray.at(0xd1) = new Instruction(op_remove);

    instructionMapArray.at(0xe0) = new Instruction(op_uadd);
    instructionMapArray.at(0xe1) = new Instruction(op_sadd);
    instructionMapArray.at(0xe2) = new Instruction(op_fadd);

    instructionMapArray.at(0xe3) = new Instruction(op_usub);
    instructionMapArray.at(0xe4) = new Instruction(op_ssub);
    instructionMapArray.at(0xe5) = new Instruction(op_fsub);

    instructionMapArray.at(0xe6) = new Instruction(op_umult);
    instructionMapArray.at(0xe7) = new Instruction(op_smult);
    instructionMapArray.at(0xe8) = new Instruction(op_fmult);

    instructionMapArray.at(0xe9) = new Instruction(op_udiv);
    instructionMapArray.at(0xea) = new Instruction(op_sdiv);
    instructionMapArray.at(0xeb) = new Instruction(op_fdiv);

    instructionMapArray.at(0xec) = new Instruction(op_utof);
    instructionMapArray.at(0xed) = new Instruction(op_stof);
    instructionMapArray.at(0xee) = new Instruction(op_abs);

    instructionMapArray.at(0xef) = new Instruction(op_ucmp);
    instructionMapArray.at(0xf0) = new Instruction(op_scmp);
    instructionMapArray.at(0xf1) = new Instruction(op_fcmp);

    instructionMapArray.at(0x01) = new Instruction(op_jmp);
    instructionMapArray.at(0x02) = new Instruction(op_jless);
    instructionMapArray.at(0x03) = new Instruction(op_jgreater);
    instructionMapArray.at(0x04) = new Instruction(op_jequal);
    instructionMapArray.at(0x05) = new Instruction(op_jNequal);

    instructionMapArray.at(0x06) = new Instruction(op_call);
    instructionMapArray.at(0x07) = new Instruction(op_return);

    instructionMapArray.at(0x10) = new Instruction(op_int);
    instructionMapArray.at(0x12) = new Instruction(op_noop);
    instructionMapArray.at(0x13) = new Instruction(op_out);
}

vm2::InstructionSet::~InstructionSet() {
    for(auto it : this->instructionMapArray){
        if(it != nullptr)
            delete it;
    }
}

vm2::IInstruction* vm2::InstructionSet::get(uint8_t opt) {
    if(instructionMapArray.at(opt) == nullptr)
        throw std::runtime_error("Unknown opcode");
    return instructionMapArray.at(opt);
}

/// Instructions

void vm2::InstructionSet::op_setSize(vm2::State *state) {
    StackObject argument = state->getStack()->pop();
    if(!argument.isGood())
        throw std::runtime_error("setSize called with none good argument!");

    state->getLinearMemory()->setPageSize(argument.getValue());
    state->iterateIp();
}

void vm2::InstructionSet::op_push(vm2::State *state) {
    uint32_t value = 0;
    value = value | (state->peekIp(1) << 24);
    value = value | (state->peekIp(2) << 16);
    value = value | (state->peekIp(3) << 8);
    value = value | (state->peekIp(4));

    state->getStack()->push(value, 0xd0);
    state->iterateIp(5);
}

void vm2::InstructionSet::op_remove(vm2::State *state) {
    state->getStack()->pop();
    state->iterateIp();
}

void vm2::InstructionSet::op_move(vm2::State *state) {
    StackObject addressArgument = state->getStack()->pop();
    StackObject valueArgument = state->getStack()->pop();
    if(!valueArgument.isGood() || !addressArgument.isGood())
        throw std::runtime_error("Move has received an none good argument.");

    state->getLinearMemory()->write(addressArgument.getValue(), valueArgument.getValue());
    state->iterateIp();
}

void vm2::InstructionSet::op_read(vm2::State *state) {
    StackObject addressArgument = state->getStack()->pop();
    if(!addressArgument.isGood())
        throw std::runtime_error("Read has received an none good argument.");
    uint32_t readValue = state->getLinearMemory()->read(addressArgument.getValue());

    state->getStack()->push(readValue, 0xc1);
    state->iterateIp();
}

void vm2::InstructionSet::op_alloc(vm2::State *state) {
    state->getLinearMemory()->allocPage();
    state->iterateIp();
}


void vm2::InstructionSet::op_uadd(vm2::State *state) {
    StackObject a = state->getStack()->pop();
    StackObject b = state->getStack()->pop();

    if(!a.isGood() || !b.isGood())
        throw std::runtime_error("uadd has received an none good argument.");

    uint32_t value = a.getValue() + b.getValue();
    state->getStack()->push(value, 0xe0);

    state->iterateIp();
}

void vm2::InstructionSet::op_sadd(vm2::State *state) {
    StackObject b = state->getStack()->pop();
    StackObject a = state->getStack()->pop();

    if(!a.isGood() || !b.isGood())
        throw std::runtime_error("sadd has received an none good argument.");

    uint32_t value = maths::manualSignedAdding(a.getValue(), b.getValue());
    state->getStack()->push(value, 0xe1);
    state->iterateIp();
}

void vm2::InstructionSet::op_fadd(vm2::State *state) {
    StackObject b = state->getStack()->pop();
    StackObject a = state->getStack()->pop();

    if(!a.isGood() || !b.isGood())
        throw std::runtime_error("sadd has received an none good argument.");

    float aAsFloat = maths::readIEEE754Float(a.getValue());
    float bAsFloat = maths::readIEEE754Float(b.getValue());

    float result = aAsFloat + bAsFloat;
    state->getStack()->push(maths::transformToIEEE754Float(result), 0xe2);

    state->iterateIp();
}

void vm2::InstructionSet::op_usub(vm2::State *state) {
    StackObject b = state->getStack()->pop();
    StackObject a = state->getStack()->pop();

    if(!a.isGood() || !b.isGood())
        throw std::runtime_error("usub has received an none good argument.");

   uint32_t value = a.getValue() - b.getValue();
   state->getStack()->push(value, 0xe3);
   state->iterateIp();
}

void vm2::InstructionSet::op_ssub(vm2::State *state) {
    StackObject b = state->getStack()->pop();
    StackObject a = state->getStack()->pop();

    if(!a.isGood() || !b.isGood())
        throw std::runtime_error("ssub has received an none good argument.");

    uint32_t value = maths::manualSignedSubtracting(a.getValue(), b.getValue());
    state->getStack()->push(value, 0xe4);
    state->iterateIp();
}

void vm2::InstructionSet::op_fsub(vm2::State *state) {
    StackObject b = state->getStack()->pop();
    StackObject a = state->getStack()->pop();

    if(!a.isGood() || !b.isGood())
        throw std::runtime_error("sadd has received an none good argument.");

    float aAsFloat = maths::readIEEE754Float(a.getValue());
    float bAsFloat = maths::readIEEE754Float(b.getValue());

    float result = aAsFloat - bAsFloat;
    state->getStack()->push(maths::transformToIEEE754Float(result), 0xe5);

    state->iterateIp();
}

void vm2::InstructionSet::op_umult(vm2::State *state) {
    StackObject b = state->getStack()->pop();
    StackObject a = state->getStack()->pop();

    if(!a.isGood() || !b.isGood())
        throw std::runtime_error("umult has received an none good argument.");

    uint32_t value = a.getValue() * b.getValue();
    state->getStack()->push(value, 0xe6);
    state->iterateIp();
}

void vm2::InstructionSet::op_smult(vm2::State *state) {
    StackObject b = state->getStack()->pop();
    StackObject a = state->getStack()->pop();

    if(!a.isGood() || !b.isGood())
        throw std::runtime_error("ssub has received an none good argument.");

    uint32_t value = maths::manualSignedMultiplication(a.getValue(), b.getValue());
    state->getStack()->push(value, 0xe7);
    state->iterateIp();
}

void vm2::InstructionSet::op_fmult(vm2::State *state) {
    StackObject b = state->getStack()->pop();
    StackObject a = state->getStack()->pop();

    if(!a.isGood() || !b.isGood())
        throw std::runtime_error("fmult has received an none good argument.");

    float aAsFloat = maths::readIEEE754Float(a.getValue());
    float bAsFloat = maths::readIEEE754Float(b.getValue());

    float result = aAsFloat * bAsFloat;
    state->getStack()->push(maths::transformToIEEE754Float(result), 0xe8);

    state->iterateIp();
}

void vm2::InstructionSet::op_udiv(vm2::State *state) {
    StackObject b = state->getStack()->pop();
    StackObject a = state->getStack()->pop();

    if(!a.isGood() || !b.isGood())
        throw std::runtime_error("udiv has received an none good argument.");
    uint32_t value = a.getValue() / b.getValue();
    state->getStack()->push(value, 0xe9);
    state->iterateIp();
}

void vm2::InstructionSet::op_sdiv(vm2::State *state) {
    StackObject b = state->getStack()->pop();
    StackObject a = state->getStack()->pop();

    if(!a.isGood() || !b.isGood())
        throw std::runtime_error("ssub has received an none good argument.");
    uint32_t value = maths::manualSignedDivision(a.getValue(), b.getValue());
    state->getStack()->push(value, 0xea);
    state->iterateIp();
}

void vm2::InstructionSet::op_fdiv(vm2::State *state) {
    StackObject b = state->getStack()->pop();
    StackObject a = state->getStack()->pop();

    if(!a.isGood() || !b.isGood())
        throw std::runtime_error("fdiv has received an none good argument.");

    float aAsFloat = maths::readIEEE754Float(a.getValue());
    float bAsFloat = maths::readIEEE754Float(b.getValue());

    float result = aAsFloat / bAsFloat;
    state->getStack()->push(maths::transformToIEEE754Float(result), 0xeb);

    state->iterateIp();
}

void vm2::InstructionSet::op_utof(vm2::State *state) {
    StackObject a = state->getStack()->pop();

    if(!a.isGood())
        throw std::runtime_error("utof has received an none good argument.");


    float result = (float)a.getValue();
    state->getStack()->push(maths::transformToIEEE754Float(result), 0xec);

    state->iterateIp();
}

void vm2::InstructionSet::op_stof(vm2::State *state) {
    StackObject a = state->getStack()->pop();

    if(!a.isGood())
        throw std::runtime_error("stof has received an none good argument.");


    float result = (float)(a.getValue() & 0x7FFFFFFF);
    if(a.getValue() >> 31 == 1)
        result = -1 * result;

    state->getStack()->push(maths::transformToIEEE754Float(result), 0xed);

    state->iterateIp();
}

void vm2::InstructionSet::op_abs(vm2::State *state) {
    StackObject arg = state->getStack()->pop();
    if(!arg.isGood())
        throw std::runtime_error("abs called with none good value!");

    uint32_t value = arg.getValue() & 0xffffffff >> 1;
    state->getStack()->push(value, 0xee);
    state->iterateIp();
}

void vm2::InstructionSet::op_ucmp(vm2::State *state) {
    StackObject b = state->getStack()->pop();
    StackObject a = state->getStack()->pop();
    if(!a.isGood() || !b.isGood())
        throw std::runtime_error("ucmp has received an none good argument.");

    uint32_t flag = 0;
    if(a.getValue() == b.getValue())
        flag = 0;
    else if (a.getValue() < b.getValue())
        flag = 1;
    else if(a.getValue() > b.getValue())
        flag = 2;
    state->getStack()->push(flag, 0xef);
    state->iterateIp();
}

void vm2::InstructionSet::op_scmp(vm2::State *state) {
    StackObject b = state->getStack()->pop();
    StackObject a = state->getStack()->pop();
    if(!a.isGood() || !b.isGood())
        throw std::runtime_error("scmp has received none good argument.");

    uint32_t flag = maths::manualSignedSubtracting(a.getValue(), b.getValue());
    if(flag == 0) // arg1 == arg2
        state->getStack()->push(flag, 0xf0);
    else {
        if ((flag & (uint32_t) 1 << 31) == 0) // has the subtraction yield a positive number?
            flag = 2; // if yes => arg1 > arg2
        else // the subtraction yielded a negative number
            flag = 1; // => arg1 < arg2
        state->getStack()->push(flag, 0xf0);
    }
    state->iterateIp();
}

void vm2::InstructionSet::op_fcmp(vm2::State *state) {
    StackObject b = state->getStack()->pop();
    StackObject a = state->getStack()->pop();

    if (!a.isGood() || !b.isGood())
        throw std::runtime_error("fcmp has received an none good argument.");

    float aAsFloat = maths::readIEEE754Float(a.getValue());
    float bAsFloat = maths::readIEEE754Float(b.getValue());

    float testResult = aAsFloat - bAsFloat;
    uint32_t flag = 0;
    if(testResult == 0) // arg1 == arg2
        state->getStack()->push(flag, 0xf1);
    else {
        if (testResult > 0)
            flag = 2; // if yes => arg1 > arg2
        else // the subtraction yielded a negative number
            flag = 1; // => arg1 < arg2
        state->getStack()->push(flag, 0xf1);
    }

    state->iterateIp();
}

void vm2::InstructionSet::op_jmp(vm2::State *state) {
    StackObject address = state->getStack()->pop();
    if(!address.isGood())
        throw std::runtime_error("jmp received none good argument!");

    state->setIp(address.getValue());
}

void vm2::InstructionSet::op_jless(vm2::State *state) {
    StackObject address = state->getStack()->pop();
    StackObject flag = state->getStack()->pop();

    if(!address.isGood() || !flag.isGood())
        throw std::runtime_error("jless received none good argument!");

    if(flag.getValue() == 1)
        state->setIp(address.getValue());
    else
        state->iterateIp();
}

void vm2::InstructionSet::op_jgreater(vm2::State *state) {
    StackObject address = state->getStack()->pop();
    StackObject flag = state->getStack()->pop();

    if(!address.isGood() || !flag.isGood())
        throw std::runtime_error("jgreater received none good argument!");

    if(flag.getValue() == 2)
        state->setIp(address.getValue());
    else
        state->iterateIp();
}

void vm2::InstructionSet::op_jequal(vm2::State *state) {
    StackObject address = state->getStack()->pop();
    StackObject flag = state->getStack()->pop();

    if(!address.isGood() || !flag.isGood())
        throw std::runtime_error("jequal received none good argument!");

    if(flag.getValue() == 0)
        state->setIp(address.getValue());
    else
        state->iterateIp();

}

void vm2::InstructionSet::op_jNequal(vm2::State *state) {
    StackObject address = state->getStack()->pop();
    StackObject flag = state->getStack()->pop();

    if(!address.isGood() || !flag.isGood())
        throw std::runtime_error("jNequal received none good argument!");

    if(flag.getValue() != 0)
        state->setIp(address.getValue());
    else
        state->iterateIp();

}

void vm2::InstructionSet::op_call(vm2::State *state) {
    StackObject address = state->getStack()->pop();
    if(!address.isGood())
        throw std::runtime_error("call received none good argument!");

    uint32_t myAddress = state->getIpIndex();
    state->getStack()->push(myAddress, 0x06);
    state->setIp(address.getValue());
}

void vm2::InstructionSet::op_return(vm2::State *state) {
    uint32_t i = 1;
    StackObject obj;
    while(true){
        obj = state->getStack()->peek(i);
        if(obj.getOpcode() == 0x06 && obj.isGood())
            break;
        i++;
   }
   state->setIp(obj.getValue());
}

void vm2::InstructionSet::op_int(vm2::State *state) {
    // Not sure what interrupts, if any, will exist.
    state->iterateIp();
}

void vm2::InstructionSet::op_noop(vm2::State *state) {
    state->iterateIp();
}

void vm2::InstructionSet::op_out(vm2::State *state) {
    StackObject arg = state->getStack()->pop();
    if(!arg.isGood())
        throw std::runtime_error("out received invalid argument.");

    std::cout << std::to_string(arg.getValue()) << " ";

    state->iterateIp();
}

///