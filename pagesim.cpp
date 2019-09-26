//Answer to Q6 on Assignment 5
//Ahmad F Hassan || 30055847

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <climits>
#include<bits/stdc++.h>
#include <map>
#include <utility>
#include <unordered_map>
#include <algorithm>

using namespace std;
int LRU(int pages[], int n, int capacity);
int CLOCK(int pages[], int n, int capacity);
int optimal(int pages[], int n, int capacity);

int MAX = 5000;
int main( int argc, char ** argv){
        if (argc !=2 ) {
          cout << "Usage: ./pagesim <page size>";
          exit(1);
        }

        int capacity = stoi(argv[1]);

        string current;
        string line;
        int num;
        int * pages = new int[MAX];
        int ct = 0;

        while(getline(cin, line)){
          stringstream ss(line);
          while(ss >> current){
            num = stoi(current);
            pages[ct] = num;
            ct++;
          }
        }
        optimal(pages, ct, capacity);
        LRU(pages, ct, capacity);
        CLOCK(pages, ct, capacity);
}

int optimal(int pages[], int n, int capacity){
  //Current pages
  vector<int> v;
  //Iterate over pages
  int faults = 0;
  for(int i=0; i<n; i++){
    //If frame is not full
    if(v.size() < capacity){
      //check if frame already contains page
      if(find(v.begin(), v.end(), pages[i]) != v.end()) {
        //do nothing
      } else {
        v.push_back(pages[i]);  //Add to frame
        faults++;
      }
    }
    //else the frame is full, need to remove a pages
    else{
      if(find(v.begin(), v.end(), pages[i]) != v.end()) {
      } else {
        //perform future look to determine victim page
        int victim = 0;
        int keepCount = 0;
        int top_index = 0;
        int max_index = 0;

        for(int j=0; j<v.size(); j++){
          bool exists = false;
          for(int k=i+1; k<n; k++){
            if(v[j] == pages[k]){
              exists = true;
              //If I can keep
              if(keepCount < capacity-1){
                //victim = j+1;
                if(k > max_index){
                  max_index = k;
                  top_index = j;
                }
                keepCount++;
                break;
              }
              //if I can't keep
              else{
                //cout << "can't keep anymore, found with index:  "<< k << " but max index is " << max_index << endl;
                if(k<max_index){
                  victim = top_index;
                  //cout << "Swapping " << v[j] << " with " << pages[max_index] << endl;
                  break;
                }else{
                  top_index = j;
                  victim = top_index;
                }
              }
            }
          }
          if(!exists){
            top_index = j;
            break;
          }
        }
        //Victim has been found
        v[top_index] = pages[i];
        faults++;
    }
  }
}
  //Print results
  cout << "Optimal: " << endl;
  cout << " - frames: ";
  for(int k=0; k<v.size(); k++){
  cout << v[k] << " ";
  }
  cout << endl;
  cout << " - page faults: " << faults << endl;
  return faults;
}

int CLOCK(int pages[], int n, int capacity){
  //Current pages
  vector<int> v;
  //pages and their reference bits
  unordered_map<int, int> reference;
  //Iterate over pages
  int faults = 0;
  int pointer = 0;
  for(int i=0; i<n; i++){
    if(v.size() < capacity){
      //check if frame already contains page
      if(find(v.begin(), v.end(), pages[i]) != v.end()) {
        reference[pages[i]] = 1;
      } else {
        v.push_back(pages[i]);  //Add to frame
        reference[pages[i]] = 1;  //Set reference bit to 1
        if(pointer+1 == capacity){
          pointer=0;
        }else{
            pointer++;
        }
        faults++;
      }
    }
    //else the frame is full, need to remove a pages
    else{
      if(find(v.begin(), v.end(), pages[i]) != v.end()) {
        reference[pages[i]] = 1;
      } else {
        bool deleted = false;
        while(!deleted){
          //if page has reference bit=0
          if(reference[v[pointer]] == 0){
            v[pointer] = pages[i];
            reference[v[pointer]] = 1;
            faults++;
            deleted = true;
            if(pointer+1 == capacity){
              pointer = 0;
            }else{
              pointer++;
            }
            break;
            //else page has reference bit=1
          }else{
            reference[v[pointer]] = 0;  //Set it to 0
            if(pointer+1 == capacity){
              pointer = 0;
            }else{
              pointer++;
            }
          }
        }
      }

    }
  }
  cout << "Clock: " << endl;
  cout << " - frames: ";
  for(int j=0; j<v.size(); j++){
  cout << v[j] << " ";
}
  cout << endl;
  cout << " - page faults: " << faults << endl;
  return faults;
}

int LRU(int pages[], int n, int capacity){
  //Current pages
  vector<int> v;
  //Iterate over pages
  int faults = 0;
  for(int i=0; i<n; i++){
    //If frame is not full
    if(v.size() < capacity){
      //check if frame already contains page
      if(find(v.begin(), v.end(), pages[i]) != v.end()) {
        //do nothing
      } else {
        v.push_back(pages[i]);  //Add to frame
        faults++;
      }
    }
    //else the frame is full, need to remove a pages
    else{
      if(find(v.begin(), v.end(), pages[i]) != v.end()) {
      } else {
        //perform past look to determine victim page
        int victim = 0;
        int keepCount = 0;
        int top_index = 0;
        int min_index = n;

        for(int j=0; j<v.size(); j++){
          bool exists = false;
          for(int k=i-1; k>=0; k--){
            if(v[j] == pages[k]){
              exists = true;
              //If I can keep
              if(keepCount < capacity-1){
                if(k < min_index){
                  min_index = k;
                  top_index = j;
                  break;
                }
                keepCount++;
                break;
              }
              //if I can't keep
              else{
                if(k<min_index){
                  victim = top_index;
                  break;
                }else{
                  top_index = j;
                  victim = top_index;
                }
              }
            }
          }
        }
        //Victim has been found
        v[top_index] = pages[i];
        faults++;
    }
  }
}
  //Print results
  cout << "LRU: " << endl;
  cout << " - frames: ";
  for(int k=0; k<v.size(); k++){
  cout << v[k] << " ";
  }
  cout << endl;
  cout << " - page faults: " << faults << endl;
  return faults;
}
