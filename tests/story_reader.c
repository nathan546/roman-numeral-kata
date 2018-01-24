#include "story_reader.h"

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

bool story_open(TEST_STORY * story){
   short attemptCount = 0;

   if(story->fp == NULL){

      do{
         story->fp = fopen(story->file, "r");
      }while(story->fp == NULL && attemptCount++ < 10);
      
      if(story->fp != NULL)
         return 1;

   }

   return 0;
}

bool story_read_line(TEST_STORY * story){
   if(story->fp == NULL){
      return 0;
   }

   if(fgets(story->readBuffer, sizeof(story->readBuffer), story->fp) != NULL){
      return 1;
   }else{
      return 0;
   }
}

bool story_close(TEST_STORY * story){
   fclose(story->fp);
   free(story);
   return 1;
}

int story_peek_lines(TEST_STORY * story){

   story_open(story);

   char currentChar;
   int numberLines = 0;

   while(!feof(story->fp)){
      currentChar = fgetc(story->fp);
      if(currentChar == '\n'){
         numberLines++;
      }
   }

   story_close(story);

   return numberLines;
}