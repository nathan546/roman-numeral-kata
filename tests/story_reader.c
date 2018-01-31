
/*******************************************************************
* 
*
* DESCRIPTION :     Create a basic file reader for opening, reading, and closing story files
*
* PROCESS :
*                   [1]  Create a TEST_STORY pointer
*                   [2]  Peek lines if needed for preallocation of memory
*                   [3]  Open the test story
*                   [4]  Read lines until empty
*                   [4]  Close the test story
*
* NOTES :           None
*
* CHANGES :
*             DATE                  WHO                    DETAIL
*      August 26, 2018     Nathan Barrett Morrison      Original Code
*
*/


#include "story_reader.h"


//Description:      Create a new story reader to read in a story file
//Input Parameters: file - String containing path to story file
//Return:           Success - Pointer to a new test story
//                  Failure - NULL pointer
TEST_STORY * story_create(char * file){
   int fileNameLength = strlen(file);

   if(fileNameLength < MAX_FILE_NAME_LENGTH){
      TEST_STORY * story = malloc(sizeof(TEST_STORY));
      if(story != NULL){
         memcpy(story->file, file, fileNameLength+1); //make sure to copy the null termination!
         story->fp = NULL;
         return story;
      }
   }else{
      return NULL;
   }
}


//Description:      Open a story reader's file
//Input Parameters: story - Pointer to test story to open
//Return:           Success - true
//                  Failure - false
bool story_open(TEST_STORY * story){
   if(story->fp == NULL){
      story->fp = fopen(story->file, "r");
      if(story->fp != NULL)
         return 1;
   }

   return 0;
}


//Description:      For parsing story files into a roman numeral test list
//Input Parameters: romanNumeralTestList - Pointer to roman numeral operation list
//                  fileName - String containing path to story file
//                  expressionType - Type of expression we're attepting to parse (I+I=II, II-I=I) or (1=I)
//Return:           Success - true
//                  Failure - false
bool story_read_line(TEST_STORY * story){
   char * result;
   bool ret = 0;
   bool endLoop = 0;
   short maxAttempts = 10;

   if(story->fp != NULL){

      //Iteratively read in lines until we get end of file or line length > MINIMUM_OPERATION_CHARACTERS
      do{
         result = fgets(story->readBuffer, sizeof(story->readBuffer), story->fp);
         if(result != NULL){
            if(strlen(story->readBuffer) > MINIMUM_OPERATION_CHARACTERS){
               ret = 1;
               break; //Line length was > MINIMUM_OPERATION_CHARACTERS
            }
         }else{
            break; //End of file
         }
      }while(1);
   }

   return ret;
}


//Description:      Close a test story file
//Input Parameters: Pointer to test story to close
//Return:           Always true guarantee (for now)
bool story_close(TEST_STORY * story){
   fclose(story->fp);
   free(story);
   return 1;
}


//Description:      Peek at a test story file and return the number of lines
//                  which have > MINIMUM_OPERATION_CHARACTERS in them
//Input Parameters: Pointer to test story file to peek at
//Return:           Success: Number of lines found
//                  Failure: 0
int story_peek_lines(char * file){
   char currentChar;
   int characterCount = 0;
   int numberLines = 0;
   TEST_STORY * tempStory;

   //Create a new temporary test story pointer
   tempStory = story_create(file);
   if(tempStory == NULL){
      printf("Unable to create story, error number %d\r\n", errno);
   }else{
      //Open story
      story_open(tempStory);
      
      //Parse out lines by looking for CR or LF characters to indicate line endings
      while(!feof(tempStory->fp)){
         currentChar = fgetc(tempStory->fp);
         characterCount++;
         if(currentChar == '\n' || currentChar == '\r'){
            if(characterCount > MINIMUM_OPERATION_CHARACTERS) //Only count it as a line if line length > MINIMUM_OPERATION_CHARACTERS
               numberLines++;
            characterCount = 0;
         }
      }

      if(characterCount > MINIMUM_OPERATION_CHARACTERS){ //We have one last line without a line ending (CR) 
         numberLines++;
      }

      //Close the story
      story_close(tempStory);
   }

   //Return the number of lines we found!
   return numberLines;
}