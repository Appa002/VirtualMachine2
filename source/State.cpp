//
// Created by a_mod on 19.06.2018.
//

#include "../header/State.h"

#include <fstream>
#include <iterator>

vm2::State::State(std::string filePath) {
    loadFile(filePath);
    ip = &(byteCode[0]);
    stack = Stack();
    registers.reserve(10);
    linearMemory.reserve(5);

    linearMemory.push_back(new Page());
}


vm2::State::State(std::vector<uint8_t> code) {
    byteCode = code;
    ip = &(byteCode[0]);
    stack = Stack();
    registers.reserve(10);
    linearMemory.reserve(5);

    linearMemory.push_back(new Page());
}



void vm2::State::loadFile(std::string &filePath) {
    std::ifstream file;
    file.open(filePath, std::ios::binary | std::ios::ate);
    if(!file.is_open())
        throw std::runtime_error("File could not be opened!");

    size_t size = (size_t)file.tellg();
    file.seekg(std::ios::beg);

    ip = new uint8_t[size + 1];
    ip[size] = '\0';

    byteCode.reserve(size);
    byteCode.insert(byteCode.begin(),
                    std::istream_iterator<uint8_t>(file),
                    std::istream_iterator<uint8_t>());

    file.close();
}

void vm2::State::iterateIp(size_t amount) {
    if(amount < byteCode.size())
        ip += amount;
    else
        throw std::runtime_error("New instruction pointer location out of range");
}

void vm2::State::setIp(size_t index) {
    if(byteCode.size() < index)
        ip = &byteCode[index];
    else
        throw std::runtime_error("New instruction pointer location out of range");
}

uint8_t vm2::State::readIp() {
    return *ip;
}

uint8_t vm2::State::peekIp(int offset) {
    if((ip - &byteCode[0]) + offset < 0 || (ip - &byteCode[0]) + offset > byteCode.size())
        throw std::runtime_error("Peeking ip at undefined address!");
    return *(ip + offset);
}

void vm2::State::setRegister(size_t number, uint32_t value) {
    if(number <= 9 && number >= 0)
        registers[number] = value;
    else
        throw std::runtime_error("Registers are numbered from to 0...9");
}

uint32_t vm2::State::readRegister(size_t number) {
    if(number <= 9 && number >= 0)
        return registers[number];
    else
        throw std::runtime_error("Registers are numbered from to 0...9");
}

void vm2::State::writeMemory(size_t address, uint32_t value) {
    size_t pagesCombinedSize = 0;
    for(auto& page : linearMemory){
        pagesCombinedSize += page->size();
        if(address < pagesCombinedSize){
            page->writeTo(pagesCombinedSize - address, value);
            return;
        }
    }

    linearMemory.push_back(
            new Page(linearMemory.at(linearMemory.size() - 1)->size() * 2));
    writeMemory(address, value);
}

uint32_t vm2::State::readMemory(size_t address) {
    size_t pagesCombinedSize = 0;
    for(auto& page : linearMemory){
        pagesCombinedSize += page->size();
        if(address < pagesCombinedSize)
            return page->readFrom(pagesCombinedSize - address);

    }
}

vm2::Stack vm2::State::getStack() {
    return stack;
}

vm2::State::~State() {
    for(auto* it : this->linearMemory){
        delete it;
    }
}



