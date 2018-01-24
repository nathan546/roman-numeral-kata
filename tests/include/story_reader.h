#ifndef STORY_READER_H

#define STORY_READER_H

typedef struct{
   char file[256];
   FILE * fp;
   char readBuffer[1024];
}TEST_STORY;

#define bool char //boolean

TEST_STORY * story_create(char * file);
bool story_open(TEST_STORY * story);
bool story_read_line(TEST_STORY * story);
bool story_close(TEST_STORY * story);

#endif