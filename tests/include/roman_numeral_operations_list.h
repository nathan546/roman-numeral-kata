
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

#define MAX_ROMAN_NUMERAL_CHARACTERS 32 //Maximum number of roman numeral characters in an expression/result

//Roman numeral operation structure for confirmation that
//		operand1 operator operand2 = result
//		I+I=II
// OR
//		operand1=decimalComparator
//      1=I
typedef struct{ 
    char operand1[MAX_ROMAN_NUMERAL_CHARACTERS];  // String for first operand of roman numeral expression
    char operator;                                // Operand of expression (+ or -)
    char operand2[MAX_ROMAN_NUMERAL_CHARACTERS];  // String for second operator of roman numeral expression
    char result[MAX_ROMAN_NUMERAL_CHARACTERS];    // Result, in string form of operand1 operand operator2
    unsigned short decimalComparator;             // Integer comparator for comparing integer to operand1
}ROMAN_NUMERAL_OPERATION;

//Public functions
ROMAN_NUMERAL_OPERATION * rntList_create(int listSize);
bool rntList_parse(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, char * fileName, EXPRESSION_TYPE story);
bool rntList_destroy(ROMAN_NUMERAL_OPERATION * romanNumeralTestList);
bool rntList_operation_valid(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, EXPRESSION_TYPE expressionType);

//Private functions
static bool rntList_parseOperations(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, char * fileName, TEST_STORY * story);
static bool rntList_parseComparisons(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, char * fileName, TEST_STORY * story);

#endif