//
// Created by russell on 20.09.16.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "queue.h"
#include "socketStruct.h"
#include "MessageUpper.h"

void *MessageUpper(void *thrStr) {
    const int THREAD_ID=6;
    srand(time(NULL) + THREAD_ID);
    sleep(rand() % MAX_SLEEP_TIME);
    socketStr *queue = (socketStr *) thrStr;
    qMessage *initMessage;
    qMessage finMessage;
    for (; ;) {
        if ((initMessage = get(queue->initQueue, THREAD_ID)) == NULL) {
            fprintf(stderr, "MessageUpper.c: get() failed\n");
            sleep(1);
            continue;
        }
        printf("Message case upped! ID=%d %s\n", THREAD_ID, initMessage->payload);

        for(int i=0; i<strlen(initMessage->payload); i++) {
            finMessage.payload[i] = toupper(initMessage->payload[i]);
        }
        finMessage.payload[strlen(initMessage->payload)] = '\0';

        finMessage.id = initMessage->id;
        finMessage.proc = THREAD_ID;

        if (put(queue->finQueue, finMessage) < 0) {
            fprintf(stderr, "MessageUpper.c: put() failed\n");
            sleep(1);
            continue;
        }

        free(initMessage);
        sleep((rand() % MAX_SLEEP_TIME) + 1);
    }
}