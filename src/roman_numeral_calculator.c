#include <stdlib.h>
#include "roman_numeral_calculator.h"
#include "globals.h"

//Guidelines from Kata specifications
//------------------------------------------------------------------------------------
//Roman numerals consist of the following letters: I, V, X, L, C, D, and M which mean
//one, five, ten, fifty, hundred, five hundred and one thousand respectively.

//An example would be "XIV" + "LX" = "LXXIV"
//Numerals can be concatenated to form a larger numeral ("XX" + "II" = "XXII").

//If a lesser numeral is put before a bigger it means subtraction of the lesser from the bigger
//("IV" means four, "CM" means ninehundred).

//If the numeral is I, X or C you can't have more than three ("II" + "II" = "IV" not “IIII”).
//If the numeral is V, L or D you can't have more than one ("D" + "D" = "M" not “DD”)

//The maximum roman numeral is 3999 (MMMCMXCIX)
//-------------------------------------------------------------------------------------

 
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

static bool roman_numeral_valid(char * romanNumeral){
	return 1;
}

static unsigned short roman_numeral_to_decimal(char * romanNumeral){
	unsigned short i, previous = 0, current;
	short cumulator = 0;

	if(roman_numeral_valid(romanNumeral)){
		for(i = 0; i < strlen(romanNumeral); i++){
			current = romanNumeralLookupTable[romanNumeral[i]];
			cumulator += current;

			if(previous && (previous < current) ){
				cumulator -= (2*previous);
				previous = 0;
			}else{
				previous = current;
			}

		}
	}

	return cumulator;

}

RomanNumeralCalculator * rnc_create(){
    return NULL;
}

char * rnc_perform_operation(RomanNumeralCalculator * m, char * operand1, char operator, char * operand2){

	printf("Operand 1 in decimal %d\r\n", roman_numeral_to_decimal(operand1));
    return NULL;
}

void rnc_free(RomanNumeralCalculator * m){
    return;
}

