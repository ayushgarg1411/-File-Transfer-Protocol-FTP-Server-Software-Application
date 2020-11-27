/**
 * @file: ftp_server_session.cpp
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
 #include "ftp_server_session.hpp"
 #include "ftp_server_request.hpp"
 #include "ftp_server_response.hpp"
 #include "ftp_server_connection.hpp"

using namespace std;

 void startClientFTPSession(int& controlSockDescriptor)
 {
 	   bool isClientConnected = true;
     bool isUser = false;
     bool isLoggedIn = false;
     bool isError, isTimedout;
     int dataSockDescriptor = -1;
     int dataListenerSockDescriptor = -1;
     char *rootDir, *cmd;
     getcwd(rootDir, sizeof(rootDir));
     isClientConnected = isConnectionReadyToRead(controlSockDescriptor, FTP_CLIENT_SESSION_TIMEOUT_SEC, FTP_CLIENT_SESSION_TIMEOUT_USEC, isError, isTimedout);
     if(isClientConnected)
     {
     //	const int size = 1024;

 		//memset(cmd, 0, sizeof(char)*size);
     	interpreteCommand(cmd, controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isUser, isLoggedIn, rootDir);
 	}
 	else
 	{
 		closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
 	}
 }
