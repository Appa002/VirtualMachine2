//
// Created by a_mod on 26.06.2018.
//

#ifndef VM2_0_UNIT_FRAME_WORK_H
#define VM2_0_UNIT_FRAME_WORK_H

/*
 * This file contains super crude code for unit testing.
 * The Only reason this exists is because I can't be bothered to learn to use an actual unit testing framework.
 * With "learn" I mean having to setup the library.
*/

/*
 * Also this is copied from a C project.
 * */

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

typedef int(* test_t)();

std::vector<test_t> registered_tests;
std::vector<std::string> registered_tests_names;

#define register_test(func){ \
    registered_tests.push_back(func);\
    registered_tests_names.push_back(std::string(#func)); \
}

#define ASSERT_EQUAL(a, b) if(a!=b) return 1;

void start_unit_test(){
    int successful_tests = 0;
    for(unsigned int i = 0; i < registered_tests.size(); i++){
        printf("Checking test ... \"");
        printf(registered_tests_names[i].c_str());
        printf("\"\n");
        int result = registered_tests[i]();
        printf("    -> %i ", result);
        if(result == 0){
            printf("[OK]\n");
            successful_tests++;
        }
        else
            printf("[ERROR]\n");

    }
    printf("==============\n");
    printf("Ran: %u, Successful: %u, Failed: %u, %f%%\n",
           (unsigned)registered_tests.size(), successful_tests,
           (unsigned)registered_tests.size() - successful_tests,
           ((double)successful_tests / (double)registered_tests.size()) * 100);
}


#endif //VM2_0_UNIT_FRAME_WORK_H
