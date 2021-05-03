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
using namespace std;
#define TRUE   1 
#define FALSE  0 
#define PORT 8888 
// #define NI_MAXHOST 128
// #define NI_MAXSVC  128


MemPool::MemPool() {
    
};

int MemPool::listenTransactions() {
    // create a socket
    int masterSocket = socket(AF_INET,SOCK_STREAM,0);
    if(masterSocket == -1) {
        cerr << "Cant create a socket!" << endl;
        return -1;
    };
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this
    int opt = TRUE; 
    if( setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
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

    if(bind(masterSocket, (struct sockaddr *)&hint, sizeof(hint)) == -1) {
        cerr << "Cant bind to port!" << endl;
        return FALSE;
    }
    //specify the maximum number of max connections (128)
    if(listen(masterSocket,SOMAXCONN)) {
        cerr << "Exceeded number of max connections" << endl;
        return FALSE;
    };
    // accept a call
    sockaddr_in client;
    socklen_t clientSize;
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];
    
    int clientSocket = accept(masterSocket,(sockaddr *)&client,&clientSize);
    if(clientSocket == -1) {
        cerr << "Problem with client connecting!" << endl;
        return FALSE; 
    };
    close(masterSocket);
    memset(host,0,NI_MAXHOST);
    memset(svc,0,NI_MAXSERV);
    int result = getnameinfo((sockaddr *)&client,sizeof(client),host,NI_MAXHOST,svc,NI_MAXSERV,0);
    if(result) {
        cout << host << "connected on: " << svc << endl;
    } else {
        inet_ntop(AF_INET,&client.sin_addr,host,NI_MAXHOST);
        cout << host << "connected on :" << ntohs(client.sin_port) << endl;
    }
    char buff[4096];
    while(TRUE) {
        // clear the buffer
        memset(buff,0,4096);
        // wait for a message
        int bytesRecv = recv(clientSocket,buff,4096,0);
        // Display message
        if(bytesRecv == -1) {
            cout << "There was a connection issue " << endl;
            break;
        };
        // Resend message
        if(bytesRecv == 0) {
            cout << "The client disconnected " << endl;
            break;
        };
        cout << "Received : " << string(buff,0,bytesRecv) << endl;
        // resend message
        send(clientSocket,buff,bytesRecv + 1, 0);

    }
    // close socket
    close(clientSocket);
    return TRUE;
};