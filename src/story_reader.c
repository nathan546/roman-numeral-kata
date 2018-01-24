#include <stdio.h>
#include <stdlib.h>
#include "story_reader.h"

TEST_STORY * story_create(char * file){
   
   int fileNameLength = strlen(file);

   if(fileNameLength < 256){
      TEST_STORY * story = malloc(sizeof(TEST_STORY));
      if(story != NULL){
         memcpy(story->file, file, fileNameLength);
         story->fp = NULL;
         return story;
      }
   }else{
      return NULL;
   }
   

}

bool story_open(TEST_STORY * story){
   if(story->fp == NULL){
      story->fp = fopen(story->file, "r");
      return 1;
   }else{
      return 0;
   }
}

int story_read_line(TEST_STORY * story){
   int count = fgets(story->readBuffer, sizeof(story->readBuffer), story->fp);
   return count;
}

bool story_close(TEST_STORY * story){

   fclose(story->fp);
   free(story);

}
