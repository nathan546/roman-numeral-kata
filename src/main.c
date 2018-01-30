/*******************************************************************
* 
*
* DESCRIPTION :     Entry point for software and main menu command line parsing functions
*
*
* NOTES :                   
*
*              TO DO:
*                   README.md
*                   Flow chart?
*
*
* CHANGES :
*             DATE                  WHO                    DETAIL
*      August 29, 2018     Nathan Barrett Morrison      Original Code
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <check.h>

#include "main.h"


//Description:      Main entry point, starts main menu parsing for story selection and manual expression inputs
//Input Parameters: none
//Return:           Always true guarantee
int main(void){

    char input;
    bool exit = 0;
    printf("%s\r\n", mainMenu);

    while(!exit){

        printf("Enter Option From Menu: ");

        input = getAlphanumericChar();
        flushInput();

        //Perform input action
        switch(input){

            case ADDITION_STORY:
                printf("%s\r\n", additionStoryDescript);
                performTestStory("./story_addition.equations", EXPRESSION_RN_OPERATIONS);
                printf("Testing complete!\r\n\r\n");
                break;

            case SUBTRACTION_STORY:
                printf("%s\r\n", subtractionStoryDescript);
                performTestStory("./story_subtraction.equations", EXPRESSION_RN_OPERATIONS);
                printf("Testing complete!\r\n\r\n");
                break;

            case COMPLETE_INDUCTION: 
                printf("%s\r\n", completeInductionDescript);
                performTestStory("./complete_induction.equations", EXPRESSION_RN_TO_DEC_COMPARISONS);
                printf("Testing/Proof complete!\r\n\r\n");  
                break;
                
            case MANUAL_ENTRY:
                manualEntry();
                break;

            case FOSS_LIST:
                printf("%s\r\n", fossList);
                break;

            case QUIT:
                exit = 1;
                break;

            default:
                printf("Input not recognized, try again...\r\n");
                break;
        }

    }

    return 1;

}

//Description:      Performs parsing for manual expression input (addition, subtraction, decimal to roman numeral, roman numeral to decimal, ...)
//Input Parameters: operation - None
//Return:           None
static void manualEntry(){
        char input;
        bool exit = 0;
        ROMAN_NUMERAL_OPERATION romanNumeralOperation;

        printf("%s\r\n", manualMainMenu);

        while(!exit){

            printf("Enter Option From Manual Menu: ");

            input = getAlphanumericChar();

            //Perform input action
            switch(input){
                case MANUAL_ADDITION:
                    romanNumeralOperation.operator = '+';
                    doManualOperation(&romanNumeralOperation);
                    break;
                case MANUAL_SUBTRACTION:
                    romanNumeralOperation.operator = '-';
                    doManualOperation(&romanNumeralOperation);
                    break;
                case MANUAL_DEC_TO_RN:
                    doDecimalToRomanNumeral();
                    break;
                case MANUAL_RN_TO_DEC:
                    doRomanNumeralToDecimal();
                    break;
                case MANUAL_QUIT:
                    printf("%s\r\n", mainMenu);
                    exit = 1;
                    break;
                default:
                    printf("Input not recognized, try again...\r\n");
                    break;
            }

        }

}


//Description:      Gets an alphanumeric character from input (stdin)
//Input Parameters: None
//Return:           Success:  alphanumeric character that was received from stdin
//                  Failure:  Blocking unless successful
static char getAlphanumericChar(){
    char input;
    
    //Only accept standard alphanumeric characters -- discard new lines, carriage returns, etc
    do{
        input = getchar();
    }while(input < '!' || input > '~');

    return input;
}



//Description:      Check if an input character is numeric (0-9) 
//Input Parameters: Pointer to input character
//Return:           Success:  true -- character is numeric (0-9)
//                  Failure:  false -- character is not numeric
static bool isNumericChar(char * input){
    return ( (*input >= '0') && (*input <= '9'));
}


//Description:      Waits for the next CR/LF from input (stdin) and flushes all input until received
//Input Parameters: None
//Return:           None
static void flushInput(){
    char input;
    
    do{
        input = getchar();
    }while(input != '\r' && input !='\n');

}

//Description:      Receives input characters into a string until running out of buffer space, hitting CR/LF, or failing a passed in check function
//Input Parameters: input - string pointer to store input characters into
//                  functionPointer - pointer to a boolean function which determines if the received character is appropriate or not
//Return:           Success: true
//                  Failure: false
static bool getValue(char * input, bool (*functionPointer)(char*)){
    short i = 0; //Currently parsed string position
    bool doneParsing = 0;

    do{

        if(i == 0){
            input[i] = getAlphanumericChar(); //Discard CR/LFs
        }else{
            input[i] = getchar(); //Monitor for CR/LFs
        }

        //End of line or exceeded max characters
        if( i >= MAX_ROMAN_NUMERAL_CHARACTERS ||
            input[i] == '\r'                  ||
            input[i] == '\n' ){
                input[i] = '\0'; //null termination
                doneParsing = 1;
        }else{
            //Only accept types of characters which return true from function pointer
            if( (*functionPointer)(&input[i]) ){
                i++;
            }else{
                flushInput();
                break;
            }     
        }

    }while(!doneParsing);

    return doneParsing;
}


//Description:      Performs a manual addition/subtraction operation (For example, II+I=III or II-I=I) by receiving expression from input (stdin)
//Input Parameters: romanNumeralOperation - pointer to roman numeral operation structure to be used for storing operands, operators, and results
//Return:           None
static void doManualOperation(ROMAN_NUMERAL_OPERATION * romanNumeralOperation){
    printf("Input Operand 1: ");
    if(getValue(romanNumeralOperation->operand1, rnc_is_roman_character)){ //Get a roman numeral value
        printf("Input Operand 2: ");
        if(getValue(romanNumeralOperation->operand2, rnc_is_roman_character)){ //Get a roman numeral value
                
                if(rnc_perform_operation(romanNumeralOperation)){ //Perform addition/subtraction operation
                    printf("\r\nResult: %s %c %s = %s\r\n\r\n", romanNumeralOperation->operand1,
                                                                romanNumeralOperation->operator,
                                                                romanNumeralOperation->operand2,
                                                                romanNumeralOperation->result);
                }else{
                    printf("Error: Unable to perform operation\r\n");
                }

        }else{
            printf("Error:  Invalid input for operand2\r\n");
        }
    }else{
        printf("Error:  Invalid input for operand1\r\n");
    }
}

//Description:      Performs a decimal to roman numeral conversion by receiving decimal value from input (stdin)
//Input Parameters: None
//Return:           None
static void doDecimalToRomanNumeral(){
    char input[MAX_ROMAN_NUMERAL_CHARACTERS];
    int decimalValue;

    printf("Input Decimal Integer: ");

    if(getValue(input, isNumericChar)){ //Get decimal value as a string
        decimalValue = atoi(input); //Convert string to int
        if(decimal_to_roman_numeral(decimalValue, input)){ //Convert decimal to roman numeral
            printf("\r\nResult: %d is %s in roman numerals\r\n\r\n", decimalValue, input);
        }else{
            printf("Error: unable to convert decimal value to roman numeral value\r\n");
        }
    }else{
        printf("Error: Unable to read in decimal value from command line\r\n");
    }
}

//Description:      Performs a roman numeral to decimal conversion by receiving roman numeral value from input (stdin)
//Input Parameters: None
//Return:           None
static void doRomanNumeralToDecimal(){
    char input[MAX_ROMAN_NUMERAL_CHARACTERS];
    int decimalValue;
    printf("Input Roman Numeral: ");
    if(getValue(input, rnc_is_roman_character)){ //Get a roman numeral value

        if(decimalValue = roman_numeral_to_decimal(input)){ //Convert roman numeral value to decimal
            printf("\r\nResult: %s is %d in decimal\r\n\r\n", input, decimalValue);
        }else{
            printf("Error: Invalid input for roman numeral value\r\n");
        }

    }else{
        printf("Error: Invalid input for roman numeral value\r\n");
    }

}

