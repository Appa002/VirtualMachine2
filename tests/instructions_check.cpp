//
// Created by a_mod on 26.06.2018.
//

#include "unit_framework.h"

#include "../header/State.h"

using namespace vm2;

int unit_readRegisterN(){
    State state(static_cast<std::vector<uint8_t >>({0x02}));
}

int main(){
    register_test(unit_readRegisterN);
    start_unit_test();
    end_unit_test();
}