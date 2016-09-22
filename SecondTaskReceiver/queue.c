//
// Created by russell on 13.09.16.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void init(queueStr *queue) {
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->recvCond, NULL);
    pthread_cond_init(&queue->sndrCond, NULL);
    for(int i=0; i<=MAX_THREADS_PER_QUEUE; i++) {
        queue->threadPuts[i] = 0;
        queue->threadGets[i] = 0;
    }
    queue->count = 0;
}

int put(queueStr *queue, qMessage elem) {

    pthread_mutex_lock(&queue->mutex);
    if (queue->count >= QUEUE_SIZE) {
        printf("Generator waiting...\n");
        pthread_cond_wait(&queue->sndrCond, &queue->mutex);
        if (queue->count >= QUEUE_SIZE) {
            pthread_mutex_unlock(&queue->mutex);
            return -1;
        }
        printf("Generator is good to go\n");
    }
    queue->count++;
    queue->threadPuts[elem.proc]++;
    memcpy(&queue->messages[queue->count - 1], &elem, sizeof(elem));

    printf("\n");
    for (int i = 0; i < queue->count; i++) printf("%d: %s\n", i + 1, queue->messages[i].payload);
    printf("\n");

    pthread_mutex_unlock(&queue->mutex);
    pthread_cond_signal(&queue->recvCond);
    return 0;
}

qMessage *get(queueStr *queue, int threadID) {
    pthread_mutex_lock(&queue->mutex);
    if (queue->count <= 0) {
        printf("Receiver waiting...\n");
        pthread_cond_wait(&queue->recvCond, &queue->mutex);
        if (queue->count <= 0) {
            pthread_mutex_unlock(&queue->mutex);
            return NULL;
        }
        printf("Receiver is good to go\n");
    }
    qMessage *msg;
    msg = malloc(sizeof(qMessage));
    memcpy(msg, &queue->messages[0], sizeof(queue->messages[0]));
    memset(&queue->messages[0], 0, sizeof(queue->messages[0]));

    for (int i = 0; i < queue->count - 1; i++) {
        memcpy(&queue->messages[i], &queue->messages[i + 1], sizeof(queue->messages[0]));
    }
    memset(&queue->messages[queue->count - 1], 0, sizeof(queue->messages[queue->count - 1]));

    queue->count--;
    queue->threadGets[threadID]++;
    pthread_mutex_unlock(&queue->mutex);
    pthread_cond_signal(&queue->sndrCond);
    return msg;
}