#include <iostream>

#include "header/State.h"
#include "header/InstructionSet.h"
#include "header/Logger.h"

using namespace vm2;

void usage(){
    std::cout << "Usage: vm2 [file]" << std::endl;
}

int main(int argc, char** argv) {
    if(argc < 2){
        usage();
        return -1;
    }

    State* state = new State(argv[1]);
    InstructionSet* instructionSet = new InstructionSet();

    for(size_t i = 2; i < argc; i++){
        int num = std::stoi(argv[i]);
        uint32_t value = *(uint32_t*)&num;
        value &= 0x7FFF;
        if(num < 0)
            value |= 1 << 31;

        state->getStack()->push(value, 0x00);
    }

    state->getStack()->push((uint32_t)argc, 0x00);

    while (state->readIp() != 0x11){
        instructionSet->get(state->readIp())->call(state);
    }

    delete state;
    delete instructionSet;

    return 0;
}