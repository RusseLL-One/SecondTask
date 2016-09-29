//
// Created by russell on 19.09.16.
//
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "ReceiveMessage.h"
#include "structures.h"

void *ReceiveMessage(void *thrStr) {

    socketStr sharedStr = *(socketStr *) thrStr;
    socklen_t len;
    qMessage message;

    for (; ;) {
        if (recvfrom(sharedStr.sock, &message, sizeof(qMessage), 0, (struct sockaddr *) &sharedStr.addrStr, &len) < 0) {
            fprintf(stderr, "ReceiveMessage.c: recvfrom() failed\n");
            sleep(1);
            continue;
        }

        printf("Message received!\t%d:%d:%s ", message.id, message.proc, message.payload);
        switch(message.proc) {
            case 0:
                printf("(Reversed)\n");
                break;
            case 2:
                printf("(Spaces added)\n");
                break;
            case 4:
                printf("(Dashes added)\n");
                break;
            case 6:
                printf("(Upper Case)\n");
                break;
            default:
                printf("\n");
        }
    }
}