/**
 * @file: ftp_server_connection.cpp
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
 using namespace std;
 #include "ftp_server_net_util.hpp"




 int sendToRemote(const int sockDescriptor, const char* message, const int messageLength)
 {
 	return send(sockDescriptor, message, messageLength, 0);
 }


 //Returns true if there is any data sent by the remote computer on the stream socket represented by 'sockDescriptor'.
 //Waits for the data until 'timeoutSec' + 0.000001x'timeoutUsec' time.
 //If no data has been received before the time out, sets 'isTimedout' value to 'true'.
 //If any error occurs, sets 'isError' value to 'true'.
 //Calls 'isSocketReadyToRead()' function from 'ftp_server_net_util.hpp' to do all of the above.
 bool isConnectionReadyToRead(const int sockDescriptor, const int timeoutSec, const int timeoutUSec, bool& isError, bool&isTimedout)
 {
 	return isSocketReadyToRead(sockDescriptor, timeoutSec, timeoutUSec, isError, isTimedout);
 }



 //Receives data from the remote computer into a buffer 'message'.
 //Sets the length of the received data into 'messageLength'.
 //Uses a stream socket, represented by 'sockDescriptor', to receive the data.
 int receiveFromRemote(const int sockDescriptor, char* message, int messageLength)
 {
 	return recv(sockDescriptor, message, messageLength, 0);
 }


 //Closes the stream socket, represented by 'sockDescriptor'.
 void closeConnection(int& sockDescriptor)
 {
 	closeSocket(sockDescriptor);
 }



 //Closes all the stream sockets, represented by 'controlSockDescriptor', 'dataListenerSockDescriptor', and 'dataSockDescriptor'.
 //Sets 'false' to 'isClientConnected'.
 void closeAllConnections(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected)
 {
 	closeConnection(controlSockDescriptor);
 	closeConnection(dataListenerSockDescriptor);
 	closeConnection(dataSockDescriptor);
 	isClientConnected = false;
 }
