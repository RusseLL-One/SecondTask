//
// Created by russell on 13.09.16.
//

#ifndef FIRSTTASK_QUEUE_H
#define FIRSTTASK_QUEUE_H

#define QUEUE_SIZE 15
#define MAX_STRING_SIZE 60
#define MAX_THREADS_PER_QUEUE 10

#include <pthread.h>

typedef struct {
    char payload[MAX_STRING_SIZE];
    int id;
    int proc;
} qMessage;

typedef struct { // Mutex для синхронизации очереди
    pthread_mutex_t mutex;
    pthread_cond_t recvCond;
    pthread_cond_t sndrCond;
    int threadPuts[MAX_THREADS_PER_QUEUE+1];
    int threadGets[MAX_THREADS_PER_QUEUE+1];
    qMessage messages[QUEUE_SIZE];
    int count;
} queueStr;

void init(queueStr *queue);

int put(queueStr *queue, qMessage elem);

qMessage *get(queueStr *queue, int threadID);

#endif //FIRSTTASK_QUEUE_H
