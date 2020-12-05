/**
 * @file: ftp_server_retrieve.cpp
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
 #include "ftp_server_retrieve.hpp"
 #include "ftp_server_response.hpp"
 #include "ftp_server_connection.hpp"

 using namespace std;

int sendFile(char* filename, int& dataSockDescriptor)
{
  int size=0;
  FILE *fp;
	fp = fopen(filename, FILE_OPEN_MODE);
	if(fp)
	{
		char chunk[DATA_SOCKET_SEND_BUFFER_SIZE];
		while(!feof(fp))
		{
			fscanf(fp,"%s", chunk);
			sendToRemote(dataSockDescriptor, chunk, strlen(chunk));
		}
    fclose(fp);
    ifstream fsize(filename, ios::binary);
    fsize.seekg(0, ios::end);
    size = fsize.tellg();
    fsize.close();
	}

  return size;

}
