#include <iostream>
#include <cstdio>
#define MAX_LEN 100

using namespace std;

int main(){
  FILE *fp;
  char buffer [MAX_LEN];

  fp = popen("./myFind", "r");

  while(fgets(buffer, MAX_LEN, fp)){
    printf("%s", buffer);
  }
  pclose(fp);
  return 0;
}
