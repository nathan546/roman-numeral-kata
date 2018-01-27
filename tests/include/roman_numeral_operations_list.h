#ifndef ROMAN_NUMERAL_OPERATIONS_LIST_H

#include "globals.h"
#include "roman_numeral_calculator.h"
#include "story_reader.h"

#define ROMAN_NUMERAL_OPERATIONS_LIST_H

#define MAX_ROMAN_NUMERAL_CHARACTERS 32


//For confirmation that
//		operand1 operator operand2 = result
//		I + I = II
// OR
//		operand1 = decimalComparator
typedef struct{ 
    char operand1[MAX_ROMAN_NUMERAL_CHARACTERS];
    char operator;    
    char operand2[MAX_ROMAN_NUMERAL_CHARACTERS];
    char result[MAX_ROMAN_NUMERAL_CHARACTERS];
    unsigned short decimalComparator;
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