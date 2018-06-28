//
// Created by a_mod on 19.06.2018.
//

#include <stdexcept>
#include "../header/Page.h"

vm2::Page::Page() {
    data = new uint32_t[1024/4];
    pageSize = 1024/4;
}

vm2::Page::Page(unsigned long size_) {
    data = new uint32_t[size_/4];
    pageSize = size_ / 4;
}

vm2::Page::~Page() {
    delete[] data;
    pageSize = 0;
}

int vm2::Page::writeTo(unsigned long index, uint32_t content) {
    if(index < pageSize)
        data[index] = content;
    else
        return -1;
    return 0;
}

uint32_t vm2::Page::readFrom(unsigned long index) {
    if(index < pageSize)
        return data[index];
    throw std::runtime_error("Index out of range");
}

unsigned long vm2::Page::size() {
    return pageSize;
}


