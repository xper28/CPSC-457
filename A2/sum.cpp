/**********************************************
 * Last Name:   <Hassan>
 * First Name:  <Ahmad>
 * Student ID:  <30055847>
 * Course:      CPSC 457
 * Tutorial:    <1>
 * Assignment:  2
 * Question:    Q5
 *
 * File name: sum.cpp
 *********************************************/

#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

unsigned long sum;
int max = 1000000;
int numbers[max];

void *adder(int flag){


  for(int i=1; i<=num; i++){
    sum += i;
  }
  cout << "Thread ID = " << pthread_self() << ": " << sum << endl;
  pthread_exit(0);
}

int main(int argc, char ** argv) {
  // handle command line arguments
  if( argc != 3) {
    fprintf(stderr, "Incorrect number of arguments. Please enter <fileName> <threadCount>\n");
    exit(-1);
  }
  std::string fileName = argv[1];
  int nThreads = atoi(argv[2]);

  //Read numbers from file
  ifstream File;
  File.open(fileName);

  int n = 0;
  while (File >> numbers[n]) {
    n++;
  }
  File.close();

  for(int i = 0; i<nThreads; i++){
  pthread_t tid;
  pthread_create(&tid,NULL,adder,(void *) (nThreads/2));
  }
  //Groups split


  // Wait for the thread to exit
  pthread_join(tid,NULL);

  cout << "Sum (" << 1 << ", " << nThreads << ") = " << sum+sum2 << endl;
  return 0;
  }
