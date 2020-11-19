/**
 * @file: ftp_server_passive.cpp
 * @author: Name, Student Number, Section, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: June 24, 2020
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
 #include "ftp_server_net_util.hpp"
 #include "ftp_server_connection_listener.hpp"
 #include "ftp_server_session.hpp"
 #include "ftp_server_nlist.hpp"
 #include "ftp_server_request.hpp"
 #include "ftp_server_retrieve.hpp"


 void enteringIntoPassive(const int controlSockDescriptor, int& passiveListenerSockDescriptor, int& dataSockDescriptor)
 {

 }
 //Starts a passive connection listener by calling 'startPassiveListener()' function.
 //Once successful on the above function call, sends an appropriate response to the client.
 //Waits for a specific time interval to receive a client's connection request on the listener by calling
 //isListenerSocketReady() from 'ftp_server_connection_listener.hpp'.
 //Accepts client's connection request, if there is any, and opens a data connection with the client by calling
 //'acceptClientConnetion() function from 'ftp_server_connection_listener.hpp'.
 //Closes the connection listener after opening the data connection by calling 'closeListenerSocket()'
 //function from 'ftp_server_connection_listener.hpp'.
 //Sends appropriate response to the client using control connection.
 //Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send response to client.

 void startPassiveListener(int& listenerSockDescriptor, bool& succeded)
 {

 }
 //Starts a passive listener socket that can listen connection requests from the remote computer.
 //by calling 'startListenerSocket()' function from 'ftp_server_connection_listener.hpp'.


 void createPassiveSuccessResponse(char* response, const int passiveListenerSockDescriptor)
 {

 }
 //Creates a Passive success response.
 //Determines the passive listener port number from 'passiveListenerSockDescriptor' by calling
 //'getPortFromSocketDescriptor()' function from 'ftp_server_net_util.hpp'.
 //Determines the local IP address by calling 'getHostIPAddress()' function from 'ftp_server_net_util.hpp'.
 //Includes both the IP address and the port number into passive success response according to RFC.
