#include "hdr.h"                                                                                                                               
                                                                                                                                               
void func(int sockfd)  {                                                                                                                       
        char file[100], line[100];                                                                                                             
        printf("Enter filename to send: ");                                                                                                    
        scanf("%s", file);                                                                                                                     
        if (strncmp(file, "exit", sizeof("exit")) == 0)  {                                                                                     
                write(sockfd, "exit", sizeof("exit"));                                                                                         
                return ;                                                                                                                       
        }                                                                                                                                      
        FILE *fd = fopen(file, "r");                                                                                                           
        while(fgets(line, sizeof(line), fd))  {                                                                                                
                printf("%s", line);                                                                                                            
                write(sockfd, line, sizeof(line));                                                                                             
        }                                                                                                                                      
        write(sockfd, "exit", sizeof("exit")); //to make server exit                                                                           
        fclose(fd);                                                                                                                            
}                                                                                                                                              
                                                                                                                                               
int main()  {                                                                                                                                  
        int sockfd = -1;                                                                                                                       
        sockfd = socket(AF_INET, SOCK_STREAM, 0);                                                                                              
        if (sockfd < 0)  {                                                                                                                     
                printf("Create error"); exit(1);                                                                                               
        }                                                                                                                                      
        struct sockaddr_in server;                                                                                                             
        server.sin_family = AF_INET;                                                                                                           
        server.sin_port = htons(PORT);                                                                                                         
        server.sin_addr.s_addr = inet_addr("127.0.0.1");                                                                                       
        if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0)  {                                                                 
                printf("Connect error"); exit(1);                                                                                              
        }                                                                                                                                      
        func(sockfd);                                                                                                                          
        close(sockfd);                                                                                                                         
        return 0;                                                                                                                              
}
