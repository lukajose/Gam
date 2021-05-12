#include <iostream>
#include "mempool.h"
#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h>
#include <sys/time.h>
#define TRUE   1 
#define FALSE  0 
#define PORT 8888


MemPool::MemPool(int connSize) {
    this->maxClients = connSize;
    this->clientSockets = new int[connSize];
    memset(this->clientSockets,0,connSize);
    this->clientIndex = 0;
};

int MemPool::listenTransactions() {
    // create a socket
    int masterSocket = socket(AF_INET,SOCK_STREAM,0);
    if(masterSocket == -1) {
        std::cerr << "Cant create a socket!" << std::endl;
        return -1;
    };
    //set of socket descriptors 
    fd_set readfds;
    

    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this
    int opt = TRUE; 
    if( setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  {  
        perror("setsockopt");  
        return FALSE;
    };
    // bind the socket to an IP port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_addr.s_addr = INADDR_ANY;
    hint.sin_port = htons(PORT);
    // pointer to a string to a number 127.0.0.1
    inet_pton(AF_INET,"0.0.0.0",&hint.sin_addr);
    int bindStats = bind(masterSocket, (struct sockaddr *)&hint, sizeof(hint));
    if(bindStats == -1) {
        std::cerr << "Cant bind to port!" << std::endl;
        return FALSE;
    }
    //specify the maximum number of max connections (128)
    if(listen(masterSocket,SOMAXCONN)) {
        std::cerr << "Exceeded number of max connections" << std::endl;
        return FALSE;
    };
  
   
    while(TRUE) {
        ///clear the socket set 
        FD_ZERO(&readfds);  
     
        //add master socket to set 
        FD_SET(master_socket, &readfds);  
        max_sd = master_socket;  
             
        //add child sockets to set 
        for ( i = 0 ; i < this->maxClients ; i++)  {  
            //socket descriptor 
            sd = this->clientSockets[i];  
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0) FD_SET( sd , &readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno!=EINTR)) {  
            printf("select error");  
        }


        send(clientSocket,buff,bytesRecv + 1, 0);

    }
    // close socket
    close(clientSocket);
    return TRUE;
};