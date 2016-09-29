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
#define SEND_PORT 32000
//#define RECV_PORT 30000
#define MAXSLEEPTIME 5

int CreateSocket();
int SendMessage(socketStr sockStr);
struct sockaddr_in CreateAddrStr(int port);

int main(int argc, char *argv[]) {

    socketStr sockStr;
    sockStr.sock = CreateSocket();
    sockStr.addrStr = CreateAddrStr(SEND_PORT);
    pthread_t threadID;

    pthread_create(&threadID, NULL, ReceiveMessage, &sockStr);
    SendMessage(sockStr);
    return 0;
}

int SendMessage(socketStr sockStr) {
    int id = 0;
    qMessage message;
    int length;

    for(int i=0; i<100; i++) {
        srand(time(NULL) + pthread_self());
        length = (rand() % MAXSTRINGSIZE) + 1;
        for (int j = 0; j < length; j++) {
            message.payload[j] = 65 + (rand() % 57);
        }
        message.payload[length] = '\0';
        message.id = id;
        message.proc = -1;

        if (sendto(sockStr.sock, &message, sizeof(message), 0, (struct sockaddr *) &sockStr.addrStr, sizeof(sockStr.addrStr)) != sizeof(message)) {
            perror("sendto()");
            return -1;
        }
        printf("Message sent!\t\t%d::%s\n", message.id, message.payload);
        id++;

        sleep((rand() % MAXSLEEPTIME) + 1);
    }
    return 0;
}

int CreateSocket(){
    int sock, flag;
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        fprintf(stderr, "socket() failed\n");
        return -1;
    }

    flag = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *) &flag, sizeof (flag)) < 0) {
        fprintf(stderr, "setsockopt() failed\n");
        return -1;
    }
    return sock;
}

struct sockaddr_in CreateAddrStr(int port) {
    struct sockaddr_in addrStr;

    memset(&addrStr, 0, sizeof (addrStr));
    addrStr.sin_family = AF_INET;
    addrStr.sin_addr.s_addr = inet_addr(IP_ADDR);
    addrStr.sin_port = htons(port);

    return addrStr;
}