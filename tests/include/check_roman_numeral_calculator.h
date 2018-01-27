
/*******************************************************************
* 
*
* DESCRIPTION :     Header file for check_roman_numeral_calculator.c
*                   For more info see check_roman_numeral_calculator.c
*
* NOTES :           None
*
* CHANGES :
*             DATE                  WHO                    DETAIL
*      August 26, 2018     Nathan Barrett Morrison      Original Code
*
*/

#ifndef CHECK_ROMAN_NUMERAL_CALCULATOR_H

#define CHECK_ROMAN_NUMERAL_CALCULATOR_H

//Public functions
void performTestStory(char * storyFilePath, EXPRESSION_TYPE expressionTypeParam);


//Private functions
static void check_roman_numeral_setup();
static void check_roman_numeral_teardown();
static Suite * roman_numeral_calculator_test_suite();

#endif