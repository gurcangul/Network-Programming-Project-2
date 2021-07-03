#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define MAXBUFFER 1024 
#define PORT     8080 

  

int main() { 
    int socketFD;   
    int receiveMessage;  
    int lenghtOfMessage; 
    
 
    char buffer[MAXBUFFER]; 
    char *state = ""; 
    struct sockaddr_in serverAddress, clientAddress; 
      

    if ( (socketFD = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
    { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&serverAddress, 0, sizeof(serverAddress)); 
    memset(&clientAddress, 0, sizeof(clientAddress)); 
      
    serverAddress.sin_family    = AF_INET;  
    serverAddress.sin_addr.s_addr = INADDR_ANY; 
    serverAddress.sin_port = htons(PORT); 
    
   
    if ( bind(socketFD, (const struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    lenghtOfMessage = sizeof(clientAddress);  
  
    receiveMessage = recvfrom(socketFD, (char *)buffer, MAXBUFFER, 0, ( struct sockaddr *) &clientAddress,&lenghtOfMessage); 
    buffer[receiveMessage] = '\0'; 
     printf("telnet %s\n", buffer);
    printf("connected...\n");
    
    sendto(socketFD, (const char *)state, strlen(state), 0, (const struct sockaddr *) &clientAddress, lenghtOfMessage); 
    return 0; 
} 
