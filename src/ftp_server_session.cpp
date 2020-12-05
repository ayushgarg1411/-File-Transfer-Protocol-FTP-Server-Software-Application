/**
 * @file: ftp_server_session.cpp
 * @author: Ayush, 656665809, F20N02, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: DEC 04, 2020
 *
 */


#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <string.h>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include "ftp_server_session.hpp"
#include "ftp_server_connection.hpp"
#include "ftp_server_response.hpp"
#include "ftp_server_request.hpp"

using namespace std;


void startClientFTPSession(int& controlSockDescriptor)
{
  bool isClientConnected = true;
  bool isUser = false;
  bool isLoggedIn = false;
  bool isError = false;
  bool isTimedOut = false;
  int dataSockDescriptor = -1;
  int dataListenerSockDescriptor = -1;
  char rootDir[PATH_MAX];
  char message[FTP_RESPONSE_MAX_LENGTH];
  memset(message,0,sizeof(char)*FTP_RESPONSE_MAX_LENGTH);
  if(getcwd(rootDir, sizeof(rootDir)) == NULL)
  {
    exit(1);
  }
  sendToRemote(controlSockDescriptor, CONNECTED_RESPONSE, strlen(CONNECTED_RESPONSE));
  bool y = isConnectionReadyToRead(controlSockDescriptor, FTP_CLIENT_SESSION_TIMEOUT_SEC, FTP_CLIENT_SESSION_TIMEOUT_USEC, isError, isTimedOut);

  while(y==true)
  {
    if(receiveFromRemote(controlSockDescriptor, message, sizeof(char)*FTP_RESPONSE_MAX_LENGTH) > 0)
    {
      interpreteCommand(message, controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isUser, isLoggedIn, rootDir);
      memset(message,0, FTP_RESPONSE_MAX_LENGTH);
    }
    else
    {
      closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
      break;
    }

  if(isTimedOut)
  {
  	sendToRemote(controlSockDescriptor, PASSIVE_ERROR_TIMEOUT_RESPONSE, strlen(PASSIVE_ERROR_TIMEOUT_RESPONSE));
    closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
  }
  else if(isError)
  {
  	sendToRemote(controlSockDescriptor, PASSIVE_ERROR_RESPONSE, strlen(PASSIVE_ERROR_RESPONSE));
    closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
  }
}
}
