#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORT 1254

int main() {
        int sockfd,ret;
        struct sockaddr_in serverAddr;

        int newSocket;
        struct sockaddr_in newAddr;

        socklen_t addr_size;

        char buffer[1024];

        sockfd = socket(AF_INET,SOCK_STREAM,0);
        if (sockfd<0) printf("error creating socket\n");

        memset(&serverAddr,'\0',sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        serverAddr.sin_port = htons(PORT);

        ret = bind(sockfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
        if (ret<0) printf("error in binding socket\n");

        if (listen(sockfd,10)!=0) printf("error in listening\n");

        newSocket = accept(sockfd,(struct sockaddr *)&newAddr,&addr_size);
        if (newSocket<0) printf("error in accepting\n");

        while (1) {
                recv(newSocket,buffer,1024,0);
                if (strcmp(buffer,"exit")==0) break;
                printf("from client:%s\n",buffer);
                bzero(buffer,sizeof(buffer));

                printf("enter msg for client:");
                scanf("%s",buffer);
                send(newSocket,buffer,strlen(buffer),0);
                bzero(buffer,sizeof(buffer));
        }
        close(newSocket);
        return 0;
}
