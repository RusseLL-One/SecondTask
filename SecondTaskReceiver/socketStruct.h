//
// Created by russell on 19.09.16.
//

#ifndef SECONDTASKRECEIVER_SOCKETSTRUCT_H
#define SECONDTASKRECEIVER_SOCKETSTRUCT_H

#include <arpa/inet.h>
#include "queue.h"

typedef struct {
    int sock;
    struct sockaddr_in sndrAddrStr;
    queueStr *initQueue;
    queueStr *finQueue;
} socketStr;
#endif //SECONDTASKRECEIVER_SOCKETSTRUCT_H
