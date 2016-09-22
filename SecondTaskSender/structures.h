//
// Created by russell on 20.09.16.
//

#ifndef SECONDTASKSENDER_STRUCTURES_H
#define SECONDTASKSENDER_STRUCTURES_H

#define MAXSTRINGSIZE 60

typedef struct {
    char payload[MAXSTRINGSIZE];
    int id;
    int proc;
} qMessage;

typedef struct {
    int sock;
    struct sockaddr_in addrStr;
} socketStr;

#endif //SECONDTASKSENDER_STRUCTURES_H
