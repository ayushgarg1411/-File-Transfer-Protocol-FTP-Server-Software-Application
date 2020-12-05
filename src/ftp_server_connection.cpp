/**
 * @file: ftp_server_connection.cpp
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
 #include "ftp_server_connection.hpp"

 using namespace std;




 int sendToRemote(const int sockDescriptor, const char* message, const int messageLength)
 {
 	return send(sockDescriptor, message, messageLength, 0);
 }



 bool isConnectionReadyToRead(const int sockDescriptor, const int timeoutSec, const int timeoutUSec, bool& isError, bool&isTimedout)
 {
 	return isSocketReadyToRead(sockDescriptor, timeoutSec, timeoutUSec, isError, isTimedout);
 }



 int receiveFromRemote(const int sockDescriptor, char* message, int messageLength)
 {
 	return recv(sockDescriptor, message, messageLength, 0);
 }





 void closeConnection(int& sockDescriptor)
 {
 	closeSocket(sockDescriptor);
 }





 void closeAllConnections(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected)
 {
 	closeConnection(controlSockDescriptor);
 	closeConnection(dataListenerSockDescriptor);
 	closeConnection(dataSockDescriptor);
 	isClientConnected = false;
 }
