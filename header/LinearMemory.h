//
// Created by a_mod on 03.07.2018.
//

#ifndef VM2_0_LINEARMEMORY_H
#define VM2_0_LINEARMEMORY_H

#include <cstdint>
#include <vector>
#include "Page.h"

namespace vm2{
    class LinearMemory {
    public:
        LinearMemory();
        ~LinearMemory();

    private:
        uint32_t pageSize;
        std::vector<vm2::Page*>* pages;

    public:
        void setPageSize(uint32_t newSize);
        uint32_t getPageSize();
        void allocPage();
        void write(uint32_t address, uint32_t value);
        uint32_t read(uint32_t address);
    };
}


#endif //VM2_0_LINEARMEMORY_H
