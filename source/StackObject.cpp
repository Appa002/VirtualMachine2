//
// Created by a_mod on 27.06.2018.
//

#include "../header/StackObject.h"

vm2::StackObject::StackObject(uint32_t val, uint8_t opcode) {
    set(val, opcode);
}

vm2::StackObject::StackObject() : value(0), opcode(0), good(false) {}

uint32_t vm2::StackObject::get() {
    return this->value;
}

void vm2::StackObject::set(uint32_t val, uint8_t opcode) {
    this->value = val;
    this->opcode = opcode;
    this->good = true;
}

bool vm2::StackObject::isGood() {
    return this->good;
}

void vm2::StackObject::makeBad() {
    this->good = false;
}
