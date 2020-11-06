/**
 * @file: ftp_server_net_util.cpp
 * @author: Ayush, 656665809, F20N02, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: NOV 06, 2020
 *
 */

 #include <iostream>
 #include <string>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/types.h>
 #include <sys/time.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <netdb.h>
 #include <algorithm>
 #include "../include/ftp_server_net_util.hpp"

 using namespace std;


 //Closes the stream socket, represented by 'sockDescriptor'.
 void closeSocket(int& sockDescriptor)
 {
 	close(sockDescriptor);
 }



 //Determines and returns the associated port number from a given socket descriptor.
 int getPortFromSocketDescriptor(const int sockDescriptor)
 {
   struct sockaddr_in sin;
   socklen_t len = sizeof(sin);

   if (getsockname(sockDescriptor, (struct sockaddr *)&sin, &len) == -1)
       perror("getsockname");

   return ntohs(sin.sin_port);

 }



 //Returns true if there is any data sent by the remote computer on the stream socket represented by 'sockDescriptor'.
 //Waits for the data until 'timeoutSec' + 0.000001x'timeoutUsec' time.
 //If no data has been sent before the time out, sets 'isTimedout' value to 'true'.
 //If any error occurs, sets 'isError' value to 'true'.
 bool isSocketReadyToRead(const int sockDescriptor, const int timeoutSec, const int timeoutUSec, bool& isError, bool& isTimedout)
 {
   fd_set listenerReadySet;
   FD_ZERO(&listenerReadySet);
   FD_SET(sockDescriptor, &listenerReadySet);
 	struct timeval socketTimeOutValue;
 	socketTimeOutValue.tv_sec = timeoutSec;
 	socketTimeOutValue.tv_usec = timeoutUSec;

 	int ready = select(sockDescriptor, &listenerReadySet, NULL, NULL, &socketTimeOutValue);
 	if(ready == -1)
 	{
 		isError = true;
     return false;
 	}
 	else if(ready == 0)
 	{
 		isTimedout = true;
     return false;
 	}
 	else
 		return true;

 }




 //Determines and returns an IP address of the local host.
 char* getHostIPAddress()
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
   char* port = strdup("2020");
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
 	return listenerSocketIP;
 }
