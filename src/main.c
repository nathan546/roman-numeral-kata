#include <stdlib.h>
#include <stdio.h>
#include <check.h>

#include "main.h"

int main(void){

    char input;

    printf("\r\nWelcome to Roman Numeral Calculator Kata\r\n");
    printf("\t1) Run Addition Test Story\r\n");
    printf("\t2) Run Subtraction Test Story\r\n");
    printf("\t3) Manually Enter Roman Numeral Expression\r\n");
    printf("\t4) Quit\r\n\r\n");

    while(1){

        printf("Enter Option From Menu: ");

        //Only accept standard ASCII characters -- discard new lines, carriage returns, etc
        do{
            input = getchar();
        }while(input < '!' || input > '~');

        //Perform input action
        switch(input){

            case ADDITION_STORY:
                performTestStory("./story_addition.equations");
                break;

            case SUBTRACTION_STORY:
                performTestStory("./story_subtraction.equations");
                break;

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

