#include "hdr.h"                                                                               
void func(int sockfd)  {                                                                       
        char *filename = "server.txt";                                                         
        char buf[100];                                                                         
        FILE *fd = fopen(filename, "w");                                                       
        if (!fd) return;                                                                       
        while(1)  {                                                                            
                bzero(buf, 100);                                                               
                read(sockfd, buf,sizeof(buf)); //file contents - each line                     
                printf("%s", buf);                                                             
                if (strncmp(buf, "exit", sizeof("exit")) == 0) return ;                        
                fprintf(fd, "%s", buf); //write into file                                      
        }                                                                                      
        fclose(fd);                                                                            
}                                                                                              

int main ()  {                                                                                 
        int sockfd = -1, connfd =-1;                                                           
        sockfd = socket(AF_INET, SOCK_STREAM ,0);                                              
        if (sockfd < 0)  {                                                                     
                printf("Create error"); exit(1);                                               
        }                                                                                      
        struct sockaddr_in server, client;                                                     
        server.sin_family = AF_INET;                                                           
        server.sin_port = htons(PORT);                                                         
        server.sin_addr.s_addr = htonl(INADDR_ANY);                                            

        if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0)  {                    
                printf("Bind error"); exit(1);                                                 
        }                                                                                      
        if (listen(sockfd, 5) < 0)  {                                                          
                printf("Listen error"); exit(1);                                               
        }                                                                                      
        int length = sizeof(client);                                                           
        if ((connfd = accept(sockfd, (struct sockaddr*)&client, &length)) < 0)  {              
                printf("Accept error") ; exit(1);                                              
        }                                                                                      
        printf("Connection established\n");                                                    
        func(connfd);                                                                          
        close(connfd);                                                                         
        close(sockfd);                                                                         
        return 0;                                                                              
}
