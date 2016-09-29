#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"
#include "socketStruct.h"
#include "ReceiveMessage.h"
#include "SendMessage.h"
#include "MessageReverse.h"
#include "MessageAddSpaces.h"
#include "MessageAddDashes.h"
#include "MessageUpper.h"

#define IP_ADDR "127.0.0.1"
#define RECV_PORT 32000

int CreateSocket();
void PrintStats(socketStr *sockStr);

int main(int argc, char *argv[]) {
    socketStr sockStr;
    pthread_t  threadID;

    sockStr.initQueue = malloc(sizeof(queueStr));
    sockStr.finQueue = malloc(sizeof(queueStr));
    init(sockStr.initQueue);
    init(sockStr.finQueue);
    sockStr.sock = CreateSocket();

    pthread_create(&threadID, NULL, ReceiveMessage, &sockStr);

    pthread_create(&threadID, NULL, MessageReverse, &sockStr);
    pthread_create(&threadID, NULL, MessageAddSpaces, &sockStr);
    pthread_create(&threadID, NULL, MessageAddDashes, &sockStr);
    pthread_create(&threadID, NULL, MessageUpper, &sockStr);

    pthread_create(&threadID, NULL, SendMessage, &sockStr);
    sleep(60);
    PrintStats(&sockStr);
    destroy(sockStr.initQueue);
    destroy(sockStr.finQueue);
    return 0;
}

int CreateSocket() {
    int sock;
    int flag;
    struct sockaddr_in addrStr;

    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        fprintf(stderr, "socket() failed\n");
        return -1;
    }

    flag = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *) &flag, sizeof (flag)) < 0) {
        fprintf(stderr, "setsockopt() failed\n");
        return -1;
    }

    memset(&addrStr, 0, sizeof (addrStr));
    addrStr.sin_family = AF_INET;
    addrStr.sin_addr.s_addr = inet_addr(IP_ADDR);
    addrStr.sin_port = htons(RECV_PORT);

    if (bind(sock, (struct sockaddr *) &addrStr, sizeof (addrStr)) < 0) {
        fprintf(stderr, "bind() failed\n");
        return -1;
    }

    return sock;
}

void PrintStats(socketStr *sockStr) {
    printf("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
    printf("Queue №1:\n");
    for (int j = 0; j <= MAX_THREADS_PER_QUEUE; j+=2) { //For each thread
        printf("Thread ID: %d,  Puts: %d,  Gets: %d\n", j, sockStr->initQueue->threadPuts[j], sockStr->initQueue->threadGets[j]);
    }
    printf("--------------------------------------\n");
    printf("Queue №2:\n");
    for (int j = 0; j <= MAX_THREADS_PER_QUEUE; j+=2) { //For each thread
        printf("Thread ID: %d,  Puts: %d,  Gets: %d\n", j, sockStr->finQueue->threadPuts[j], sockStr->finQueue->threadGets[j]);
    }
}