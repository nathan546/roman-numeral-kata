#ifndef STORY_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "globals.h"

#define STORY_READER_H

#define MAX_FILE_NAME_LENGTH 256       //Maximum length of story file name
#define MAX_LINE_SIZE 256              //Maximum size of each line in story
#define MINIMUM_OPERATION_CHARACTERS 3 //Minimum number of characters to expect in an operation/equation

typedef struct{
   char file[MAX_FILE_NAME_LENGTH];
   char readBuffer[MAX_LINE_SIZE];
   FILE * fp;   
}TEST_STORY;

typedef enum {OPERAND_1, OPERAND_2, RESULT, PARSE_COMPLETE} STORY_PARSE_STATE;

TEST_STORY * story_create(char * file);
bool story_open(TEST_STORY * story);
bool story_read_line(TEST_STORY * story);
bool story_close(TEST_STORY * story);
int story_peek_lines(char * file);

#endif