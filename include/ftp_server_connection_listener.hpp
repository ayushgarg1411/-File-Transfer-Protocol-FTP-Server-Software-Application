/**
 * @file: ftp_server_connection_listener.hpp
 * @author: Humayun Kabir, Instructor, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: June 22, 2020
 *
 */


#ifndef __FTP_SERVER_CONNECTION_LISTENER_HEADER__
#define __FTP_SERVER_CONNECTION_LISTENER_HEADER__

#define MAX_CLIENT_CONNECTIONS 10

void startListenerSocket(char* port, int& listenerSockDescriptor, bool& succeded);
//Starts a listener socket that can listen connection requests from the remote computer.
//Creates a stream socket and binds it to a local IP address and to the given port number.
//Once the binding is successful listens for connection request from the remote computers.

bool isListenerSocketReady(const int sockDescriptor, const int timeoutSec, const int timeoutUSec, bool& isError, bool&isTimedout);
//Returns true if there is any remote connection request on the listener socket represented by 'sockDescriptor'.
//Waits for a connection request until 'timeoutSec' + 'timeoutUsec' time.
//If no connection request has been received before the time out, sets 'isTimedout' value to 'true'.
//If any error occurs, sets 'isError' value to 'true'.
//Calls 'isSocketReadyToRead()' function from 'ftp_server_net_util.hpp' to do all of the above.

void acceptClientConnection(const int listenerSockDescriptor, int& clientSockDescriptor);
//Accepts a connection request on the listener socket represented by 'listenerSockDescriptor'.
//Opens the connection to the remote computer and represents the connection by 'clientSockDescriptor'.

void closeListenerSocket(int& listenerSockDescriptor);
//Closes the listener socket represented by 'listenerSockDescriptor'.

#endif
