#ifndef __FILE_H
#define __FILE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE_PERMISSIONS 0777
#define READ_FLAGS  (O_RDONLY)
#define WRITE_FLAGS (O_CREAT | O_WRONLY | O_TRUNC)

int openFile(char* filePath, int oflag);
void closeFile(int fd);
void unlockFile(int fd);
void lockFileForWrite(int fd);
void lockFileForRead(int fd);
int getFileLength(char * filePath);
int readFromFile(int fd, char* content, int length);
int writeToFile(int fd, char* content);

#endif
