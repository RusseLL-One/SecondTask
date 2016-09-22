//
// Created by russell on 20.09.16.
//
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "socketStruct.h"
#include "MessageReverse.h"

void *MessageReverse(void *thrStr) {
    const int THREAD_ID=0;
    srand(time(NULL) + THREAD_ID);
    sleep(rand() % MAX_SLEEP_TIME);
    socketStr *queue = (socketStr *) thrStr;
    qMessage *initMessage;
    qMessage finMessage;
    for (; ;) {
        if ((initMessage = get(queue->initQueue, THREAD_ID)) == NULL) {
            fprintf(stderr, "MessageReverse.c: get() failed\n");
            sleep(1);
            continue;
        }
        printf("Message reversed! ID=%d %s\n", THREAD_ID, initMessage->payload);

        for(int i=0; i<strlen(initMessage->payload); i++) {
            finMessage.payload[i] = initMessage->payload[strlen(initMessage->payload)-i-1];
        }
        finMessage.payload[strlen(initMessage->payload)] = '\0';

        finMessage.id = initMessage->id;
        finMessage.proc = THREAD_ID;

        if (put(queue->finQueue, finMessage) < 0) {
            fprintf(stderr, "MessageReverse.c: put() failed\n");
            sleep(1);
            continue;
        }

        free(initMessage);
        sleep((rand() % MAX_SLEEP_TIME) + 1);
    }
}