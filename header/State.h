//
// Created by a_mod on 19.06.2018.
//

#ifndef VM2_0_STATE_H
#define VM2_0_STATE_H

#include <cstdint>
#include <vector>
#include <string>

#include "Page.h"
#include "Stack.h"

namespace vm2{
    class State {
    public:
        State() = delete;
        explicit State(std::string filePath);
        explicit State(std::vector<uint8_t> code);

    private:
        uint8_t* ip;
        std::vector<uint8_t> byteCode;
        std::vector<uint32_t> registers;
        Stack stack;
        std::vector<Page> linearMemory;

    private:
        void loadFile(std::string& filePath);

    public:
        void iterateIp(size_t amount = 1);
        void setIp(size_t index);
        uint8_t readIp();

        void setRegister(size_t number, uint32_t value);
        uint32_t readRegister(size_t number);

        void writeMemory(size_t address, uint32_t value);
        uint32_t readMemory(size_t address);

        Stack getStack();
    };
}



#endif //VM2_0_STATE_H
