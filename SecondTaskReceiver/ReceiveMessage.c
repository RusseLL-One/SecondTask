//
// Created by russell on 19.09.16.
//
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include "ReceiveMessage.h"
#include "socketStruct.h"
#include "queue.h"


void *ReceiveMessage(void *thrStr) {

    socketStr *sharedStr = (socketStr *) thrStr;
    int counter = 0;
    socklen_t len = sizeof (sharedStr->sndrAddrStr);
    qMessage message;

    for (; ;) {
        if (recvfrom(sharedStr->sock, &message, sizeof (message), 0, (struct sockaddr *) &sharedStr->sndrAddrStr, &len) < 0) {
            fprintf(stderr, "ReceiveMessage.c: recvfrom() failed\n");
            sleep(1);
            continue;
        }
        counter++;

        message.proc=8;
        if (put(sharedStr->initQueue, message) < 0) {
            fprintf(stderr, "ReceiveMessage.c: put() failed\n");
            sleep(1);
            continue;
        }

        printf("Message received! %d:%d:%s\n", message.id, message.proc, message.payload);

    }
}