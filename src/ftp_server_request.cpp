/**
 * @file: ftp_server_command.cpp
 * @author: Ayush, 656665809, F20N02, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: NOV 06, 2020
 *
 */
 #include <iostream>
 #include <string>
 #include <list>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/types.h>
 #include <sys/time.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <netdb.h>
 #include <algorithm>
 #include "ftp_server_nlist.hpp"
 #include "ftp_server_request.hpp"
 #include "ftp_server_retrieve.hpp"
 #include "ftp_server_response.hpp"
 #include "ftp_server_passive.hpp"
 #include "ftp_server_connection.hpp"
 #include <signal.h>
 #include <iomanip>
 #include <cstring>
 #include <cstdlib>


using namespace std;

void interpreteCommand(char* command, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isUser, bool& isLoggedIn, const char* rootDir)
{

}

void parseCommandLine(char* commandLine, char* command, char* argument)
{

}

 void handleCommandUSER(char* username, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isUser)
 {/*
   const int size = 1024;
   char cmd[size];
   memset(cmd, 0, sizeof(char)*size);
   sendToRemote(controlSockDescriptor, cmd, size);
   if((strcmp(*username, DEFAULT_USERNAME)) == 0)
   {
     isUser = true;
   }
   else
   {
     closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
   }
   sendToRemote(controlSockDescriptor, cmd, size);*/
 }

 void handleCommandPASS(char* password, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isUser, bool& isLoggedIn)
 {/*
   const int size = 1024;
   char cmd[size];
   memset(cmd, 0, sizeof(char)*size);
   if(isUser != true)
   {
     sendToRemote(controlSockDescriptor, cmd, size);
     handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
   }
  if((strcmp(*password, DEFAULT_PASSWORD)) == 0)
  {
    isLoggedIn = true;
    sendToRemote(controlSockDescriptor, cmd, size);
  }
  else
  {
    sendToRemote(controlSockDescriptor, cmd, size);
    handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
  }*/
 }

 void handleCommandPWD(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
 {/*
 	if(!isLoggedIn)
 	{
 		handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
 	}
 	else
 	{
 		const int size = 1024;
 		char cmd[size];
 		memset(cmd, 0, sizeof(char)*size);
 		sendToRemote(controlSockDescriptor, cmd, size);
 	}*/
 }

 void handleCommandCWD(char* directory, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
 {/*
 	if(!isLoggedIn)
 	{
 		handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
 	}
 	else
 	{
 		const int size = 1024;
 		char cmd[size];
 		memset(cmd, 0, sizeof(char)*size);
 		sendToRemote(controlSockDescriptor, cmd, size);
 	}*/
 }


 void handleCommandCDUP(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn, const char* rootDir)
 {/*
 	if(!isLoggedIn)
 	{
 		handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
 	}
 	else
 	{
 		const int size = 1024;
 		char cmd[size];
 		memset(cmd, 0, sizeof(char)*size);
 		sendToRemote(controlSockDescriptor, cmd, size);
 	}*/
 }
 void handleCommandPASV(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
 {

 }

 void handleCommandNLST(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
 {

 }

 void handleCommandRETR(char* argument, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
 {

 }



 void handleCommandQUIT(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor,bool& isClientConnected)
 {/*
 	const int size = 1024;
 	char cmd[size];
 	memset(cmd, 0, sizeof(char)*size);
 	closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
 	sendToRemote(controlSockDescriptor, cmd, size);*/
 }

 void handleCommandUnSupported(const int controlSockDescriptor)
 {/*
 	const int size = 1024;
 	char cmd[size];
 	memset(cmd, 0, sizeof(char)*size);
 	sendToRemote(controlSockDescriptor, cmd, size);*/
 }

 void handleNotLoggedIn(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected)
 {/*
 	const int size = 1024;
 	char cmd[size];
 	memset(cmd, 0, sizeof(char)*size);
 	closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
 	sendToRemote(controlSockDescriptor, cmd, size);*/
 }
