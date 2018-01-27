//TO DO: License
//       README.md
//       Flow chart

#include <stdlib.h>
#include <stdio.h>
#include <check.h>

#include "main.h"
#include "roman_numeral_calculator.h"
#include "check_roman_numeral_calculator.h"
#include "roman_numeral_operations_list.h"

char getAlphanumericChar(){
    char input;
    
    //Only accept standard alphanumeric characters -- discard new lines, carriage returns, etc
    do{
        input = getchar();
    }while(input < '!' || input > '~');

    return input;
}

void flushInput(){
    char input;
    
    do{
        input = getchar();
    }while(input != '\r' && input !='\n');

}

bool getRomanNumeralValue(char * input){
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
            //Only keep roman numeral characters (M, D, C, ...)
            if(rnc_is_roman_character(&input[i])){
                i++;
            }else{
                flushInput();
                break;
            }     
        }

    }while(!doneParsing);

    return doneParsing;
}


void doManualOperation(ROMAN_NUMERAL_OPERATION * romanNumeralOperation){
    printf("Input Operand 1: ");
    if(getRomanNumeralValue(romanNumeralOperation->operand1)){
        printf("Input Operand 2: ");
        if(getRomanNumeralValue(romanNumeralOperation->operand2)){
                rnc_perform_operation(romanNumeralOperation);
                printf("\r\nResult: %s %c %s = %s\r\n\r\n", romanNumeralOperation->operand1,
                                                            romanNumeralOperation->operator,
                                                            romanNumeralOperation->operand2,
                                                            romanNumeralOperation->result);
        }else{
            printf("Error:  Invalid input for operand2");
        }
    }else{
        printf("Error:  Invalid input for operand1");
    }
}


void manualEntry(){
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
                    break;
                case MANUAL_RN_TO_DEC:
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
                performTestStory("./story_addition.equations", EXPRESSION_RN_OPERATIONS);
                break;

            case SUBTRACTION_STORY:
                performTestStory("./story_subtraction.equations", EXPRESSION_RN_OPERATIONS);
                break;

            case COMPLETE_INDUCTION: 
                printf("%s\r\n", completeInductionDescript);
                performTestStory("./complete_induction.equations", EXPRESSION_RN_TO_DEC_COMPARISONS);
                printf("Proof complete!\r\n\r\n");  
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



