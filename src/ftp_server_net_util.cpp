/**
 * @file: ftp_server_net_util.cpp
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

 	int ready = select(sockDescriptor+1, &listenerReadySet, NULL, NULL, &socketTimeOutValue);
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

 		return true;

 }




 char* getHostIPAddress()
 {
 	size_t hn_length = 256;
 	char hostname[hn_length];
 	gethostname(hostname, hn_length);
	char *hostIP;
	struct hostent *host;
	gethostname(hostname, hn_length);
	host = gethostbyname(hostname);
	hostIP = inet_ntoa(*((struct in_addr*) host->h_addr_list[0]));
	return hostIP;

 }
