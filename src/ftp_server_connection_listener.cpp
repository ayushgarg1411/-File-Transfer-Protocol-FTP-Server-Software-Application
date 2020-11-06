/**
 * @file: ftp_server_connection_listener.cpp
 * @author: Name, Student Number, Section, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: June 24, 2020
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
  using namespace std;
#include "ftp_server_net_util.hpp"





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
