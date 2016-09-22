#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include "ReceiveMessage.h"
#include "structures.h"

#define IP_ADDR "127.0.0.1"
#define PORT 32000

#define MAXSLEEPTIME 5

int CreateSocket();
int SendMessage(socketStr sockStr);
struct sockaddr_in CreateAddrStr();

int main(int argc, char *argv[]) {

    socketStr sockStr;
    sockStr.sock = CreateSocket();
    sockStr.addrStr = CreateAddrStr();
    pthread_t threadID;

    pthread_create(&threadID, NULL, ReceiveMessage, &sockStr);
    SendMessage(sockStr);
}

int SendMessage(socketStr sockStr) {
    int id = 0;
    qMessage message;
    int length;

    for(int i=0; i<100; i++) {
        srand(time(NULL) + pthread_self());
        length = (rand() % MAXSTRINGSIZE) + 1;
        for (int i = 0; i < length; i++) {
            message.payload[i] = 65 + (rand() % 57);
        }
        message.payload[length] = '\0';
        message.id = id;
        message.proc = -1;

        if (sendto(sockStr.sock, &message, sizeof(message), 0, (struct sockaddr *) &sockStr.addrStr, sizeof(sockStr.addrStr)) != sizeof(message)) {
            fprintf(stderr, "sendto() failed\n");
            return -1;
        }
        printf("Message sent!\t\t%d::%s\n", message.id, message.payload);
        id++;

        sleep((rand() % MAXSLEEPTIME) + 1);
    }
}

int CreateSocket(){
    int sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        fprintf(stderr, "socket() failed\n");
        return -1;
    }
    return sock;
}

struct sockaddr_in CreateAddrStr() {
    struct sockaddr_in addrStr;

    memset(&addrStr, 0, sizeof (addrStr)); /* Заполняем структуру нулями */
    addrStr.sin_family = AF_INET; /* Internet address family */
    addrStr.sin_addr.s_addr = inet_addr(IP_ADDR); /* Broadcast IP address */
    addrStr.sin_port = htons(PORT);/* Broadcast port */

    return addrStr;
}