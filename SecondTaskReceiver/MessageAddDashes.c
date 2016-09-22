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
#include "MessageAddDashes.h"

void *MessageAddDashes(void *thrStr) {
    const int THREAD_ID=4;
    srand(time(NULL) + THREAD_ID);
    sleep(rand() % MAX_STRING_SIZE);
    socketStr *queue = (socketStr *) thrStr;
    qMessage *initMessage;
    qMessage finMessage;
    for (; ;) {
        if ((initMessage = get(queue->initQueue, THREAD_ID)) == NULL) {
            fprintf(stderr, "MessageAddDashes.c: get() failed\n");
            sleep(1);
            continue;
        }
        printf("Dashes added! ID=%d %s\n", THREAD_ID, initMessage->payload);

        for(int i=0; i<5; i++) {
            finMessage.payload[i] = '-';
        }
        for(int i=0; i<strlen(initMessage->payload); i++) {
            finMessage.payload[i+5] = initMessage->payload[i];
        }
        for(int i=0; i<5; i++) {
            finMessage.payload[i+5+strlen(initMessage->payload)] = '-';
        }
        finMessage.payload[strlen(initMessage->payload)+10] = '\0';

        finMessage.id = initMessage->id;
        finMessage.proc = THREAD_ID;

        if (put(queue->finQueue, finMessage) < 0) {
            fprintf(stderr, "MessageAddDashes.c: put() failed\n");
            sleep(1);
            continue;
        }

        free(initMessage);
        sleep((rand() % MAX_SLEEP_TIME) + 1);
    }
}