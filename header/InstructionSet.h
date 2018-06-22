//
// Created by a_mod on 22.06.2018.
//

#ifndef VM2_0_INSTRUCTIONSET_H
#define VM2_0_INSTRUCTIONSET_H


#include <cstdint>
#include <unordered_map>

#include "State.h"

namespace vm2{

    typedef void(* instruction_t)(vm2::State*);

    class InstructionSet {
    public:
        InstructionSet();
        ~InstructionSet();
    private:
        std::unordered_map<uint8_t, instruction_t>* instructionMap;

    private:
        static void hello(State* state);

    public:
        instruction_t get(uint8_t opt);
    };
}



#endif //VM2_0_INSTRUCTIONSET_H
