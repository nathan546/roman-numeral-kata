
/*******************************************************************
* 
*
* DESCRIPTION :     Performs a libcheck-based test on a roman numeral calculator by
*                   iteratively checking the expressions/comparisons inside a provided
*                   story file
*             
*
* PROCESS :
*                   [1]  Call performTestStory() with story file path and expression type
*
* NOTES :           None
*
* CHANGES :
*             DATE                  WHO                    DETAIL
*      August 27, 2018     Nathan Barrett Morrison      Original Code
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <pthread.h>

#include "roman_numeral_calculator.h"
#include "roman_numeral_operations_list.h"
#include "check_roman_numeral_calculator.h"
#include "story_reader.h"

//Private Globals
static ROMAN_NUMERAL_OPERATION * romanNumeralTestList = NULL;
static int numberOperations;
static char storyFile[256];
static pthread_mutex_t testMutex = PTHREAD_MUTEX_INITIALIZER;
static EXPRESSION_TYPE expressionType;

//Libcheck assertion check for the validity of a single expression/comparison inside a roman numeral test list
START_TEST (check_roman_numeral_operation){
    ck_assert (rntList_operation_valid(&romanNumeralTestList[_i], expressionType));
}
END_TEST

//Description:      Setup function to be run prior to starting roman numeral operation test via libcheck fixture
//Input Parameters: none
//Return:           none
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

//Description:      Tear down function to be run post roman numeral operation test via libcheck fixture
//Input Parameters: none
//Return:           none
static void check_roman_numeral_teardown(){
    if(!rntList_destroy(romanNumeralTestList)){ //Clean up... Destroy the list after we're done testing
        printf("Unable to destroy Roman Numeral Test List\r\n");
    }
}

//Description:      Creates test cases, fixtures, and loops for roman numeral operation test
//Input Parameters: none
//Return:           Pointer to new libcheck test suite
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


//Description:      Public function to launch libecheck-based roman numeral calaculator test stories
//Input Parameters: storyFilePath - String path to story file to be used for testing
//                  expressionTypeParam - Expression type represented in story file we're using
//Return:           none
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
        printf("Error: Story File Path Too Long (> %ld characters)\r\n", sizeof(storyFile));
    }

}