
/*******************************************************************
* 
*
* DESCRIPTION :     Create a roman numeral calculator to be used for:
*                   [1] Roman Numeral Addition/Subtraction
*                   [2] Roman Numeral to Decimal Conversion and Comparison
*                   [3] Decimal to Roman Numeral Conversion and Comparison
*
* PROCESS :         [1] Create a new roman numeral calculator
*                   [2] Perform the desired operations/comparisons
*                   [3] Free the roman numeral calculator once done
*
* NOTES :                   
*				Guidelines from Kata specifications
*
*				Roman numerals consist of the following letters: I, V, X, L, C, D, and M which mean
*				one, five, ten, fifty, hundred, five hundred and one thousand respectively.
*
*				An example would be "XIV" + "LX" = "LXXIV"
*				Numerals can be concatenated to form a larger numeral ("XX" + "II" = "XXII").
*
*				If a lesser numeral is put before a bigger it means subtraction of the lesser from the bigger
*				("IV" means four, "CM" means ninehundred).
*
*				If the numeral is I, X or C you can't have more than three ("II" + "II" = "IV" not “IIII”).
*				If the numeral is V, L or D you can't have more than one ("D" + "D" = "M" not “DD”)
*
*				The maximum roman numeral is 3999 (MMMCMXCIX)
*
*       - Need to add calculator structure instantiation / deletion
*       - Need to complete roman_numeral_valid() function
*       - Need to check for invalid negative numbers during subtractions
*
* CHANGES :
*             DATE                  WHO                    DETAIL
*      August 27, 2018     Nathan Barrett Morrison      Original Code
*
*/

#include <stdlib.h>
#include <stdio.h>
#include "roman_numeral_calculator.h"


//Description:      Roman numeral calculator creation function
//Input Parameters: none
//Return:           Success:  Pointer to roman numeral calculator
//                  Failure:  NULL
RomanNumeralCalculator * rnc_create(){
    return NULL;
}

//Description:      
//Input Parameters:
//Return:           Success:  
//                  Failure:  
char * rnc_perform_operation(RomanNumeralCalculator * m, char * operand1, char operator, char * operand2){
    unsigned short decimalOperand1, decimalOperand2, decimalResult;

    char result[32];

    decimalOperand1 = roman_numeral_to_decimal(operand1);
    decimalOperand2 = roman_numeral_to_decimal(operand2);
    decimalResult = (operator == '+') ? (decimalOperand1 + decimalOperand2) : (decimalOperand1 - decimalOperand2);

    decimal_to_roman_numeral(decimalResult, result);

    printf("%s %c %s = %s\r\n", operand1, operator, operand2, result);
	printf("%d %c %d = %d\r\n\r\n", decimalOperand1, operator, decimalOperand2, decimalResult);

    return NULL;
}

//Description:      
//Input Parameters:
//Return:           Success:  
//                  Failure:  
bool rnc_perform_comparison(RomanNumeralCalculator * m, char * operand1, unsigned short decimalComparator){

	unsigned short decimalOperand1;
	char result[32];
	bool ret = 0;

	//printf("Confirming %s = %d ", operand1, decimalComparator);

    decimalOperand1 = roman_numeral_to_decimal(operand1);
    decimal_to_roman_numeral(decimalComparator, result);

	if(  (strcmp(result, operand1) == 0)  && (decimalComparator == decimalOperand1) ){
		//printf("... good!\r\n");
		ret = 1;
	}else{
		printf("Confirming %s = %d ", operand1, decimalComparator);
		printf("... bad!\r\n");
	}

	return ret;
}

//Description:      
//Input Parameters:
//Return:           Success:  
//                  Failure:  
void rnc_free(RomanNumeralCalculator * m){
    return;
}

//Description:      
//Input Parameters:
//Return:           Success:  
//                  Failure:  
static bool roman_numeral_valid(char * romanNumeral){
	return 1;
}

//Description:      
//Input Parameters:
//Return:           Success:  
//                  Failure:  
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

//Description:      
//Input Parameters:
//Return:           Success:  
//                  Failure:  
static bool decimal_to_roman_numeral(unsigned short decimal, char * outputRomanNumeral){
    unsigned short divisor, i, j, k = 0;

    for(i = 0; i < ROMAN_CHARACTERS_AVAILABLE; i++){
        divisor = decimal / romanValues[i];

        //Check for 3x repetition of I, X, or C and compress if so
        if( ( romanCharacters[i] == 'I' ||
              romanCharacters[i] == 'X' ||
              romanCharacters[i] == 'C'    ) && divisor > 3){

                //Consider: 10 + 4 = 14, X + IV = XIV - the modulo approach would show XIIII without this check
                //          10 + 9 = 19, X + IX = XIX - the modulo approach would show XVIV without this check
                unsigned short previousValue = romanNumeralLookupTable[outputRomanNumeral[k-1]];
            
                if( (previousValue + divisor*romanValues[i]) == (romanValues[i-2]-romanValues[i]) ) { //Check if the previous roman numeral can be merged in as well (XVIV -> XIX)
                    outputRomanNumeral[k-1] = romanCharacters[i];
                    outputRomanNumeral[k++] = romanCharacters[i-2];
                }else{ //Just replace the repetition with the next highest roman numeral - 1, no additional merging necessary (XIII -> XIV)

                    if(previousValue == romanNumeralLookupTable[romanCharacters[i-1]]){
                        if(romanCharacters[i-1] == 'V' ||
                           romanCharacters[i-1] == 'L' ||
                           romanCharacters[i-1] == 'D'){
                        }
                    }

                    outputRomanNumeral[k++] = romanCharacters[i];
                    outputRomanNumeral[k++] = romanCharacters[i-1];
                }

                decimal = decimal % romanValues[i];

        }

        //Standard path, no special cases
        else{
            for(j = 0; j < divisor; j++){
                outputRomanNumeral[k++] = romanCharacters[i];
            }
            decimal = decimal % romanValues[i];
        }


    }

    outputRomanNumeral[k] = '\0'; //null termination

}


