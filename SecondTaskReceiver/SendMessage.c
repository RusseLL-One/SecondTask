//
// Created by russell on 20.09.16.
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socketStruct.h"
#include "queue.h"
#include "SendMessage.h"

void *SendMessage(void *thrStr) {
    socketStr *sharedStr = (socketStr *) thrStr;
    qMessage *sendMessage;

    for(;;) {
        if ((sendMessage = get(sharedStr->finQueue, 10)) == NULL) {
            fprintf(stderr, "SendMessage.c: get() failed\n");
            sleep(1);
            continue;
        }

        if (sendto(sharedStr->sock, (void*)sendMessage, sizeof(*sendMessage), 0, (struct sockaddr *) &sharedStr->sndrAddrStr, sizeof(sharedStr->sndrAddrStr)) != sizeof(*sendMessage)) {
            fprintf(stderr, "SendMessage.c: sendto() failed\n");
            sleep(1);
            continue;
        }
        free(sendMessage);
    }
}