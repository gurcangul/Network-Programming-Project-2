#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <time.h>
#include <sys/types.h> 
#include <sys/socket.h> 

#define MAXBUFFER 1024 
#define PORT     8080 



char *getMonth(int x){
	char *p;
	p=(char *)malloc(5*sizeof(char));
	switch(x)
    	{
    		case 1:
            p="Jan";
            break;
        case 2:
             p="Feb";
            break;
        case 3:
             p="Mar";
            break;
        case 4:
             p="Apr";
            break;
        case 5:
             p="May";
            break;
        case 6:
             p="June";
            break;
        case 7:
             p="July";
            break;
        case 8:
             p="Aug";
            break;
        case 9:
             p="Sep";
            break;
        case 10:
            p="Oct";
            break;
        case 11:
            p="Nov";
            break;
        case 12:
            p="Dec";
            break;
    	}
    	return p;

}


int main() { 

    int socketFD; 
    int lenghtOfMessage; 
    int receiveMessage;


    char buffer[MAXBUFFER]; 
    char *state = "127.0.0.1  5555"; 
    struct sockaddr_in     serverAddress; 
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if ( (socketFD = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 

    } 

    memset(&serverAddress, 0, sizeof(serverAddress)); 
      
   
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(PORT); 
    serverAddress.sin_addr.s_addr = INADDR_ANY; 
      
    sendto(socketFD, (const char *)state, strlen(state), 0, (const struct sockaddr *) &serverAddress, sizeof(serverAddress)); 
          
    receiveMessage = recvfrom(socketFD, (char *)buffer, MAXBUFFER,0, (struct sockaddr *) &serverAddress,&lenghtOfMessage); 

    buffer[receiveMessage] = '\0';

    
    if (state == "127.0.0.1  5555") {

    	printf("It's %s %d %d, Time is: %d:%d:%d\n",  getMonth(tm.tm_mon + 1), tm.tm_mday, tm.tm_year+1900,tm.tm_hour, tm.tm_min, tm.tm_sec); 
	printf("disconnected...\n");
   	
  	}


    close(socketFD); 
    return 0; 
} 
