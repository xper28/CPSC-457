/**********************************************
 * Last Name:   <Hassan>
 * First Name:  <Ahmad>
 * Student ID:  <30055847>
 * Course:      CPSC 457
 * Tutorial:    <1>
 * Assignment:  2
 * Question:    Q2
 *
 * File name: myFind.cpp
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string>

using namespace std;

void getFiles(const char *path){
  //Get current working directory
  DIR *dir;
  struct dirent *f;

  dir = opendir(path);

  if (dir != NULL) {
    while ( f = readdir(dir)) {
        if (!f->d_name || f->d_name[0] == '.')
            continue;
          printf("./%s\n", f->d_name);
    }
  }
    closedir(dir);
}


int main(){
  char directory[] = "./";
  getFiles(directory);
}
