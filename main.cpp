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

    while (state->readIp() != 0x11){
        instructionSet->get(state->readIp())(state);
    }

    delete state;
    delete instructionSet;

    return 0;
}