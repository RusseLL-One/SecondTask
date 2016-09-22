//
// Created by russell on 20.09.16.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "queue.h"
#include "socketStruct.h"
#include "MessageAddSpaces.h"

void *MessageAddSpaces(void *thrStr) {
    const int THREAD_ID=2;
    srand(time(NULL) + THREAD_ID);
    sleep(rand() % MAX_SLEEP_TIME);
    socketStr *queue = (socketStr *) thrStr;
    qMessage *initMessage;
    qMessage finMessage;
    for (; ;) {
        if ((initMessage = get(queue->initQueue, THREAD_ID)) == NULL) {
            fprintf(stderr, "MessageAddSpaces.c: get() failed\n");
            sleep(1);
            continue;
        }
        printf("Spaces added! ID=%d %s\n", THREAD_ID, initMessage->payload);

        for(int i=0; i<strlen(initMessage->payload)*2; i+=2) {
            finMessage.payload[i] = initMessage->payload[i/2];
            finMessage.payload[i+1] = ' ';
        }
        finMessage.payload[(strlen(initMessage->payload)*2)-1] = '\0';

        finMessage.id = initMessage->id;
        finMessage.proc = THREAD_ID;

        if (put(queue->finQueue, finMessage) < 0) {
            fprintf(stderr, "MessageAddSpaces.c: put() failed\n");
            sleep(1);
            continue;
        }

        free(initMessage);
        sleep((rand() % MAX_SLEEP_TIME) + 1);
    }
}