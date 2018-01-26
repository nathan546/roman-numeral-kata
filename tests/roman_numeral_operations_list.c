
#include "roman_numeral_operations_list.h"
#include "story_reader.h"

ROMAN_NUMERAL_OPERATION * rntList_create(int listSize){
    ROMAN_NUMERAL_OPERATION * romanNumeralTestList;
    romanNumeralTestList = calloc(listSize * sizeof(ROMAN_NUMERAL_OPERATION), 1);
    return romanNumeralTestList;
}

//For parsing expressions/operations such as I+I=II
static bool rntList_parseOperations(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, char * fileName, TEST_STORY * story){

    int listPosition = 0, lineLength;
    int i, j; //iterators
    char currentChar;
    bool ret = 1;
    STORY_PARSE_STATE parseState;

    while(story_read_line(story)){
        lineLength = strlen(story->readBuffer)+1; //Also process null termination
        parseState = OPERAND_1;

        for(i = 0, j = 0; i < lineLength; i++){
            currentChar = story->readBuffer[i];

            switch(parseState){

                case OPERAND_1:
                    if(currentChar == '+' || currentChar == '-'){
                        romanNumeralTestList[listPosition].operator = currentChar;
                        j = 0;
                        parseState = OPERAND_2;
                    }else{
                        romanNumeralTestList[listPosition].operand1[j++] = currentChar;

                    }               
                    break;
                case OPERAND_2:
                    if(currentChar == '='){
                        j = 0;
                        parseState = RESULT;
                    }else{
                        romanNumeralTestList[listPosition].operand2[j++] = currentChar;
                    }               
                    break;
                case RESULT:
                    //If we see a line ending, null termination, space, or semicolon - consider the line complete and move on to the next line
                    if( currentChar == '\r' ||
                        currentChar == '\n' ||
                        currentChar == '\0' ||
                        currentChar == ' '  ||
                        currentChar == ';')    {

                            parseState = PARSE_COMPLETE;

                    }else{
                            romanNumeralTestList[listPosition].result[j++] = currentChar;
                    }                   
                    break;
            }
            if(j == MAX_ROMAN_NUMERAL_CHARACTERS){
                printf("Error: Operand on line greater than %d characters\r\n", MAX_ROMAN_NUMERAL_CHARACTERS);
                ret = 0;
                break;
            }

        }

        if(parseState != PARSE_COMPLETE){
            printf("Error: Unable to parse current line from story file\r\n");
            ret = 0;
            break;
        }

        listPosition++;
    }

    return ret;

}

//For parsing comparsions such as 1=I
static bool rntList_parseComparisons(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, char * fileName, TEST_STORY * story){

    int listPosition = 0, lineLength;
    int i, j; //iterators
    char currentChar;
    bool ret = 1;
    STORY_PARSE_STATE parseState;

    while(story_read_line(story)){
        lineLength = strlen(story->readBuffer)+1; //Also process null termination
        
        parseState = OPERAND_1;

        for(i = 0, j = 0; i < lineLength; i++){
            currentChar = story->readBuffer[i];

            //If we see a line ending, null termination, space, or semicolon - consider the line complete and move on to the next line
            if( currentChar == '\r' ||
                currentChar == '\n' ||
                currentChar == '\0' ||
                currentChar == ' '  ||
                currentChar == ';')    {
                
                    romanNumeralTestList[listPosition].operand1[j] = 0;
                    parseState = PARSE_COMPLETE;
                    break;

            }else if(currentChar == '='){
                romanNumeralTestList[listPosition].decimalComparator = atoi(romanNumeralTestList[listPosition].operand1);
                j = 0;

            }else{

                romanNumeralTestList[listPosition].operand1[j++] = currentChar;

            }
        }

        if(parseState != PARSE_COMPLETE){
            printf("Error: Unable to parse current line from story file\r\n");
            ret = 0;
            break;
        }

        listPosition++;
    }

    return ret;
}

bool rntList_parse(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, char * fileName, EXPRESSION_TYPE expressionType){
    TEST_STORY * story;
    bool ret = 1;

    story = story_create(fileName);
    if(story == NULL){
        printf("Error: Unable to create story, error number %d\r\n", errno);
        ret = 0;
    }

    if(!story_open(story)){
        printf("Error: Unable to open story, error number %d\r\n", errno);
        ret = 0;
    }

    if(ret){

        switch(expressionType){
            case EXPRESSION_RN_OPERATIONS:

                if(!rntList_parseOperations(romanNumeralTestList, fileName, story)){
                    printf("Error: Unable to parse story file - aborting test...\r\n");
                    ret = 0;
                }

                break;
            case EXPRESSION_RN_TO_DEC_COMPARISONS:

                if(!rntList_parseComparisons(romanNumeralTestList, fileName, story)){
                    printf("Error: Unable to parse story file - aborting test...\r\n");
                    ret = 0;
                }

                break;
        }


    }

    if(!story_close(story)){
        printf("Error: Unable to close story, error number %d\r\n", errno);
        ret = 0;
    }

    return ret;

}

bool rntList_destroy(ROMAN_NUMERAL_OPERATION * romanNumeralTestList){
    free(romanNumeralTestList);
    romanNumeralTestList = NULL;
    return 1;
}

bool rntList_operation_valid(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, EXPRESSION_TYPE expressionType){
    bool ret = 0;

    switch(expressionType){
        case EXPRESSION_RN_OPERATIONS:
            rnc_perform_operation(NULL, romanNumeralTestList->operand1, romanNumeralTestList->operator, romanNumeralTestList->operand2);
            ret = 1; //fixed for now
            break;
        case EXPRESSION_RN_TO_DEC_COMPARISONS:
            ret = rnc_perform_comparison(NULL, romanNumeralTestList->operand1, romanNumeralTestList->decimalComparator);
            break;
    }

    return ret;
}