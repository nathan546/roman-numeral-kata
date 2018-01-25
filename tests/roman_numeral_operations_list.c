
#include "roman_numeral_operations_list.h"
#include "story_reader.h"

ROMAN_NUMERAL_OPERATION * rntList_create(int listSize){
    ROMAN_NUMERAL_OPERATION * romanNumeralTestList;
    romanNumeralTestList = calloc(listSize * sizeof(ROMAN_NUMERAL_OPERATION), 1);
    return romanNumeralTestList;
}

bool rntList_parse(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, char * fileName){
    TEST_STORY * story;
    int listPosition = 0, lineLength;
    int i, j; //iterators
    char currentChar;
    STORY_PARSE_STATE parseState;
    bool ret = 1;

    story = story_create(fileName);
    if(story == NULL){
        printf("Unable to create story, error number %d\r\n", errno);
        ret = 0;
    }

    if(!story_open(story)){
        printf("Unable to open story, error number %d\r\n", errno);
        ret = 0;
    }

    while(ret && story_read_line(story)){
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

bool rntList_operation_valid(ROMAN_NUMERAL_OPERATION * romanNumeralTestList){

    rnc_perform_operation(NULL, romanNumeralTestList->operand1, romanNumeralTestList->operator, romanNumeralTestList->operand2);

    return 1; 
}
