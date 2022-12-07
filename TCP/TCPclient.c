#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>
#define PORT 1254

int main() {
        int clientSocket,ret;
        struct sockaddr_in serverAddr;
        char buffer[1024];

        clientSocket = socket(AF_INET,SOCK_STREAM,0);
        if (clientSocket<0) printf("error in creating socket\n");

        memset(&serverAddr,'\0',sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        serverAddr.sin_port = htons(PORT);

        ret = connect(clientSocket,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
        if (ret<0) printf("error in connecting to server\n");

        while (1) {
                printf("Enter msg to send to server:");
                bzero(buffer,sizeof(buffer));
                scanf("%s",buffer);
                send(clientSocket,buffer,sizeof(buffer),0);
                bzero(buffer,sizeof(buffer));
                recv(clientSocket,buffer,1024,0);
                printf("msg from server:%s\n",buffer);
        }
        close(clientSocket);
        return 0;
}
