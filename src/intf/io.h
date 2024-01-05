#pragma once
#define FILENAME_MAX_LENGTH 128
#define BUFFER_SIZE 512

typedef struct {
    char name[FILENAME_MAX_LENGTH];
    int size;
    char data[BUFFER_SIZE];
} File;

void initializeFile(File* file,const char* name);
void writeFile(File* file,const char* data,int size);
void readFile(File* file,char* buffer,int size);