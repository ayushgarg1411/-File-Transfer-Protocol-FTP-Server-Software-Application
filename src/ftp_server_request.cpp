/**
 * @file: ftp_server_command.cpp
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
 #include <sys/types.h>
 #include <unistd.h>
 #include <signal.h>
 #include <regex>
 #include "ftp_server_nlist.hpp"
 #include "ftp_server_request.hpp"
 #include "ftp_server_retrieve.hpp"
 #include "ftp_server_response.hpp"
 #include "ftp_server_passive.hpp"
 #include "ftp_server_connection.hpp"

using namespace std;

void interpreteCommand(char* command, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isUser, bool& isLoggedIn, const char* rootDir)
{
  char *cmd = new char[COMMAND_BUFFER_SIZE];
  char *arg = new char[COMMAND_ARG_MAX_CHARACTER_COUNT];
  char *directory = strdup(rootDir);
  parseCommandLine(command, cmd, arg);
  string str = cmd;
  if(str == COMMAND_USER)
  {
    handleCommandUSER(arg, controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isUser);
  }
  else if(str == COMMAND_PASSWORD)
  {
      handleCommandPASS(arg, controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isUser, isLoggedIn);
  }
  else if(str == COMMAND_PWD)
    {
      handleCommandPWD(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isLoggedIn);
    }
  else if(str == COMMAND_CWD)
    {
      handleCommandCWD(directory, controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isLoggedIn);
    }
  else if(str == COMMAND_CDUP)
    {
      handleCommandCDUP(controlSockDescriptor,dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isLoggedIn, rootDir);
    }
  else if(str == COMMAND_QUIT)
    {
      handleCommandQUIT(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
    }
  else if(str == COMMAND_PASV)
    {
      handleCommandPASV(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isLoggedIn);
    }
  else if(str == COMMAND_NLST)
    {
      handleCommandNLST(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isLoggedIn);
    }
  else if(str == COMMAND_RETR)
    {
      handleCommandRETR(arg, controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isLoggedIn);
    }
  else
  {
    handleCommandUnSupported(controlSockDescriptor);
  }
}

void parseCommandLine(char* commandLine, char* command, char* argument)
{
  string str = commandLine;
  string cmd = command;
  string arg = argument;
  int pos = str. find_first_of(' ');
  cmd = str.substr(0, pos);
  arg = str.substr(pos+1);
  strcpy(command, cmd.c_str());
  strcpy(argument, arg.c_str());

}

 void handleCommandUSER(char* username, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isUser)
 {
   if(strcmp(username, DEFAULT_USERNAME) == 0)
  {
    isUser = true;
    sendToRemote(controlSockDescriptor, USERNAME_OK_RESPONSE, strlen(USERNAME_OK_RESPONSE));
  }
  else
  {
    //sendToRemote(controlSockDescriptor, message.c_str(), message.length());
    sendToRemote(controlSockDescriptor, INVALID_USERNAME_RESPONSE, strlen(INVALID_USERNAME_RESPONSE));
    closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
  }
 }



 void handleCommandPASS(char* password, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isUser, bool& isLoggedIn)
 {
   if(!isUser)
   {
   	sendToRemote(controlSockDescriptor, INVALID_USERNAME_RESPONSE, strlen(INVALID_USERNAME_RESPONSE));
 	handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
   }
   else if(strcmp(password, DEFAULT_PASSWORD) != 0)
   {
   	sendToRemote(controlSockDescriptor, NOT_LOGGED_IN_RESPONSE, strlen(NOT_LOGGED_IN_RESPONSE));
 	handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
   }
   else
   {
   	isLoggedIn = true;
   	sendToRemote(controlSockDescriptor, LOGIN_RESPONSE, strlen(LOGIN_RESPONSE));
   }
 }

 void handleCommandPWD(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
 {
   if(!isLoggedIn)
 	{
 		sendToRemote(controlSockDescriptor, NOT_LOGGED_IN_RESPONSE, strlen(NOT_LOGGED_IN_RESPONSE));
 		handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
 	}
 	else
 	{
    char * dir;
    dir = (char*) malloc( COMMAND_BUFFER_SIZE * sizeof(char) );
    getcwd(dir,COMMAND_BUFFER_SIZE);
 		sendToRemote(controlSockDescriptor, dir, strlen(dir));
 	}
 }




 void handleCommandCWD(char* directory, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
 {
   string s = directory;
   if(!isLoggedIn)
	{
		sendToRemote(controlSockDescriptor, NOT_LOGGED_IN_RESPONSE, strlen(NOT_LOGGED_IN_RESPONSE));
		handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
	}
	else if(regex_match (s, regex("(./)(.*)")) || regex_match (s, regex("(../)(.*)")) || regex_match (s, regex("(.*)(/.)(.*)")) || regex_match (s, regex("(.*)(/..)(.*)")))
	{
		sendToRemote(controlSockDescriptor, CWD_FAIL_RESPONSE, strlen(CWD_FAIL_RESPONSE));
		handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
	}
	else
	{
		chdir(directory);
		sendToRemote(controlSockDescriptor, CHANGE_DIRECTORY_RESPONSE, strlen(CHANGE_DIRECTORY_RESPONSE));
	}
 }
 //If the client is logged in, determines whether the requested 'directory' is valid or not.
 //A requested directory is not valid if any of the following is true
 //	It is not a subdirectory of the current working directory
 //	It starts with "./" or "../"
 //	It contains "/.", "/..", or "*"

 void handleCommandCDUP(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn, const char* rootDir)
 {
   if(!isLoggedIn)
	{
		sendToRemote(controlSockDescriptor, NOT_LOGGED_IN_RESPONSE, strlen(NOT_LOGGED_IN_RESPONSE));
		handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
	}
	else
	{
    char * dir;
    dir = (char*) malloc( COMMAND_BUFFER_SIZE * sizeof(char) );
    getcwd(dir,COMMAND_BUFFER_SIZE);
		if(dir == rootDir)
		{
			sendToRemote(controlSockDescriptor, CDUP_FAIL_RESPONSE, strlen(CDUP_FAIL_RESPONSE));
			handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
		}
		else
		{
			chdir("..");
			sendToRemote(controlSockDescriptor, CHANGE_TO_PARENT_DIRECTORY_RESPONSE, strlen(CHANGE_TO_PARENT_DIRECTORY_RESPONSE));
		}
	}
 }


 void handleCommandPASV(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
 {
  if(!isLoggedIn)
	{
		sendToRemote(controlSockDescriptor, NOT_LOGGED_IN_RESPONSE, strlen(NOT_LOGGED_IN_RESPONSE));
		handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
	}
	enteringIntoPassive(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor);
 }


 void handleCommandNLST(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
 {
  if(!isLoggedIn)
	{
		sendToRemote(controlSockDescriptor, NOT_LOGGED_IN_RESPONSE, strlen(NOT_LOGGED_IN_RESPONSE));
		handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
	}
	if(!dataSockDescriptor)
	{
		sendToRemote(controlSockDescriptor, DATA_OPEN_CONNECTION_ERROR_RESPONSE, strlen(DATA_OPEN_CONNECTION_ERROR_RESPONSE));
	}
	else
	{
		listDirEntries(dataSockDescriptor);
	}
 }










 void handleCommandRETR(char* argument, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
 {

 }













 void handleCommandQUIT(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor,bool& isClientConnected)
 {
   sendToRemote(controlSockDescriptor, QUIT_RESPONSE, strlen(QUIT_RESPONSE));
   closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
 }

 void handleCommandUnSupported(const int controlSockDescriptor)
 {
   sendToRemote(controlSockDescriptor, UNSUPPORTED_COMMAND_RESPONSE, strlen(UNSUPPORTED_COMMAND_RESPONSE));
 }

 void handleNotLoggedIn(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected)
 {
   sendToRemote(controlSockDescriptor, NOT_LOGGED_IN_RESPONSE, strlen(NOT_LOGGED_IN_RESPONSE));
   closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
 }
