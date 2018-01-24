#ifndef STORY_READER_H

#define STORY_READER_H

typedef struct{
   char file[256];
   FILE * fp;
   char readBuffer[1024];
}TEST_STORY;

#define bool char

#endif