/* 
 * File:   main.cpp
 * Author: patrik
 *
 * Created on 27. duben 2011, 17:55
 */

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <vector>
#include <pcrecpp.h>

#define PORT 25000
#define DIRSIZE 8192

//#include "Request.h"

using namespace std;
using namespace pcrecpp;
/*
 * 
 */

int main(int argc, char** argv) 
{
    char dir[DIRSIZE]; // Incoming, outgoing data 
    
    int sd, sd_current, cc, fromlen, tolen, addrlen; // integer definitions - using in this scope
    
   
    
    struct sockaddr_in sin; // Structure of socket in
    struct sockaddr_in pin; // Structure of socket pin
    
    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error"); // Throw new error
        exit(1); // kill
    }
    
    // Socket structure
    
    memset(&sin, 0, sizeof(sin)); 
    
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(PORT);
    
    // bind the socket
    if(bind(sd, (struct sockaddr *) &sin, sizeof(sin)) == -1)
    {
        perror("bind error"); // Throw new error
        exit(1); // kill
    }
    
    // If we are able to listen
    if(listen(sd,5) == -1)
    {
        perror("listen error"); // throw new error
        exit(1); // kill
    }
        cout << "Socket stat:  " << sd << "\n" << endl;
    // client accept talk
    do{
    addrlen = sizeof(pin);
    if((sd_current = accept(sd, (struct sockaddr *) &pin, (socklen_t *) &addrlen)) == -1)
    {
        perror("accept error"); //throw new error
        exit(1);
    }
     
    
    if(recv(sd_current, dir, sizeof(dir),0) == -1)
    {
        perror("receive error: ");
        exit(1);
    }
    
    printf("Connection from: %s\n",inet_ntoa(pin.sin_addr));
    //printf("Request: %s\n",dir);
    
    string fst;
    string snd;
    
    //  GET /kill HTTP/1.1  
    pcrecpp::RE regxp("(GET) ([\\w//]+))");
    regxp.PartialMatch(dir, &fst, &snd);
    
    //cout << fst << ":" << snd << endl;
    cout << dir << endl;
    char *httpBody = "<html><head></head><body><h1>It work's</h1></body></html>";
    
    //char *httpHeader = "HTTP/1.1 200 OK\r\nServer: Padik\r\nContent-type: text/html;charset=UTF-8\r\nConnection: Keep-Alive\r\nContent-Length:\r\n";

    if(write(sd_current, httpBody, strlen(httpBody)) == -1)
    {
        perror("write error: ");
        exit(1);
    }
    //printf("%s",httpHeader);
    
    close(sd_current);
   
    }while(true);
     
    // Close sockets 
    
    close(sd_current);
    close(sd);
    
    sleep(1); // Client can properly shutdown
    return 0;
}

