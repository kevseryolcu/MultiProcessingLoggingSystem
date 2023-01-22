
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
    int count = 0;
    
    char  timeBuffer[50];
    char line[128];
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int opt = 1, newSocket, serverFd, valread;
    char buffer[1024] = { 0 };
    char* hello = "Hello from server";

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

    int protocol = 0;

    failChecker(serverFd = socket(AF_INET, SOCK_STREAM, 0), "Failed to open socket!");
    failChecker (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)), "Failed to set socket options");
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    failChecker(bind(serverFd, (struct sockaddr*)&address, sizeof(address)), "Failed to bind port!");
    failChecker(listen(serverFd, 3), "Failed to listen server socket");
    failChecker((newSocket = accept(serverFd, (struct sockaddr*)&address, (socklen_t*)&addrlen)), "Fa'led to accept socket conn");
    
    valread = read(newSocket, buffer, 1024);
    printf("%s\n", buffer);
    send(newSocket, hello, strlen(hello), 0);
    printf("Hello message sent\n");
 
    // closing the connected socket
    close(newSocket);
    // closing the listening socket
    shutdown(serverFd, SHUT_RDWR);

    /*
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
    */

    
    fprintf(stdout, "Finished program %s with argument %s\n", argv[0], filePath);

    return 0;
}