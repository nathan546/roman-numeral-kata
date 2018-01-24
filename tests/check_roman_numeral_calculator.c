#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <pthread.h>

#include "roman_numeral_calculator.h"
#include "roman_numeral_operations_list.h"
#include "story_reader.h"

enum {ADDITION_STORY='1', SUBTRACTION_STORY='2', MANUAL_ENTRY='3', QUIT='4'};

//Globals
static ROMAN_NUMERAL_TEST_OPERATION * romanNumeralTestList = NULL;
static int numberOperations;

START_TEST (check_roman_numeral_operation){
    ck_assert (rntList_operation_valid ( &romanNumeralTestList[_i] ) );
}
END_TEST

void check_roman_numeral_setup(){
    romanNumeralTestList = rntList_create(numberOperations); //Create a new test list of equations
    if(romanNumeralTestList != NULL){
        if(!rntList_parse(romanNumeralTestList, "./story_addition.equations")){ //Parse equations in from a file
            printf ("Error parsing story file\r\n");
        }
    }else{
        printf("Unable to allocate memory for Roman Numeral Test List\r\n");
    }
}

void check_roman_numeral_teardown(){
    if(!rntList_destroy(romanNumeralTestList)){ //Clean up... Destroy the list after we're done testing
        printf("Unable to destroy Roman Numeral Test List\r\n");
    }
}

Suite * roman_numeral_calculator_test_suite(){
    Suite *s;
    TCase *tc_core;

    s = suite_create("RomanNumeralCalculator");
    //Core test case
    tc_core = tcase_create("Core");

    TEST_STORY * tempStory;
    tempStory = story_create("./story_addition.equations");
    if(tempStory == NULL){
        printf("Unable to create story, error number %d\r\n", errno);
    }else{
        numberOperations = story_peek_lines(tempStory);
    }

    tcase_add_unchecked_fixture(tc_core, check_roman_numeral_setup, check_roman_numeral_teardown);
    tcase_add_loop_test (tc_core, check_roman_numeral_operation, 0, numberOperations); //Perform testing on all incoming equations
    suite_add_tcase(s, tc_core);

    return s;
}

void performStory(){
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = roman_numeral_calculator_test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
}

int main(void){

    char input;

    printf("\r\nWelcome to Roman Numeral Calculator Kata\r\n");
    printf("\t1) Run Addition Test Story\r\n");
    printf("\t2) Run Subtraction Test Story\r\n");
    printf("\t3) Manually Enter Roman Numeral Expression\r\n");
    printf("\t4) Quit\r\n\r\n");

    while(1){

        printf("Enter Option From Menu: ");

        //Only accept standard ASCII characters -- discard new lines, carriage returns, etc
        do{
            input = getchar();
        }while(input < '!' || input > '~');

        //Perform input action
        switch(input){

            case ADDITION_STORY:
                    performStory();
                break;

            case SUBTRACTION_STORY:
                return EXIT_SUCCESS;
                break;

            case MANUAL_ENTRY:
                return EXIT_SUCCESS;
                break;

            case QUIT:
                return EXIT_SUCCESS;
                break;

            default:
                printf("Input not recognized, try again...\r\n");
                break;
        }

    }

}

