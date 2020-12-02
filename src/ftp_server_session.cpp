#include "ftp_server_session.hpp"
#include "ftp_server_connection.hpp"
#include "ftp_server_response.hpp"
#include "ftp_server_request.hpp"
#include <unistd.h>
#include <string.h>
#include <limits.h>

#include "ftp_server_response.hpp"
#include "ftp_server_retrieve.hpp"

#include <iostream>
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
  cout<<"\nHEY1234\n";
  char* rootDir = new char[PATH_MAX], *message = new char[FTP_RESPONSE_MAX_LENGTH];
  getcwd(rootDir, sizeof(rootDir));
  sendToRemote(controlSockDescriptor, CONNECTED_RESPONSE, strlen(CONNECTED_RESPONSE));
  cout<<"\nHEY12\n";
  while(isConnectionReadyToRead(controlSockDescriptor, FTP_CLIENT_SESSION_TIMEOUT_SEC, FTP_CLIENT_SESSION_TIMEOUT_USEC, isError, isTimedOut))
  {
    cout<<"\nHEY\n";
  	receiveFromRemote(controlSockDescriptor, message, strlen(message));
    //cout<<"\n\n"<<message<<"\t"<<strlen(message)<<"\n\n";
    interpreteCommand(message, controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isUser, isLoggedIn, rootDir);
  }
  closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
  if(isTimedOut)
  {
  	sendToRemote(controlSockDescriptor, PASSIVE_ERROR_TIMEOUT_RESPONSE, strlen(PASSIVE_ERROR_TIMEOUT_RESPONSE));
    closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
  }
  else if(isTimedOut)
  {
  	sendToRemote(controlSockDescriptor, PASSIVE_ERROR_RESPONSE, strlen(PASSIVE_ERROR_RESPONSE));
    closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
  }
    //closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
}
