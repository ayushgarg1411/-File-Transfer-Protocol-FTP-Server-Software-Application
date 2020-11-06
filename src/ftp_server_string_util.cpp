/**
 * @file: ftp_server_string_util.cpp
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
#include "ftp_server_string_util.hpp"
 using namespace std;


 //Replaces all the occurrences of 'find' character in 'str' with 'replace' character.
 void replaceAll(char* str, char find, char replace)
 {
   string s = str;
   std::replace(s.begin(), s.end(), find, replace);

 }



 //Returns true if 'str' starts with 'prefix'.
 bool startsWith(const char* str, const char* prefix)
 {
 	int l = strlen(prefix);
 	for(int i=0; i<l; i++)
  {
 		if(str[i] != prefix[i])
    {
 			return false;
    }
  }
 	return true;
 }


 //Returns true if 'str' contains 'substr'
 bool contains(const char* str, const char* substr)
 {
 	const char *ptr = strstr(str, substr);
 	if(ptr != NULL)
  {
 		return true;
  }
 	return false;
 }
