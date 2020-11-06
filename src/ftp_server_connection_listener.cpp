/**
 * @file: ftp_server_connection_listener.cpp
 * @author: Ayush, 656665809, F20N02, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: NOV 06, 2020
 *
 */


  #include <iostream>
  #include <stdlib.h>
  #include <unistd.h>
  #include <string.h>
  #include <sys/types.h>
  #include <sys/time.h>
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <netdb.h>
  #include "ftp_server_net_util.hpp"


  using namespace std;


 void startListenerSocket(char* port, int& listenerSockDescriptor, bool& succeded)
 {
 	size_t hn_length = 256;
 	char hostname[hn_length];
 	gethostname(hostname, hn_length);

 	struct addrinfo hints;
 	memset(&hints, 0, sizeof(struct addrinfo));
 	hints.ai_flags = AI_PASSIVE;
 	hints.ai_family = AF_UNSPEC;
 	hints.ai_socktype = SOCK_STREAM;

 	struct addrinfo* results;
   	int x;
   	x = getaddrinfo(hostname, port, &hints, &results);
 	if(x != 0)
 	{
 		cerr<<"Can't get address info."<<endl;
 		exit(1);
 	}
 	int listenerSocket = -1;
 	char* listenerSocketIP = NULL;
 	struct addrinfo* result = results;
 	while(result != NULL)
 	{
 		listenerSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
 		if(listenerSocket != -1)
 		{
 			int optValue = 1;
 			if(setsockopt(listenerSocket, SOL_SOCKET, SO_REUSEADDR, &optValue, sizeof(int)) == 0)
 			{
 				if(bind(listenerSocket, result->ai_addr, result->ai_addrlen) == 0)
 				{
 					struct sockaddr_in* addrinfo_Address = (struct sockaddr_in*)result->ai_addr;
 					listenerSocketIP = inet_ntoa(addrinfo_Address->sin_addr);
 					break;
 				}
 			}
 			close(listenerSocket);
 			listenerSocket = -1;
 		}
 		result = result->ai_next;
 	}

 	freeaddrinfo(results);
 	if(listenerSocket == -1 || result == NULL)
 	{
 		cerr<<"Can't open and bind listener socket."<<endl;
 		exit(1);
 	}
 	const int backLog = 5;
 	listen(listenerSocket, backLog);
 	listenerSockDescriptor = listenerSocket;
 	succeded = true;

 }




 //Returns true if there is any remote connection request on the listener socket represented by 'sockDescriptor'.
 //Waits for a connection request until 'timeoutSec' + 'timeoutUsec' time.
 //If no connection request has been received before the time out, sets 'isTimedout' value to 'true'.
 //If any error occurs, sets 'isError' value to 'true'.
 //Calls 'isSocketReadyToRead()' function from 'ftp_server_net_util.hpp' to do all of the above.

 bool isListenerSocketReady(const int sockDescriptor, const int timeoutSec, const int timeoutUSec, bool& isError, bool&isTimedout)
 {
 	return isSocketReadyToRead(sockDescriptor, timeoutSec, timeoutUSec, isError, isTimedout);
 }





 //Accepts a connection request on the listener socket represented by 'listenerSockDescriptor'.
 //Opens the connection to the remote computer and represents the connection by 'clientSockDescriptor'.
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




 //Closes the listener socket represented by 'listenerSockDescriptor'.
 void closeListenerSocket(int& listenerSockDescriptor)
 {
 	close(listenerSockDescriptor);
 }
