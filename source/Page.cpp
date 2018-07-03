//
// Created by a_mod on 19.06.2018.
//

#include <stdexcept>
#include "../header/Page.h"

vm2::Page::Page(unsigned long size_) {
    data = new uint32_t[size_];
    pageSize = size_;
}

vm2::Page::~Page() {
    delete[] data;
    pageSize = 0;
}

void vm2::Page::writeTo(unsigned long index, uint32_t content) {
    if(index >= pageSize)
        throw std::runtime_error("The index to write to does not exist on this page.");
    data[index] = content;
}

uint32_t vm2::Page::readFrom(unsigned long index) {
    if(index < pageSize)
        return data[index];
    throw std::runtime_error("Index out of range");
}

unsigned long vm2::Page::size() {
    return pageSize;
}


