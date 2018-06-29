//
// Created by a_mod on 22.06.2018.
//

#ifndef VM2_0_INSTRUCTIONSET_H
#define VM2_0_INSTRUCTIONSET_H


#include <cstdint>
#include <unordered_map>
#include <functional>

#include "State.h"
#include "Instruction.h"
#include "IInstruction.h"

namespace vm2{
    class InstructionSet {
    public:
        InstructionSet();
        ~InstructionSet();
    private:
        std::unordered_map<uint8_t, vm2::IInstruction*> instructionMap;

    private:
        /// Instructions
        static void op_move(State* state);
        static void op_read(State* state);
        static void op_push (State* state);
        static void op_remove (State* state);
        ///
    public:
        vm2::IInstruction* get(uint8_t opt);
    };
}



#endif //VM2_0_INSTRUCTIONSET_H
