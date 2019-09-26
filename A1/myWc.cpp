/**********************************************
 * Last Name:   <Hassan>
 * First Name:  <Ahmad>
 * Student ID:  <30055847>
 * Course:      CPSC 457
 * Tutorial:    <1>
 * Assignment:  1
 * Question:    Q4
 *
 * File name: countLines.cpp
 *********************************************/

#include <unistd.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main (int argc, char * const argv[])
{
  // get the file name from command line
  string filename;
  if (argc != 2) {
    cerr << "Usage: readFile <input file> " << endl;
    return -1;
  }
  else {
    filename = argv[1];
  }

  // open the file for reading
  int fd = open( filename.c_str(), O_RDONLY);
  if( fd < 0) {
    cerr << "Could not open file " << filename << "\n";
    exit(-1);
  }

  // read 1000 characters into a buffer and process
  int count = 0;
  int cond = 1;
  int buffSize = 1000;
  while(cond ==1){
    char c[buffSize];
    if(read( fd, & c, buffSize)<buffSize){
      cond = 0;
    }
    for(int i=0; i<buffSize; i++){
    if(c[i]=='\n')
    count++;
  }
}
cout<<count<<endl;

  // close file and report results
  close( fd);
  cout << count << " " << filename << "\n";
  return 0;
}
