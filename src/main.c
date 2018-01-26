#include <stdlib.h>
#include <stdio.h>
#include <check.h>

#include "main.h"
#include "roman_numeral_calculator.h"

int main(void){

    char input;

    printf("\r\nWelcome to Roman Numeral Calculator Kata\r\n");
    printf("\t1) Run Addition Test Story\r\n");
    printf("\t2) Run Subtraction Test Story\r\n");
    printf("\t3) Run Complete Induction Test Story\r\n");
    printf("\t4) Manually Enter Roman Numeral Expression\r\n");
    printf("\t5) Quit\r\n\r\n");

    while(1){

        printf("Enter Option From Menu: ");

        //Only accept standard ASCII characters -- discard new lines, carriage returns, etc
        do{
            input = getchar();
        }while(input < '!' || input > '~');

        //Perform input action
        switch(input){

            case ADDITION_STORY:
                performTestStory("./story_addition.equations", EXPRESSION_RN_OPERATIONS);
                break;

            case SUBTRACTION_STORY:
                performTestStory("./story_subtraction.equations", EXPRESSION_RN_OPERATIONS);
                break;

            case COMPLETE_INDUCTION:

                printf("Explanation...\r\n");

                performTestStory("./complete_induction.equations", EXPRESSION_RN_TO_DEC_COMPARISONS);

            case MANUAL_ENTRY:
                return EXIT_SUCCESS;
                break;

            case QUIT:
                return EXIT_SUCCESS;
                break;

            default:
                printf("Input not recognized, try again...\r\n");
                break;
        }

    }

}

