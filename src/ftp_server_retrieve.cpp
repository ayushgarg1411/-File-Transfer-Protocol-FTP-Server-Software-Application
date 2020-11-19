/**
 * @file: ftp_server_retrieve.cpp
 * @author: Name, Student Number, Section, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: June 24, 2020
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
 #include <algorithm>
 #include "ftp_server_net_util.hpp"
 #include "ftp_server_connection_listener.hpp"
 #include "ftp_server_session.hpp"
 #include "ftp_server_nlist.hpp"
 #include "ftp_server_request.hpp"
 #include "ftp_server_retrieve.hpp"

int sendFile(char* filename, int& dataSockDescriptor)
{
  return 0;
}
