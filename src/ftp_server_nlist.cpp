/**
 * @file: ftp_server_nlist.cpp
 * @author: Name, Student Number, Section, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: June 24, 2020
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
 #include <dirent.h>
 #include "ftp_server_nlist.hpp"
 using namespace std;

 int listDirEntries(int dataSockDescriptor)
 {

   int count = 0;
   char *de = new char[2000];
   DIR *d;
	struct dirent *dir;
	d = opendir(DEFAULT_DIRECTORY_PATH);
	while((dir = readdir(d)) != NULL)
	{
    count++;
		if(dir->d_type == DT_DIR)
		{
      strcat(de, "D\t");
      strcat(de, dir->d_name);
      strcat(de, "\n");
		}
		else
		{
      strcat(de, "F\t");
      strcat(de, dir->d_name);
      char* x = new char[200];
      sprintf(x, "%ld", dir->d_ino);
      strcat(de, "\t\t");
      strcat(de, x);
      strcat(de, "\n");
		}
	}
  return count;
 }
