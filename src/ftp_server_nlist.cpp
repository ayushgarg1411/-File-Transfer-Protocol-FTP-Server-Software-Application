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
 #include "ftp_server_nlist.hpp"
 using namespace std;

 int listDirEntries(int dataSockDescriptor)
 {
   return 0;
 }
 //Determines and sends the list of current directory entries to the client using
 //the data connection, represented by 'dataSockDescriptor'.
 //Returns the count of entries to the caller.
