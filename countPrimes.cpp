//Solution for q5 in assignment 3
//Ahmad F Hassan || 30055847
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>
#include <mutex>

unsigned long count=0;
int64_t getNext();

/// primality test, if n is prime, return 1, else return 0
int isPrime(int64_t n)
{
     if( n <= 1) return 0; // small numbers are not primes
     if( n <= 3) return 1; // 2 and 3 are prime
     if( n % 2 == 0 || n % 3 == 0) return 0; // multiples of 2 and 3 are not primes
     int64_t i = 5;
     int64_t max = sqrt(n);
     while( i <= max) {
         if (n % i == 0 || n % (i+2) == 0) return 0;
         i += 6;
     }
     return 1;
}

//Thread body
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* counter(void *arg){
      int64_t num;
      while(1){
      //Query for a number
      pthread_mutex_lock(&mutex);
      num = getNext();
      //If no more numbers available exit
      if(num == -1){
        pthread_mutex_unlock(&mutex);
        break;
      }
      pthread_mutex_unlock(&mutex);
      //Check if prime (parallelized)
      if( isPrime(num)){
        //Increment global count variable
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
      }
}
    //Kill thread
    pthread_exit(0);
}

//Method to get a number
int64_t getNext(){
  int64_t num;
  if( 1 != scanf("%ld", & num)) {
    return -1;
  }else{
    return num;
  }
}

int main( int argc, char ** argv)
{
    /// parse command line arguments
    int nThreads = 1;
    if( argc != 1 && argc != 2) {
        printf("Uasge: countPrimes [nThreads]\n");
        exit(-1);
    }
    if( argc == 2) nThreads = atoi( argv[1]);

    /// handle invalid arguments
    if( nThreads < 1 || nThreads > 256) {
        printf("Bad arguments. 1 <= nThreads <= 256!\n");
    }
    else{
      pthread_t threads[nThreads];
      long status, i;
      //Create threads
      for(i = 0; i<nThreads; i++){
        status = pthread_create(&threads[i], NULL, counter, NULL);
        if(status != 0){
          printf("Oops, pthread_create returned error code %d\n", status);
          exit(-1);
        }
      }
    ///Notify start
    printf("Counting primes using %d thread%s.\n",
           nThreads, nThreads == 1 ? "s" : "");
    //Wait for threads to finish
    for(i = 0; i<nThreads; i++){
      pthread_join(threads[i], NULL);
    }
  }
  /// report results
  printf("Found %ld primes.\n", count);
  return 0;

}
