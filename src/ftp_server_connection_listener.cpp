/**
 * @file: ftp_server_connection_listener.cpp
 * @author: Ayush, 656665809, F20N02, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: NOV 06, 2020
 *
 */
 #include <iostream>
 #include <iomanip>
 #include <string>
 #include <list>
 #include <cstring>
 #include <cstdlib>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <netdb.h>
 #include <netinet/in.h>
 #include <sys/types.h>
 #include <unistd.h>
 #include <signal.h>
 #include "ftp_server_net_util.hpp"
 #include "ftp_server_connection_listener.hpp"


  using namespace std;

 void startListenerSocket(char* port, int& listenerSockDescriptor, bool& succeded)
 {

 	
 	struct addrinfo hints;
 	memset(&hints, 0, sizeof(struct addrinfo));
 	hints.ai_flags = AI_PASSIVE;
 	hints.ai_family = AF_UNSPEC;
 	hints.ai_socktype = SOCK_STREAM;

 	struct addrinfo* results;
   	int x;
   	x = getaddrinfo(NULL, port, &hints, &results);

 	if(x != 0)
 	{
 		cerr<<"Can't get address info."<<endl;
 		exit(1);
 	}
 	listenerSockDescriptor = -1;
 	struct addrinfo* result = results;
 	while(result != NULL)
 	{
 		listenerSockDescriptor = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  	if(listenerSockDescriptor != -1)
 		{
    	int optValue = 1;
    	if(setsockopt(listenerSockDescriptor, SOL_SOCKET, SO_REUSEADDR, &optValue, sizeof(int)) == 0)
 			{
      	if(bind(listenerSockDescriptor, result->ai_addr, result->ai_addrlen) == 0)
 				{
      		break;
 				}
 			}
 			close(listenerSockDescriptor);
 			listenerSockDescriptor = -1;
 		}
 		result = result->ai_next;
 	}

 	freeaddrinfo(results);
 	if(listenerSockDescriptor == -1 || result == NULL)
 	{
 		cerr<<"Can't open and bind listener socket."<<endl;
 		exit(1);
 	}
 	const int backLog = 10;
 	listen(listenerSockDescriptor, backLog);
 	succeded = true;

 }




 bool isListenerSocketReady(const int sockDescriptor, const int timeoutSec, const int timeoutUSec, bool& isError, bool&isTimedout)
 {
 	return isSocketReadyToRead(sockDescriptor, timeoutSec, timeoutUSec, isError, isTimedout);
 }





void acceptClientConnection(const int listenerSockDescriptor, int& clientSockDescriptor)
 {
 	struct sockaddr_in connectionAddress;
 	socklen_t socklen = (socklen_t) sizeof(struct sockaddr_in);
 	memset(&connectionAddress, 0, sizeof(struct sockaddr_in));
 	int connectionSocket = -1;
 	connectionSocket = accept(listenerSockDescriptor, (struct sockaddr*)(&connectionAddress), &socklen);
 	if(connectionSocket != -1)
 	{
 		clientSockDescriptor = connectionSocket;
 	}

 }




 void closeListenerSocket(int& listenerSockDescriptor)
 {
 	close(listenerSockDescriptor);
 }
