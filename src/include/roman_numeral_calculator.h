#ifndef ROMAIN_NUMERAL_CALCULATOR_H
#define ROMAIN_NUMERAL_CALCULATOR_H

typedef struct RomanNumeralCalculator RomanNumeralCalculator;

RomanNumeralCalculator * rnc_create();
char * rnc_perform_operation(RomanNumeralCalculator * m, char * operand1, char operator, char * operand2);
void rnc_free(RomanNumeralCalculator * m);

#endif /* ROMAIN_NUMERAL_CALCULATOR_H */

