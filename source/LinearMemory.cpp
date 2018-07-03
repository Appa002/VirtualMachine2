//
// Created by a_mod on 03.07.2018.
//

#include <stdexcept>
#include <cmath>
#include "../header/LinearMemory.h"

vm2::LinearMemory::LinearMemory() {
    pageSize = 0;
    pages = new std::vector<Page *>;
}

vm2::LinearMemory::~LinearMemory() {
    for(auto& page : *pages){
        delete page;
    }
    delete pages;
}

void vm2::LinearMemory::setPageSize(uint32_t newSize) {
    if (this->pageSize != 0)
        throw std::runtime_error("The size of linear memory pages may only be set one time!");
    this->pageSize = newSize;
}

void vm2::LinearMemory::allocPage() {
    if (this->pageSize == 0)
        throw std::runtime_error("The size of linear memory pages has not been set.");

    pages->push_back(new Page(this->pageSize));
}

void vm2::LinearMemory::write(uint32_t address, uint32_t value) {
    if (address >= pages->size() * pageSize)
        throw std::runtime_error("Write address out of range!");

    double numOfPagesRequired = (double)address / pageSize;

    auto pageIndex = static_cast<uint32_t>(floor(numOfPagesRequired));
    uint32_t index = address - pageIndex * pageSize;
    pages->at(pageIndex)->writeTo(index, value);
}

uint32_t vm2::LinearMemory::read(uint32_t address) {
    if (address >= pages->size() * pageSize)
        throw std::runtime_error("Write address out of range!");

    double numOfPagesRequired = (double)address / pageSize;

    auto pageIndex = static_cast<uint32_t>(floor(numOfPagesRequired));
    uint32_t index = address - pageIndex * pageSize;
    return pages->at(pageIndex)->readFrom(index);
}

uint32_t vm2::LinearMemory::getPageSize() {
    return pageSize;
}

