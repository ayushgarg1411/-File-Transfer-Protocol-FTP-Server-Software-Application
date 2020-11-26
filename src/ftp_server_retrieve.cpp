/**
 * @file: ftp_server_retrieve.cpp
 * @author: Name, Student Number, Section, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: June 24, 2020
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
 #include "ftp_server_retrieve.hpp"
 #include "ftp_server_response.hpp"
 #include "ftp_server_connection.hpp"
 #include <signal.h>
 #include <iomanip>
 #include <cstring>
 #include <cstdlib>

 using namespace std;
int sendFile(char* filename, int& dataSockDescriptor)
{
  //return 0;
}
