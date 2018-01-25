#ifndef ROMAIN_NUMERAL_CALCULATOR_H
#define ROMAIN_NUMERAL_CALCULATOR_H

#define ROMAN_CHARACTERS_AVAILABLE 7
static char romanCharacters[ROMAN_CHARACTERS_AVAILABLE] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
static unsigned short romanValues[ROMAN_CHARACTERS_AVAILABLE] = {1000, 500, 100, 50, 10, 5, 1};


//This is a look up table for converting single character ASCII roman numerals into their decimal equivalents
//Example: I is an ASCII 73, so romanNumeralLookupTable[73] = 1
static unsigned short romanNumeralLookupTable[256] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 100, 500, 0, 0, 0, 0, 1, 0, 0, 50, 1000, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 0, 10, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 100, 500, 0, 0, 0, 0, 1, 0, 0, 50, 1000, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 0, 10, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


typedef struct RomanNumeralCalculator RomanNumeralCalculator;

RomanNumeralCalculator * rnc_create();
char * rnc_perform_operation(RomanNumeralCalculator * m, char * operand1, char operator, char * operand2);
void rnc_free(RomanNumeralCalculator * m);

#endif /* ROMAIN_NUMERAL_CALCULATOR_H */

