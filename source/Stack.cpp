//
// Created by a_mod on 22.06.2018.
//

#include "../header/Stack.h"

vm2::Stack::Stack() {
    data = new std::vector<uint32_t>();

    data->reserve(1024 / 4);
}

vm2::Stack::~Stack() {
    delete data;
}

void vm2::Stack::push(uint32_t value) {
    data->push_back(value);
}

uint32_t vm2::Stack::pop() {
    return data->at(data->size() - 1);
}

void vm2::Stack::write(size_t index, uint32_t value) {
    data->at(index) = value;
}

uint32_t vm2::Stack::read(size_t index) {
    return data->at(index);
}
