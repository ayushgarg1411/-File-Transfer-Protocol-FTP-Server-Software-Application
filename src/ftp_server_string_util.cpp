/**
 * @file: ftp_server_string_util.cpp
 * @author: Ayush, 656665809, F20N02, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: NOV 05, 2020
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
 	int l = strlen(str);
 	for(int i=0; i<l; i++)
 		if(str[i] == find)
 			str[i] = replace;
 }



 //Returns true if 'str' starts with 'prefix'.
 bool startsWith(const char* str, const char* prefix)
 {
 	int l = strlen(prefix);
 	for(int i=0; i<l; i++)
 		if(str[i] != prefix[i])
 			return false;
 	return true;
 }


 //Returns true if 'str' contains 'substr'
 bool contains(const char* str, const char* substr)
 {
 	const char *ptr = strstr(str, substr);
 	if(ptr != NULL)
 		return true;
 	return false;
 }



 //Changes all characters of 'str' to upper case.
 /*void toUpper(char* str)
 {
 	transform(str.begin(), str.end(), str.begin(), ::toupper);
 }



 //Changes all characters of 'str' to lower case.
 void toLower(char* str)
 {
 	transform(str.begin(), str.end(), str.begin(), ::tolower);
 }
 */

 //Removes all the spaces, if there is any, from the beginning and the ending of 'str'.
 void stripLeadingAndTrailingSpaces(char* str)
 {
 	int count = 0;
     for (int i = 0; str[i]; i++)
 		if (str[i] != ' ')
 			str[count++] = str[i];
     str[count] = '\0';
 }


 //Removes new line character ('\n'), if there is any, from the end of 'str'.
 void stripNewlineAtEnd(char* str)
 {
 	int count = 0;
     for (int i = 0; str[i]; i++)
 		if (str[i] != '\n')
 			str[count++] = str[i];
     str[count] = '\0';
 }
