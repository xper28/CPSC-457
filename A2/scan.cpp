/**********************************************
 * Last Name:   <Hassan>
 * First Name:  <Ahmad>
 * Student ID:  <30055847>
 * Course:      CPSC 457
 * Tutorial:    <1>
 * Assignment:  2
 * Question:    Q3
 *
 * File name: scan.cpp
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <utility>

#define MAX_FNAME_SIZE 512
#define MAX_FILES 1024

using namespace std;

int main( int argc, char ** argv) {
  // handle command line arguments
  if( argc != 3) {
    fprintf(stderr, "Incorrect number of arguments. Please enter <fileType> <fileNumber>\n");
    exit(-1);
  }
  string suffix = argv[1];
  int nResult = atoi(argv[2]);
  // open 'find...'
  FILE * fp = popen("./myFind", "r");
  if( fp == NULL) {
    perror("popen failed:");
    exit(-1);
  }
  // read in all filenames and filter by extension
  char buff[MAX_FNAME_SIZE];
  int nFiles = 0;
  char * files[MAX_FILES];
  while(fgets(buff,MAX_FNAME_SIZE,fp)) {
    int len = strlen(buff) - 1;
    string temp = strndup(buff,len);
    if(temp.find(suffix) != std::string::npos){
    files[nFiles] = strndup(buff,len);
    nFiles ++;
  }
  }
  fclose(fp);
  printf("Found %d files:\n", nFiles);
  //Compare given number of files to actual
  if(nResult>nFiles){
    nResult = nFiles;
  }

  // get file sizes for each file and sum them up
  long long totalSize = 0;
  struct stat st;

  //store all file sizes
  int sizes[nFiles];
  int unsorted[nFiles];
  for(int i = 0 ; i < nFiles ; i ++ ) {
    if(stat(files[i],&st) !=0) {
      perror("stat failed:");
      exit(-1);
    }
    sizes[i]=st.st_size;
    unsorted[i]=st.st_size;
  }
  //Sort one copy of the sizes
  std::sort(sizes, sizes+nFiles, std::greater<int>());

  //Compare sorted and unsorted to find the corresponding filenames
    for(int j=0; j<nResult;j++){
      int index = 0;
      for(int k=0; k<nFiles;k++){
        if(sizes[j]==unsorted[k]){
          index = k;
        }
      }
        printf("%ld %s \n", sizes[j], files[index]);
    }

  //Calculate and print total size
  for(int i=0; i<nResult;i++){
    totalSize+=sizes[i];
  }

  printf("Total size: %lld bytes.\n", totalSize);
  // clean up
  for(int i = 0; i < nFiles ; i ++ ) {
    free(files[i]);
  }
  // return success
  return 0;
}
