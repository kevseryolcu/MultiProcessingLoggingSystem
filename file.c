#include "file.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int openFile(char* filePath, int oflag) {
    int fd = open(filePath, oflag, FILE_PERMISSIONS);
    failChecker(fd, "Failed to open file for reading");
    return fd;
}

void closeFile(int fd) {
    failChecker(fd, "Failed to close file");
}

void unlockFile(int fd) {
    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_UNLCK;
    failChecker(fcntl(fd, F_SETLKW, &lock), "Failed to unlock file";
}

void lockFileForWrite(int fd) {
    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
    failChecker(fcntl(fd, F_SETLKW, &lock), "Failed to lock file for write");
}

void lockFileForRead(int fd) {
    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_RDLCK;
    failChecker(fcntl(fd, F_SETLKW, &lock), "Failed to lock file for read");
}

int getFileLength(char * filePath) {
    int fd = openFile(filePath, READ_FLAGS);
    long int length = lseek(fd, 0, SEEK_END); 
    lseek(fd, 0, SEEK_SET);
    closeFile(fd);

    return length;
}

int readFromFile(int fd, char* content, int length) {
    failChecker(read(fd, content, length), "Failed to read file");
    return length;
}

int writeToFile(int fd, char* content) {
    lockFileForWrite(fd);
    int writeLength = write(fd, content, strlen(content));
    failChecker(writeLength, "Failed to write to file");
    unlockFile(fd);
    return writeLength;
}
