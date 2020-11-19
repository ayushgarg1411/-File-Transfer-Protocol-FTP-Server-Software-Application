/**
 * @file: ftp_server_session.cpp
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
 #include "ftp_server_net_util.hpp"
 #include "ftp_server_connection_listener.hpp"
 #include "ftp_server_session.hpp"
 #include "ftp_server_nlist.hpp"
 #include "ftp_server_request.hpp"
 #include "ftp_server_retrieve.hpp"


 void startClientFTPSession(int& controlSockDescriptor)
 {
 	bool isClientConnected = true;
     bool& isUser = false;
     bool& isLoggedIn = false;
     const int dataSocketDescriptor = -1;
     const int dataListenerSockDescriptor = -1;
     rootDir;
     isClientConnected = isConnectionReadyToRead(controlSockDescriptor, FTP_CLIENT_SESSION_TIMEOUT_SEC, FTP_CLIENT_SESSION_TIMEOUT_USEC, isUser, isLoggedIn);
     if(isClientConnected)
     {
     	const int size = 1024;
 		char cmd[size];
 		memset(cmd, 0, sizeof(char)*size);
     	interpreteCommand(cmd, controlsockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isUser, isLoggedIn, rootDir);
 	}
 	else
 	{
 		if(isClientConnected == -1)
 			printf("Error in checking readiness of connection socket\n");
 		else if(isClient Connected == 0)
 			printf("Timed out without a request\n");
 		closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
 	}
 }
