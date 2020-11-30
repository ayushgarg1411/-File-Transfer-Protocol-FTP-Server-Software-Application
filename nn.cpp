#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;
#define FILENAME_MAX 512

int main()
{
  char * cwd;
  cwd = (char*) malloc( FILENAME_MAX * sizeof(char) );
  getcwd(cwd,FILENAME_MAX);
  cout<< cwd;
}
