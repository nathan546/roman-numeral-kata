
/*******************************************************************
* 
*
* DESCRIPTION :     Create a roman numeral test list... this is a list of
*                   expressions (I+I=II) or comparisons(1=I) that can be parsed
*                   in from a story file and cross-checked for validity with our
*                   roman numeral calculator
*
* PROCESS :
*                   [1]  Create a roman numeral test list
*                   [2]  Parse a story file into the list
*                   [3]  Confirm operations/comparisons from story file pass/fail
*                   [4]  Destroy roman numeral test list
*
* NOTES :           Seg faults from character positions > MAX_ROMAN_NUMERAL_CHARACTERS not checked yet
*                   Discard characters that are not roman
*
* CHANGES :
*             DATE                  WHO                    DETAIL
*      August 26, 2018     Nathan Barrett Morrison      Original Code
*
*/


#include "roman_numeral_operations_list.h"
#include "story_reader.h"


//Description:      Create a new contiguous roman numeral operation list
//Input Parameters: Size of desired roman numeral operation list
//Return:           Success - Pointer to roman numeral operation list of size listSize
//                  Failure - NULL pointer
ROMAN_NUMERAL_OPERATION * rntList_create(int listSize){
    ROMAN_NUMERAL_OPERATION * romanNumeralTestList;
    romanNumeralTestList = calloc(listSize * sizeof(ROMAN_NUMERAL_OPERATION), 1); //clearing malloc to ensure
                                                                                  //we start with empty strings by
                                                                                  //default in the ROMAN_NUMERAL_OPERATON
                                                                                  //structure
    return romanNumeralTestList;
}

//Description:      Destroy a roman numeral operation list
//Input Parameters: Pointer to roman numeral operation list to destroy
//Return:           Always true guarantee (for now)
bool rntList_destroy(ROMAN_NUMERAL_OPERATION * romanNumeralTestList){
    free(romanNumeralTestList);
    romanNumeralTestList = NULL;
    return 1;
}



//Description:      For parsing story files into a roman numeral test list
//Input Parameters: romanNumeralTestList - Pointer to roman numeral operation list
//                  fileName - String containing path to story file
//                  expressionType - Type of expression we're attepting to parse (I+I=II, II-I=I) or (1=I)
//Return:           Success - true
//                  Failure - false
bool rntList_parse(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, char * fileName, EXPRESSION_TYPE expressionType){
    TEST_STORY * story;
    bool ret = 1;

    //Create a new story pointer
    story = story_create(fileName);
    if(story == NULL){
        printf("Error: Unable to create story, error number %d\r\n", errno);
        ret = 0;
    }

    //Open the story
    if(!story_open(story)){
        printf("Error: Unable to open story, error number %d\r\n", errno);
        ret = 0;
    }

    //Make sure there were no create/open errors
    if(ret){

        switch(expressionType){
            case EXPRESSION_RN_OPERATIONS: //Parse a I+I=II type expression into our list

                if(!rntList_parseOperations(romanNumeralTestList, fileName, story)){
                    printf("Error: Unable to parse story file - aborting test...\r\n");
                    ret = 0;
                }

                break;
            case EXPRESSION_RN_TO_DEC_COMPARISONS: //Parse a 1=I type expression into our list

                if(!rntList_parseComparisons(romanNumeralTestList, fileName, story)){
                    printf("Error: Unable to parse story file - aborting test...\r\n");
                    ret = 0;
                }

                break;
        }


    }

    //Free up story-related memory structures
    if(!story_close(story)){
        printf("Error: Unable to close story, error number %d\r\n", errno);
        ret = 0;
    }

    return ret;

}


//Description:      Checks whether an roman numeral operation or comparison is valid
//Input Parameters: romanNumeralTestList - Pointer to roman numeral operation list
//                  expressionType - Type of expression we're attepting to parse (I+I=II, II-I=I) or (1=I)
//Return:           Success - true
//                  Failure - false
bool rntList_operation_valid(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, EXPRESSION_TYPE expressionType){
    bool ret = 0;

    switch(expressionType){
        case EXPRESSION_RN_OPERATIONS: //Check if a I+I=II type expression matches our calculator's results
            ret = rnc_perform_operation(romanNumeralTestList);
            break;
        case EXPRESSION_RN_TO_DEC_COMPARISONS: //Check if a 1=I type expression matches our calculator's results
            ret = rnc_perform_comparison(romanNumeralTestList);
            break;
    }

    return ret;
}

//Description:      For parsing expressions/operations such as I+I=II in from a story file
//Input Parameters: romanNumeralTestList - Pointer to roman numeral operation list
//                  fileName - String containing path to story file
//                  story - Pointer to test story reader for reading in story file
//Return:           Success - true
//                  Failure - false
static bool rntList_parseOperations(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, char * fileName, TEST_STORY * story){

    int listPosition = 0, lineLength;
    int i, j; //iterators, i for the current character position in each line
              //           j for the current character position in the post-parsed buffers (operand1, operand2, result)
    char currentChar;
    bool ret = 1;
    STORY_PARSE_STATE parseState;

    //1) Iterate through each line of the story
    //   While doing so
    //      2) Store each character into operand1 portion of current list position until a + or - is encountered
    //      3) Store the + or - operand into the operand portion of the list structure
    //      4) Store each character following a + or - into operand2 until an = is encountered
    //      5) Store each character following the = into result until an end of line, comment, or end of file is encountered
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
                        currentChar == '\0' || //end of file
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

//Description:      For parsing comparsions such as 1=I in from a story file
//Input Parameters: romanNumeralTestList - Pointer to roman numeral operation list
//                  fileName - String containing path to story file
//                  story - Pointer to test story reader for reading in story file
//Return:           Success - true
//                  Failure - false
static bool rntList_parseComparisons(ROMAN_NUMERAL_OPERATION * romanNumeralTestList, char * fileName, TEST_STORY * story){

    int listPosition = 0, lineLength;
    int i, j; //iterators, i for the current character position in each line
              //           j for the current character position in the post-parsed buffer (operand1)
    char currentChar;
    bool ret = 1;
    STORY_PARSE_STATE parseState;


    //1) Iterate through each line of the story
    //   While doing so
    //      2) Store each character into operand1 portion of current list position until an = is encountered
    //      3) After = is encountered, convert operand1 into a decimal value and store it in the decimalComparator portion
    //         of the current list position
    //      4) Store each character following a = back into operand1, starting at the beginning of operand1 again
    //      5) Continue 4) until new line, comment, or end of file is encountered
    while(story_read_line(story)){
        lineLength = strlen(story->readBuffer)+1; //Also process null termination
        
        parseState = OPERAND_1;

        for(i = 0, j = 0; i < lineLength; i++){
            currentChar = story->readBuffer[i];

            //If we see a line ending, null termination, space, or semicolon - consider the line complete and move on to the next line
            if( currentChar == '\r' ||
                currentChar == '\n' ||
                currentChar == '\0' || //end of file
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

