//
// Created by a_mod on 19.06.2018.
//

#ifndef VM2_0_PAGE_H
#define VM2_0_PAGE_H

#include <cstdint>

namespace vm2{
    class Page {
    public:
        Page();
        explicit Page(unsigned long sizeInByte_);
        ~Page();

    private:
        uint32_t* data;
        unsigned long pageSize;

    public:
        int writeTo(unsigned long index, uint32_t content);
        uint32_t readFrom(unsigned long index);
        unsigned long size();
        int destroy();
    };
}



#endif //VM2_0_PAGE_H
