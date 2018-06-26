//
// Created by a_mod on 26.06.2018.
//

#ifndef VM2_0_UNIT_FRAME_WORK_H
#define VM2_0_UNIT_FRAME_WORK_H

/*
 * This file contains super crude code for unit testing.
 * The Only reason this exists is because I can't be bothered to learn to use an actual unit testing framework.
 * With "learn" I, of course, mean having to setup the library.
*/

/*
 * Also this is copied from a C project.
 * */

#include <cstdlib>
#include <cstdio>
#include <cstring>

typedef int(* test_t)();

test_t* registered_tests = nullptr;
char** registered_tests_names = nullptr;
unsigned int num_of_test = 0;

#define register_test(func){ \
    if(registered_tests == 0) {\
        registered_tests = (test_t*)malloc(sizeof(test_t) * 255); \
        registered_tests_names = (char**)malloc(sizeof(char) * 255);\
    }\
    registered_tests[num_of_test] = func; \
    registered_tests_names[num_of_test] = (char*)malloc(sizeof(char) * strlen(#func) + 1); \
    strcpy(registered_tests_names[num_of_test], #func); \
    num_of_test++; \
}

#define ASSERT_EQUAL(a, b) if(a!=b) return 1;
#define ASSERT_EQUAL_STRING(str_a, str_b) if(strcmp(str_a, str_b) != 0) return 1;

void start_unit_test(){
    int successful_tests = 0;
    for(unsigned int i = 0; i < num_of_test; i++){
        printf("Checking test ... \"");
        printf(registered_tests_names[i]);
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
    printf("Ran: %i, Successful: %i, Failed: %i, %f%%\n", num_of_test, successful_tests, num_of_test - successful_tests, ((double)successful_tests / (double)num_of_test) * 100);
}

void end_unit_test(){
    free(registered_tests);
    for(unsigned int i = 0; i < num_of_test; i++){
        free(registered_tests_names[i]);
    }
    free(registered_tests_names);
}


#endif //VM2_0_UNIT_FRAME_WORK_H
