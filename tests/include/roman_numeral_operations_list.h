#ifndef ROMAN_NUMERAL_OPERATIONS_LIST_H

#include "globals.h"
#include "roman_numeral_calculator.h"

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

ROMAN_NUMERAL_OPERATION * rntList_create(int listSize);
bool rntList_parse(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, char * fileName, EXPRESSION_TYPE story);
bool rntList_destroy(ROMAN_NUMERAL_OPERATION * romanNumeralTestList);
bool rntList_operation_valid(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, EXPRESSION_TYPE expressionType);

#endif