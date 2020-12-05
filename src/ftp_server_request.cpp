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
  char cmd[COMMAND_BUFFER_SIZE];
  char arg[COMMAND_ARG_MAX_CHARACTER_COUNT];
  char *directory = strdup(rootDir);
  cout<<"\n\n\ncmd: "<<command<<endl;
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
    char dir[COMMAND_BUFFER_SIZE];
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

 void handleCommandCDUP(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn, const char* rootDir)
 {
   if(!isLoggedIn)
	{
		sendToRemote(controlSockDescriptor, NOT_LOGGED_IN_RESPONSE, strlen(NOT_LOGGED_IN_RESPONSE));
		handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
	}
	else
	{
    char dir[COMMAND_BUFFER_SIZE];
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
   //printf("\n\n\n inside PASV\n\n");

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
    int count;
		count = listDirEntries(dataSockDescriptor);
  //  printf("\n\ncount : %d\n",count);
    char response[FTP_RESPONSE_MAX_LENGTH];
    sprintf(response, NLST_CONNECTION_CLOSE_RESPONSE, count);
    //  cout<<response<<endl;
    sendToRemote(controlSockDescriptor, response, strlen(response));
    //free(response);
    close(dataSockDescriptor);
	}
 }










 void handleCommandRETR(char* argument, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
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
		int count;
		count = sendFile(argument, dataSockDescriptor);
    if(count > 0)
		{
			char response[FTP_RESPONSE_MAX_LENGTH];
      sprintf(response, RETR_CONNECTION_CLOSE_RESPONSE, count);
			sendToRemote(controlSockDescriptor, response, strlen(response));
		}
		else
		{
			sendToRemote(controlSockDescriptor, RETR_UNAVAILABLE_ERROR_RESPONSE, strlen(RETR_UNAVAILABLE_ERROR_RESPONSE));
		}
	}

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
