//TO DO:
//       README.md
//       Flow chart

#include <stdlib.h>
#include <stdio.h>
#include <check.h>

#include "main.h"

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
                printf("Testing complete!\r\n");
                break;

            case SUBTRACTION_STORY:
                printf("%s\r\n", subtractionStoryDescript);
                performTestStory("./story_subtraction.equations", EXPRESSION_RN_OPERATIONS);
                printf("Testing complete!\r\n");
                break;

            case COMPLETE_INDUCTION: 
                printf("%s\r\n", completeInductionDescript);
                performTestStory("./complete_induction.equations", EXPRESSION_RN_TO_DEC_COMPARISONS);
                printf("Testing/Proof complete!\r\n\r\n");  
                break;
                
            case MANUAL_ENTRY:
                manualEntry();
                break;

            case QUIT:
                exit = 1;
                break;

            default:
                printf("Input not recognized, try again...\r\n");
                break;
        }

    }

}

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

static char getAlphanumericChar(){
    char input;
    
    //Only accept standard alphanumeric characters -- discard new lines, carriage returns, etc
    do{
        input = getchar();
    }while(input < '!' || input > '~');

    return input;
}

static bool isNumericChar(char * input){
    return ( (*input >= '0') && (*input <= '9'));
}

static void flushInput(){
    char input;
    
    do{
        input = getchar();
    }while(input != '\r' && input !='\n');

}


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


static void doManualOperation(ROMAN_NUMERAL_OPERATION * romanNumeralOperation){
    printf("Input Operand 1: ");
    if(getValue(romanNumeralOperation->operand1, rnc_is_roman_character)){ //Get a roman numeral value
        printf("Input Operand 2: ");
        if(getValue(romanNumeralOperation->operand2, rnc_is_roman_character)){ //Get a roman numeral value
                
                if(rnc_perform_operation(romanNumeralOperation)){
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


static void doDecimalToRomanNumeral(){
    char input[MAX_ROMAN_NUMERAL_CHARACTERS];
    int decimalValue;

    printf("Input Decimal Integer: ");

    if(getValue(input, isNumericChar)){ //get decimal value as a string
        decimalValue = atoi(input); //Convert string to int
        if(decimal_to_roman_numeral(decimalValue, input)){
            printf("\r\nResult: %d is %s in roman numerals\r\n\r\n", decimalValue, input);
        }else{
            printf("Error: unable to convert decimal value to roman numeral value\r\n");
        }
    }else{
        printf("Error: Unable to read in decimal value from command line\r\n");
    }
}

static void doRomanNumeralToDecimal(){
    char input[MAX_ROMAN_NUMERAL_CHARACTERS];
    int decimalValue;
    printf("Input Roman Numeral: ");
    if(getValue(input, rnc_is_roman_character)){ //get a roman numeral value

        if(decimalValue = roman_numeral_to_decimal(input)){
            printf("\r\nResult: %s is %d in decimal\r\n\r\n", input, decimalValue);
        }else{
            printf("Error: Invalid input for roman numeral value\r\n");
        }

    }else{
        printf("Error: Invalid input for roman numeral value\r\n");
    }

}

