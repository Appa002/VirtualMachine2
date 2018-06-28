//
// Created by a_mod on 22.06.2018.
//

#include "../header/Stack.h"

#include <algorithm>

vm2::Stack::Stack() {
    data = new std::vector<StackObject>();
    data->reserve(1024 / 4);
    std::fill(data->begin(), data->begin() + 1024 / 4, StackObject());
}

void vm2::Stack::push(uint32_t value, uint8_t opcode) {
    data->push_back(StackObject(value, opcode));
}

void vm2::Stack::push(StackObject& value) {
    data->push_back(value);
}

void vm2::Stack::push(StackObject&& value) {
    data->push_back(value);
}

vm2::StackObject vm2::Stack::pop() {
    StackObject object = data->at(data->size() - 1);
    data->pop_back();
    return object;
}

vm2::StackObject vm2::Stack::peek() {
    return data->at(data->size() - 1);
}


void vm2::Stack::write(size_t index, vm2::StackObject value) {
    data->at(index) = value;
}

vm2::StackObject vm2::Stack::read(size_t index) {
    return data->at(index);
}

