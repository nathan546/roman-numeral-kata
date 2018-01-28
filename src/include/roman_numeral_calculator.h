
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
#define MAX_ROMAN_NUMERAL_CHARACTERS 32 //Maximum number of roman numeral characters in an expression/result

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
       0,    0,    0,  100,  500,    0,    0,    0,    0,    1,    0,    0,   50, 1000,    0,    0,   //   5
       0,    0,    0,    0,    0,    0,    5,    0,   10,    0,    0,    0,    0,    0,    0,    0,   //   6
       0,    0,    0,  100,  500,    0,    0,    0,    0,    1,    0,    0,   50, 1000,    0,    0,   //   7
       0,    0,    0,    0,    0,    0,    5,    0,   10,    0,    0,    0,    0,    0,    0,    0,   //   8
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //   9
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //  10
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //  11 
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //  12
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //  13
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   //  14
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0    //  15
};

//Roman numeral operation structure for confirmation that
//      operand1 operator operand2 = result
//      I+I=II
// OR
//      operand1=decimalComparator
//      1=I
typedef struct{ 
    char operand1[MAX_ROMAN_NUMERAL_CHARACTERS];  // String for first operand of roman numeral expression
    char operator;                                // Operand of expression (+ or -)
    char operand2[MAX_ROMAN_NUMERAL_CHARACTERS];  // String for second operator of roman numeral expression
    char result[MAX_ROMAN_NUMERAL_CHARACTERS];    // Result, in string form of operand1 operand operator2
    unsigned short decimalComparator;             // Integer comparator for comparing integer to operand1
}ROMAN_NUMERAL_OPERATION;


//Public Functions
bool rnc_perform_operation(ROMAN_NUMERAL_OPERATION * operation);
bool rnc_perform_comparison(ROMAN_NUMERAL_OPERATION * operation);
bool rnc_is_roman_character(char * c);
unsigned short roman_numeral_to_decimal(char * romanNumeral); 
bool decimal_to_roman_numeral(short decimal, char * outputRomanNumeral);

//Private functions
static bool roman_numeral_valid(char * romanNumeral);

#endif

