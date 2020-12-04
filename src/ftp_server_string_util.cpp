/**
 * @file: ftp_server_string_util.cpp
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
 #include <algorithm>
 #include <stdlib.h>
 #include <cstdlib>
 #include <sys/types.h>
 #include <unistd.h>
 #include <signal.h>
 #include "ftp_server_string_util.hpp"





  void replaceAll(char* str, char find, char replace)
  {
    std::string s = str;
    std::replace(s.begin(), s.end(), find, replace);
    strcpy(str, s.c_str());

  }
using namespace std;



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


  bool contains(const char* str, const char* substr)
  {
  	const char *ptr = strstr(str, substr);
  	if(ptr != NULL)
   {
  		return true;
   }
  	return false;
  }



  void toUpper(char* str)
  {
    int i = 0;
    char ch;
    while(str[i])
    {
      ch = str[i];
      str[i] = toupper(ch);
      i++;
    }
  }


  void toLower(char* str)
  {
    int i = 0;
    char ch;
    while(str[i])
    {
      ch = str[i];
      str[i] = tolower(ch);
      i++;
    }
  }




  void stripLeadingAndTrailingSpaces(char* str)
  {
    int i,j;
    for(i = 0; str[i] == ' '; i++);
    if(i)
     {
       for(j = 0; (str[j] = str[i+j]); j++);
     }
   for(i = strlen(str)-1; str[i] == ' '; i--);
   str[i+1] = '\0';

  }



  void stripNewlineAtEnd(char* str)
  {
    string su = str;
    su.erase(remove(su.begin(), su.end(), '\n'), su.end());
    strcpy(str, su.c_str());
  }
