
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
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

    int sockFd = 0, valread, clientFd;
    struct sockaddr_in serv_addr;
    char* message = "Hello from client";
    char buffer[1024] = {0};

    if (argc != 3) {
        fprintf(stderr, "Usage ./fileTest -f <fileName>");
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
                fprintf(stderr, "Usage: ./fileTest -f <filePath>\n");
                return -1;
        } 
    }
    
    fprintf(stderr, "Starting program %s with argument %s\n", "./fileTest", filePath);


    failChecker(sockFd = socket(AF_INET, SOCK_STREAM, 0), "Failed to open socket!");
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    failChecker(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr), "Invalid address/ address not supported");
    failChecker((clientFd = connect(sockFd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) ), "Connection failed");

    send(sockFd, message, strlen(message), 0);
    printf("Hello message sent\n");
    valread = read(sockFd, buffer, 1024);
    printf("%s\n", buffer);
 
    // closing the connected socket
    close(clientFd);


    /*
    int fd = createFile(filePath);
    while (count++ < LIMIT) {
        struct tm newtime;
        time_t ltime;
        
        ltime=time(&ltime);
        localtime_r(&ltime, &newtime);

        sprintf(line, "CL %d %s", count, asctime_r(&newtime, timeBuffer));

        writeToFile(fd, line);
        sleep(1);
    }
    closeFile(fd);
    */
    
    fprintf(stdout, "Finished program %s with argument %s\n", argv[0], filePath);

    return 0;
}