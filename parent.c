
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "file.h"
#include "utils.h"

#define LIMIT 1000
#define MAX_PATH_LEN 256

int main(int argc, char* argv[]) {
    char filePath[MAX_PATH_LEN];
    // char* fileContent;
    int opt, count = 0;
    
    char  timeBuffer[50];
    char line[128];

    if (argc != 3) {
        fprintf(stderr, "Usage ./parent -f <fileName>");
        return -1;
    }

    while((opt = getopt(argc, argv, ":f:")) != -1) 
    { 
        switch(opt) 
        { 
            case 'f':
                strcpy(filePath, optarg);
                break;
            default:
                fprintf(stderr, "Invalid argument\n");
                fprintf(stderr, "Usage: ./parent -f <filePath>\n");
                return -1;
        } 
    }
    
    fprintf(stderr, "Starting program %s with argument %s\n", "./fileTest", filePath);

    int fd = createFile(filePath);
    while (count++ < LIMIT) {
        struct tm newtime;
        time_t ltime;
        
        ltime=time(&ltime);
        localtime_r(&ltime, &newtime);

        sprintf(line, "PR %d %s", count, asctime_r(&newtime, timeBuffer));

        writeToFile(fd, line);
        sleep(1);
    }
    closeFile(fd);

    
    fprintf(stdout, "Finished program %s with argument %s\n", argv[0], filePath);

    return 0;
}