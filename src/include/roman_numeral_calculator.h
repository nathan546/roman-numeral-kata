
/*******************************************************************
* 
*
* DESCRIPTION :     Header functions, structures, and look up tables for roman_numeral_calculator.c
*                   See roman_numeral_calculator.c for more information
*
* NOTES :            None
*
* CHANGES :
*             DATE                  WHO                    DETAIL
*      August 27, 2018     Nathan Barrett Morrison      Original Code
*
*/

#ifndef ROMAIN_NUMERAL_CALCULATOR_H

#include "globals.h"

#define ROMAIN_NUMERAL_CALCULATOR_H

#define ROMAN_CHARACTERS_AVAILABLE 7 //Number of charactes in roman numeral alpabet

//1:1 translation mappings for roman numeral characters to their decimal equivalents
static char romanCharacters[ROMAN_CHARACTERS_AVAILABLE] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
static unsigned short romanValues[ROMAN_CHARACTERS_AVAILABLE] = {1000, 500, 100, 50, 10, 5, 1};

//Types of expressions we can parse in while testing (I+I=II or 1=I)
typedef enum {EXPRESSION_RN_OPERATIONS, EXPRESSION_RN_TO_DEC_COMPARISONS} EXPRESSION_TYPE;

//This is a look up table for converting single character ASCII roman numerals into their decimal equivalents
//Example: I is an ASCII 73, so romanNumeralLookupTable[73] = 1
static unsigned short romanNumeralLookupTable[256] =
{
//     1     2     3     4      5    6     7     8     9     10    11    12    13    14    15    16
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //   1
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //   2
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //   3
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //   4
       0,    0,    0,  100,  500,    0,    0,    0,    0,    1,    0,    0,   50, 1000,    0,    0,
       0,    0,    0,    0,    0,    0,    5,    0,   10,    0,    0,    0,    0,    0,    0,    0,
       0,    0,    0,  100,  500,    0,    0,    0,    0,    1,    0,    0,   50, 1000,    0,    0,
       0,    0,    0,    0,    0,    0,    5,    0,   10,    0,    0,    0,    0,    0,    0,    0,
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //   9
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //  10
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //  11 
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //  12
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //  13
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //  14
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0    //  15
};

//Structure of a roman numeral calculator
typedef struct RomanNumeralCalculator RomanNumeralCalculator;

//Public Functions
RomanNumeralCalculator * rnc_create();
bool rnc_perform_operation(RomanNumeralCalculator * m, char * operand1, char operator, char * operand2);
bool rnc_perform_comparison(RomanNumeralCalculator * m, char * operand1, unsigned short decimalComparator);
void rnc_free(RomanNumeralCalculator * m);

//Private functions
static bool roman_numeral_valid(char * romanNumeral);
static unsigned short roman_numeral_to_decimal(char * romanNumeral); 
static bool decimal_to_roman_numeral(unsigned short decimal, char * outputRomanNumeral);

#endif

