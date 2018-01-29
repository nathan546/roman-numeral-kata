
/*******************************************************************
* 
*
* DESCRIPTION :     roman numeral calculator functions to be used for:
*                   [1] Roman Numeral Addition/Subtraction
*                   [2] Roman Numeral to Decimal Conversion and Comparison
*                   [3] Decimal to Roman Numeral Conversion and Comparison
*
* PROCESS :         [1] Create a new roman numeral operation structure
*                   [2] Perform the desired operations/comparisons
*                   [3] Free the roman numeral operation structure once done
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
*
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
#include <string.h>
#include "roman_numeral_calculator.h"


//Description:      Performs a roman numeral operation, such as II+I=III or III-I=II
//Input Parameters: operation - Pointer to structure containing operands and operator
//Return:           Success:  true
//                  Failure:  false
bool rnc_perform_operation(ROMAN_NUMERAL_OPERATION * operation){
    unsigned short decimalOperand1, decimalOperand2;
    short decimalResult;
    bool ret = 0;
    char result[32];

    //Convert operand 1 to decimal
    decimalOperand1 = roman_numeral_to_decimal(operation->operand1);
    if(decimalOperand1){

    	//Convert operand 2 to decimal
    	decimalOperand2 = roman_numeral_to_decimal(operation->operand2);
    	if(decimalOperand2){

    		//Perform addition or subtraction
    		decimalResult = (operation->operator == '+') ? (decimalOperand1 + decimalOperand2) : (decimalOperand1 - decimalOperand2);
    		
    		//Convert the addition or subtraction result back to a roman numeral value
    		if(decimal_to_roman_numeral(decimalResult, operation->result)){
    			ret = 1;
    		}

    		
    	}
	}
    return ret;

}

//Description:      Performs a roman numeral comparison of the form 1=I, ensuring we can convert a decimal
//                  to an expected roman numeral value and back to a decimal value again (1 -> I and I -> 1)
//Input Parameters: operation - Pointer to structure containing expected decimal value and roman numeral value
//Return:           Success: true 
//                  Failure: false
bool rnc_perform_comparison(ROMAN_NUMERAL_OPERATION * operation){

	unsigned short decimalOperand1;
	bool ret = 0;

	//Convert the incoming roman numeral value to a decimal
    decimalOperand1 = roman_numeral_to_decimal(operation->operand1);
    if(decimalOperand1){

    	//Convert the incoming decimal value to a roman numeral
	    if(decimal_to_roman_numeral(operation->decimalComparator, operation->result)){

	    	//Confirm the two converted values match the two input values
			if(  (strcmp(operation->result, operation->operand1) == 0)  && (operation->decimalComparator == decimalOperand1) ){
				ret = 1;
			}

		}

    }

	return ret;
}


//Description:      Check if a character is part of the roman numeral alphabet ('M', 'D', 'C', 'L', 'X', 'V', 'I')
//Input Parameters: c - Pointer to a character to be checked
//Return:           Success: true 
//                  Failure: false
bool rnc_is_roman_character(char * c){
    int i;

    if(*c >= 97) //Greater than or equal to 'a'
        *c -= 32; //Convert from lower case to upper

    //Loop through our roman character table and see if there is a match
	for(i = 0; i < ROMAN_CHARACTERS_AVAILABLE; i++)
		if(romanCharacters[i] == *c)
			return 1;

	return 0;

}

//Description:      Convert a roman numeral value to a decimal value
//Input Parameters: romanNumeral - String pointer to roman numeral value to be converted
//Return:           Success: converted decimal value in range 1-3999
//                  Failure: 0
unsigned short roman_numeral_to_decimal(char * romanNumeral){
	unsigned short i, previous = 0, current;
	short cumulator = 0;

	if(roman_numeral_valid(romanNumeral)){

		//Loop through the incoming string, character by character, and add
		//the equivalent decimal values for each character into a cumulator.
		for(i = 0; i < strlen(romanNumeral); i++){
			current = romanNumeralLookupTable[romanNumeral[i]]; //Look up table to convert ASCII character to decimal value
			cumulator += current;

			//We had a case of roman numeral subtractive notation, so remove the value from the cumulator(IV=5-1=4)
			if(previous && (previous < current) ){
				cumulator -= (2*previous); //2x because we added in the subtractor once on the previous loop
				previous = 0;
			}else{
				previous = current;
			}

		}

	}

	if(cumulator > 3999) //Only accept 1-3999 as valid
		cumulator = 0;

    if(cumulator == 0)
        printf("Error: unable to convert roman numeral value to a decimal value.  Check that values are within [1-3999] range.\r\n");

	return cumulator;
}

//Description:      Convert a decimal value to a roman numeral value
//Input Parameters: decimal - Incoming decimal value to be converted
//                  outputRomanNumeral - String pointer to store converted roman numeral value into
//Return:           Success: true
//                  Failure: false
//Notes:            This iterates through a roman numeral character/value table pair {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
//                                                                                      {1000, 500, 100, 50, 10, 5, 1};
//                  starting at the highest value (M, 1000) and checking each value for the amount of times we can fit it into
//                  our output sting.
//                  We also check for >3 occurences of I,X,and C and compress it with the next highest value as necessary (so IIII -> IV)
bool decimal_to_roman_numeral(short decimal, char * outputRomanNumeral){
    unsigned short divisor, previousValue, i, j, k = 0; //iterators
                                                        //i for current roman numeral table position ('M', 'D', 'C', 'L', 'X', 'V', 'I')
                                                        //j for repetitions of character to be placed into output string
                                                        //k for current position in output string

    if(decimal > 0 && decimal < 4000){ //Only accept 1-3999 as valid

	    for(i = 0; i < ROMAN_CHARACTERS_AVAILABLE; i++){
	        divisor = decimal / romanValues[i];

	        //Check for 3x repetition of I, X, or C and compress if so
	        if( ( romanCharacters[i] == 'I' ||
	              romanCharacters[i] == 'X' ||
	              romanCharacters[i] == 'C'    ) && divisor > 3){

	                //Consider: 10 + 4 = 14, X + IV = XIV - the modulo approach would show XIIII without this check
	                //          10 + 9 = 19, X + IX = XIX - the modulo approach would show XVIV without this check
	                previousValue = romanNumeralLookupTable[outputRomanNumeral[k-1]];

	                if( (previousValue + divisor*romanValues[i]) == (romanValues[i-2]-romanValues[i]) ) { //Check if the previous roman numeral can be merged in as well (XVIV -> XIX)
	                    outputRomanNumeral[k-1] = romanCharacters[i];
	                    outputRomanNumeral[k++] = romanCharacters[i-2];
	                }else{ //Just replace the repetition with the next highest roman numeral - 1, no additional merging necessary (XIIII -> XIV)
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

	    return 1;
	}

    printf("Error: unable to convert decimal value to roman numeral value.  Check that values are within [1-3999] range.\r\n");

	return 0;

}



//Description:      
//Input Parameters:
//Return:           Success:  
//                  Failure:  
static bool roman_numeral_valid(char * romanNumeral){
    int i = 0; //current position of incoming roman numeral string
    bool ret = 1;
    char previousCharacter = 0;
    short consecutiveCharCounts[256]; //Table to keep track of number of character occurences
                                      //Optimized for speed (256 indexes instead of ROMAN_CHARACTERS_AVAILABLE), at the cost of more ram consumption

    memset(consecutiveCharCounts, 0, 256*sizeof(consecutiveCharCounts[0])); //Zero out the counts


    for(i = 0; i < strlen(romanNumeral); i++){

        if(rnc_is_roman_character(&romanNumeral[i])){

            //Keep count of each occurence of a roman character
            consecutiveCharCounts[romanNumeral[i]]++;

            //Check for too many consecutive occurences of characters
            if(previousCharacter != romanNumeral[i]){

                //If the numeral is I, X or C you can't have more than three ("II" + "II" = "IV" not “IIII”).
                //If the numeral is V, L or D you can't have more than one ("D" + "D" = "M" not “DD”)
                switch(previousCharacter){

                    case 'I':
                    case 'X':
                    case 'C':

                        if(consecutiveCharCounts[previousCharacter] > 3){
                            ret = 0;
                            break;
                        }else{
                            consecutiveCharCounts[previousCharacter] = 0; //Reset consecutive counts
                        }
                        break;

                    case 'V':
                    case 'L':
                    case 'D':

                        if(consecutiveCharCounts[previousCharacter] > 1){
                            ret = 0;
                            break;
                        }else{
                            consecutiveCharCounts[previousCharacter] = 0; //Reset consecutive counts
                        }
                        break;

                    default:
                        break;    

                }

            }

            //Get to our second character before looking for subtractive notation
            if(previousCharacter != 0){

                //Current character is greater than previous character, we may have found an error
                //or a case of subtractive notation
                if( romanNumeralLookupTable[romanNumeral[i]] > romanNumeralLookupTable[previousCharacter]){
                    
                    //Valid subtractive notations are
                    //IV, IX, XL, XC, CD, CM
                    if(  ( romanNumeral[i] == 'M' && previousCharacter != 'C' ) ||
                         ( romanNumeral[i] == 'D' && previousCharacter != 'C' ) ||
                         ( romanNumeral[i] == 'C' && previousCharacter != 'X' ) ||
                         ( romanNumeral[i] == 'L' && previousCharacter != 'X' ) ||
                         ( romanNumeral[i] == 'X' && previousCharacter != 'I' ) ||
                         ( romanNumeral[i] == 'V' && previousCharacter != 'I' )
                       ){

                        ret = 0;
                        break;

                    }

                }

            }

            previousCharacter = romanNumeral[i];

        }else{
            ret = 0;
            break;
        }

    }



	return ret;
}
