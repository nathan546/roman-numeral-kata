//TO DO: License
//       README.md
//       Flow chart

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

                printf("\r\n\tIn theory -- Proof By Complete Induction (Brute Force) \r\n\r\n");
                printf("\t    With the exception of number system's overflows (>3999), underflows (<=0), and invalid user inputs,\r\n");
                printf("\t    we can prove our roman numeral calculator works in all cases by proving that it can convert from:\r\n");
                printf("\t       - Any decimal value (1-3999) to the correct roman numeral value (I to MMMCMXCIX)\r\n");
                printf("\t       - Any roman numeral value (I to MMMCMXCIX) to the correct decimal value (1-3999) \r\n");
                printf("\t    If these two cases can be proven, then we can convert any roman numeral inputs to their decimal equivalents,\r\n");
                printf("\t    perform basic decimal addition/subtraction on them, and then convert the result back to a roman numeral equivalent\r\n\r\n"); 
                printf("\t    The file, complete_induction.equations contains 3999 lines (of the form 1=I, 2=II, etc) that provide an input for this proof\r\n\r\n");    

                performTestStory("./complete_induction.equations", EXPRESSION_RN_TO_DEC_COMPARISONS);

                printf("\r\nProof complete!\r\n\r\n");  

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

