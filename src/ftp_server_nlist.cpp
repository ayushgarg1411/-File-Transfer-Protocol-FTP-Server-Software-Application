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
 #include "ftp_server_connection.hpp"
 using namespace std;

 int listDirEntries(int dataSockDescriptor)
 {
  // printf("\n\n\n inside st\n\n");
//

   int count = 0;
   char de[2048];
   memset(de, 0, 2048);
   DIR *d;
	struct dirent *dir;
	d = opendir(DEFAULT_DIRECTORY_PATH);
  if(d == NULL)
  {
    return 0;
  }
	while((dir = readdir(d)) != NULL)
	{

		if(dir->d_type == DT_DIR)
		{
      count++;
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
//  printf("\n\n\n ioutsideide nlst\n\n");


  //sendToRemote(dataSockDescriptor, strdup(de), sizeof(char)*strlen(strdup(de)));
  return count;
 }
