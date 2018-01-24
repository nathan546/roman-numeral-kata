#ifndef ROMAN_NUMERAL_OPERATIONS_LIST_H

#define ROMAN_NUMERAL_OPERATIONS_LIST_H

#define bool char //boolean

//operand1 operator operand2 = result
// I + I = II
typedef struct{ 
    char operand1[32];
    char operator;    
    char operand2[32];
    char result[32];
}ROMAN_NUMERAL_TEST_OPERATION;

ROMAN_NUMERAL_TEST_OPERATION * rntList_create(int listSize);
bool rntList_parse(ROMAN_NUMERAL_TEST_OPERATION * romanNumeralTestList, char * fileName);
bool rntList_destroy(ROMAN_NUMERAL_TEST_OPERATION * romanNumeralTestList);
bool rntList_operation_valid(ROMAN_NUMERAL_TEST_OPERATION * romanNumeralTestList);

#endif