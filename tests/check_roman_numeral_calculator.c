#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <pthread.h>

#include "roman_numeral_calculator.h"
#include "roman_numeral_operations_list.h"
#include "story_reader.h"

//Globals
static ROMAN_NUMERAL_OPERATION * romanNumeralTestList = NULL;
static int numberOperations;
static char storyFile[256];
static pthread_mutex_t testMutex = PTHREAD_MUTEX_INITIALIZER;
static EXPRESSION_TYPE expressionType;

START_TEST (check_roman_numeral_operation){
    ck_assert (rntList_operation_valid(&romanNumeralTestList[_i], expressionType));
}
END_TEST

static void check_roman_numeral_setup(){
    romanNumeralTestList = rntList_create(numberOperations); //Create a new test list of equations
    if(romanNumeralTestList != NULL){
        if(!rntList_parse(romanNumeralTestList, storyFile, expressionType)){ //Parse equations in from a file
            printf ("Error parsing story file\r\n");
        }
    }else{
        printf("Unable to allocate memory for Roman Numeral Test List\r\n");
    }
}

static void check_roman_numeral_teardown(){
    if(!rntList_destroy(romanNumeralTestList)){ //Clean up... Destroy the list after we're done testing
        printf("Unable to destroy Roman Numeral Test List\r\n");
    }
}

static Suite * roman_numeral_calculator_test_suite(){
    Suite *s;
    TCase *tc_core;

    //Create a new test suite
    s = suite_create("RomanNumeralCalculator");

    //Core a new test case
    tc_core = tcase_create("Core");

    //Calculate the number of roman numeral operations we will be performing from our story file
    numberOperations = story_peek_lines(storyFile);

    //Set up the test suite to iteratively perform the roman numeral operations
    tcase_add_unchecked_fixture(tc_core, check_roman_numeral_setup, check_roman_numeral_teardown);
    tcase_add_loop_test (tc_core, check_roman_numeral_operation, 0, numberOperations);
    suite_add_tcase(s, tc_core);

    return s;
}

void performTestStory(char * storyFilePath, EXPRESSION_TYPE expressionTypeParam){
    int number_failed;
    Suite *s;
    SRunner *sr;
    int fileNameLength = strlen(storyFilePath);

    if(fileNameLength < sizeof(storyFile)){

        //Wrap with a mutex to ensure the global static variables are thread-safe
        //This isn't explicitly necessary in this example, as I haven't threaded anything (yet)...
        pthread_mutex_lock(&testMutex);

        expressionType = expressionTypeParam;

        //Copy file name parameter into global file name parameter, for test suite to use
        memcpy(storyFile, storyFilePath, fileNameLength+1); //Make sure to copy the null termination!

        //Instantiate and run the test suite!
        s = roman_numeral_calculator_test_suite();
        sr = srunner_create(s);

        srunner_run_all(sr, CK_NORMAL);
        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);

        //Unlock mutex so another thread/call can take testing access
        pthread_mutex_unlock(&testMutex);

    }else{
        printf("Error: Story File Path Too Long (> %d characters)\r\n", sizeof(storyFile));
    }


}