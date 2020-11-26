/**
 * @file: ftp_server_connection.cpp
 * @author: Ayush, 656665809, F20N02, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: NOV 06, 2020
 *
 */
 #include <iostream>
 #include <string>
 #include <list>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/types.h>
 #include <sys/time.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <netdb.h>
 #include <algorithm>
 #include "ftp_server_net_util.hpp"
 #include "ftp_server_connection.hpp"
 #include <signal.h>
 #include <iomanip>
 #include <cstring>
 #include <cstdlib>


 using namespace std;




 int sendToRemote(const int sockDescriptor, const char* message, const int messageLength)
 {
 	//return send(sockDescriptor, message, messageLength, 0);
 }



 bool isConnectionReadyToRead(const int sockDescriptor, const int timeoutSec, const int timeoutUSec, bool& isError, bool&isTimedout)
 {
 	//return isSocketReadyToRead(sockDescriptor, timeoutSec, timeoutUSec, isError, isTimedout);
 }



 int receiveFromRemote(const int sockDescriptor, char* message, int messageLength)
 {
 	//return recv(sockDescriptor, message, messageLength, 0);
 }





 void closeConnection(int& sockDescriptor)
 {
 	//closeSocket(sockDescriptor);
 }





 void closeAllConnections(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected)
 {/*
 	closeConnection(controlSockDescriptor);
 	closeConnection(dataListenerSockDescriptor);
 	closeConnection(dataSockDescriptor);
 	isClientConnected = false;*/
 }
