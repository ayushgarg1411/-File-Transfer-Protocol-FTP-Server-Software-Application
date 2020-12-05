/**
 * @file: ftp_server_nlist.cpp
 * @author: Ayush, 656665809, F20N02, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: Dec 04, 2020
 *
 */
 #include <iostream>
 #include <iomanip>
 #include <string>
 #include <list>
 #include <cstring>
 #include <cstdlib>
 #include <fstream>
 #include <sys/types.h>
 #include <unistd.h>
 #include <signal.h>
 #include <sys/stat.h>
 #include <dirent.h>
 #include "ftp_server_nlist.hpp"
 #include "ftp_server_connection.hpp"
 using namespace std;

 int listDirEntries(int dataSockDescriptor)
 {
  int count = 0;
   int size =0;
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
      ifstream fsize(dir->d_name, ios::binary);
      fsize.seekg(0, ios::end);
      size = fsize.tellg();
      fsize.close();
      char* x = new char[200];
      sprintf(x, "%d", size);
      strcat(de, "\t\t");
      strcat(de, x);
      strcat(de, "\n");
		}
	}
  sendToRemote(dataSockDescriptor, strdup(de), sizeof(char)*strlen(strdup(de)));
  return count;
 }
