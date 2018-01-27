
/*******************************************************************
* 
*
* DESCRIPTION :     Header file for roman_numeral_operations_list.c related functions
*                   See the *.c file for more information
*
*
* NOTES :           None
*
* CHANGES :
*             DATE                  WHO                    DETAIL
*      August 26, 2018     Nathan Barrett Morrison      Original Code
*
*/

#ifndef ROMAN_NUMERAL_OPERATIONS_LIST_H

#include "globals.h"
#include "roman_numeral_calculator.h"
#include "story_reader.h"

#define ROMAN_NUMERAL_OPERATIONS_LIST_H

//Public functions
ROMAN_NUMERAL_OPERATION * rntList_create(int listSize);
bool rntList_parse(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, char * fileName, EXPRESSION_TYPE story);
bool rntList_destroy(ROMAN_NUMERAL_OPERATION * romanNumeralTestList);
bool rntList_operation_valid(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, EXPRESSION_TYPE expressionType);

//Private functions
static bool rntList_parseOperations(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, char * fileName, TEST_STORY * story);
static bool rntList_parseComparisons(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, char * fileName, TEST_STORY * story);

#endif