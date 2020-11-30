#include "ftp_server_session.hpp"
#include "ftp_server_connection.hpp"
#include "ftp_server_response.hpp"
#include "ftp_server_request.hpp"
#include <unistd.h>
#include <string.h>
#include <limits.h>


#include <iostream>













void startClientFTPSession(int& controlSockDescriptor){
  bool isClientConnected = true;
  bool isUser = false;
  bool isLoggedIn = false;
  int dataSocketDescriptor = -1;
  int dataListenerSockDescriptor = -1;
  bool isError = false;
  bool isTimedout = false;















  char rootDir[PATH_MAX];
  if(getcwd(rootDir, sizeof(rootDir)) == NULL){
    std::cout << "Error: " << strerror(errno) << std::endl;
    exit(1);
  }
  char * response = strdup(CONNECTED_RESPONSE);
  size_t responseSize = sizeof(char)*strlen(response);
  sendToRemote(controlSockDescriptor, response, responseSize);
  free(response);

  //int ret = -1;
  //int len = 0;
  const int bufferSize = 1024;
  char buffer[bufferSize] = "0";
  //char buff [1024];
  char * msg;
  memset(buffer, 0, sizeof(char)*bufferSize);


   while(isConnectionReadyToRead(controlSockDescriptor, FTP_CLIENT_SESSION_TIMEOUT_SEC, FTP_CLIENT_SESSION_TIMEOUT_USEC, isError, isTimedout) == true){


      //ret = receiveFromRemote(controlSockDescriptor, buff, 1024 );
      receiveFromRemote(controlSockDescriptor, buffer, sizeof(char)*bufferSize);
      //check if receive error?

      msg = buffer;
      interpreteCommand(msg, controlSockDescriptor, dataListenerSockDescriptor, dataSocketDescriptor , isClientConnected, isUser, isLoggedIn, rootDir);
      memset(buffer, 0, bufferSize);
  }

  closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor,dataSocketDescriptor, isClientConnected);//??
   if(isTimedout == true){

	sendToRemote(controlSockDescriptor, PASSIVE_ERROR_TIMEOUT_RESPONSE, sizeof(PASSIVE_ERROR_TIMEOUT_RESPONSE));
	closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSocketDescriptor, isClientConnected);

      }else if(isError == true){


	sendToRemote(controlSockDescriptor, PASSIVE_ERROR_RESPONSE, sizeof(PASSIVE_ERROR_TIMEOUT_RESPONSE));
        closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSocketDescriptor, isClientConnected);





   }

   closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSocketDescriptor, isClientConnected);

}
/*
//Starts a client FTP session against a client control connection represented by 'controlSockDescriptor'.
//Keeps track of the states of the session using various local variables including 'controlSockDescriptor'\
.
//Other local variables that a session needs to maintain are as follows:
//      isClientConnected = true
//      isUser = false
//      isLoggedIn = false
//      dataSocketDescriptor = -1
//      dataListenerSockDescriptor = -1
//      rootDir
//Determines the root directory of the FTP server and sets it to the local variable 'rootDir'
//Passes the references of the local variables in various function calls, the called functions then sets
//the appropriate value to these variables.
//Waits for client's FTP request for FTP_CLIENT_SESSION_TIMEOUT_SEC + 0.000001xFTP_CLIENT_SESSION_TIMEOUT_\
USEC time
//calling 'isConnectionReadyToRead()' function from 'ftp_server_connection.hpp'.
//If a request comes before the timeout, reads the request.
//Interprets the request, takes appropriate action, and sends appropriate response to the client by callin\
g
//'interpreteCommand()' function from 'ftp_server.command.hpp'.
//If timeout or error happens before a FTP request comes, sends an appropriate response to the client
//and closes all connections calling 'closeAllConnections()' function from 'ftp_server_connection.hpp'.
//Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send response to the client.
*/
