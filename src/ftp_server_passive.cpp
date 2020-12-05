/**
 * @file: ftp_server_passive.cpp
 * @author: Ayush, 656665809, F20N02, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: Nov 30, 2020
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
  #include "ftp_server_net_util.hpp"
  #include "ftp_server_connection_listener.hpp"
  #include "ftp_server_request.hpp"
  #include "ftp_server_response.hpp"
  #include "ftp_server_passive.hpp"
  #include "ftp_server_connection.hpp"
  #include "ftp_server_string_util.hpp"
  using namespace std;

 void enteringIntoPassive(const int controlSockDescriptor, int& passiveListenerSockDescriptor, int& dataSockDescriptor)
 {

   bool succeeded = false;
   bool isError = false;
   bool isTimedout = false;
	 char* response = new char[FTP_RESPONSE_MAX_LENGTH];

	startPassiveListener(passiveListenerSockDescriptor, succeeded);
	if(succeeded)
	{
    createPassiveSuccessResponse(response, passiveListenerSockDescriptor);
		sendToRemote(controlSockDescriptor, response, strlen(response));
    if(isListenerSocketReady(passiveListenerSockDescriptor, DATA_CONNECTION_TIME_OUT_SEC, DATA_CONNECTION_TIME_OUT_USEC, isError, isTimedout))
    {
      acceptClientConnection(passiveListenerSockDescriptor, dataSockDescriptor);
      sendToRemote(controlSockDescriptor, DATA_CONNECTION_SUCCESS_RESPONSE, strlen(DATA_CONNECTION_SUCCESS_RESPONSE));
      closeListenerSocket(passiveListenerSockDescriptor);
    }
	}
  free(response);
 }




 void startPassiveListener(int& listenerSockDescriptor, bool& succeded)
 {

  char* response = new char[FTP_RESPONSE_MAX_LENGTH];
  string s = PASSIVE_DEFAULT_PORT;
  strcpy(response, s.c_str());
	startListenerSocket(response, listenerSockDescriptor, succeded);

}


 void createPassiveSuccessResponse(char* response, const int passiveListenerSockDescriptor)
 {

  int port;
  char* ip;
	port = getPortFromSocketDescriptor(passiveListenerSockDescriptor);
  int x = port%256;
  int y = port/256;
	ip = getHostIPAddress();
  replaceAll(ip, '.', ',');
  sprintf(response, PASSIVE_SUCCESS_RESPONSE, ip,y, x);

 }
