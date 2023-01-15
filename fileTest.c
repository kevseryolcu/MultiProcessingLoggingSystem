#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "file.h"
#include "utils.h"

#define MAX_PATH_LEN 256

int main(int argc, char* argv[]) {
    char filePath[MAX_PATH_LEN];
    char* fileContent;
    int opt;

    while((opt = getopt(argc, argv, ":f:")) != -1) 
    { 
        switch(opt) 
        { 
            case 'f':
                strcpy(filePath, optarg);
                break;
            default:
                fprintf(stderr, "Invalid argument\n");
                fprintf(stderr, "Usage: ./fileTest -f <filePath>\n");
                return -1;
        } 
    }
    
    fprintf(stdout, "Starting program %s with argument %s\n", argv[0], filePath);

    int fileLength = getFileLength(filePath);
    fileContent = (char*)malloc(sizeof(char*)*fileLength);

    int fd = openFile(filePath, READ_FLAGS);
    int readLength = readFromFile(fd, fileContent, fileLength);
    closeFile(fd);

    fprintf(stdout, "Content:\n %s", fileContent);
    
    fprintf(stdout, "Finished program %s with argument %s\n", argv[0], fileContent);

    return 0;
}
