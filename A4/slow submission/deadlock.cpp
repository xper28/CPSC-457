//Solution for Q2 on assignment 4
//By Ahmad F Hassan || 30055847


#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;
int remProc(int lines, int deleteCount, bool succ);
int remRec(int lines, int deleteCount, bool succ);

     int ** graph;  //1 is <, 0 is >
     int currentLines = 0;

    int parseIn(int argc, char * const argv[]){
      //Initialize graph array
      int types = 3;
      int max = 1000000;

      graph = new int*[types];
      for (int i = 0; i < types; i++){
          graph[i] = new int[max];
        }

      string file;
      if (argc < 2){

      }else{
          file = argv[1];
      }

      //Read line-by-line
      string line;
      string p;
      string d;
      string r;
      int graphCt = 0;
      int lines = 0;
      int column = 0;
      while(getline(cin, line)){
        //if end of graph
        if(line.find("#") != string::npos){
          //process graph using kahn's algorithm
          remProc(lines, 0, true);
          lines = 0;
          column = 0;
        }else{
          //read line into strings
          stringstream ss(line);
          ss>>p>>d>>r;
          //move line array members into graph array
          if(line.find("<") != string::npos){
            graph[column][lines] = stoi(p);
            column++;
            graph[column][lines] = 1;
            column++;
            graph[column][lines] = stoi(r);
            column++;
          }else if(line.find(">") != string::npos){
            graph[column][lines] = stoi(p);
            column++;
            graph[column][lines] = 0;
            column++;
            graph[column][lines] = stoi(r);
            column++;
          }
          column = 0;
          lines++;
        }
      }
      //process the last graph using kahn's algorithm
      remProc(lines, 0, true);
      lines = 0;
      return 1;
    }


    int remProc(int lines, int deleteCount, bool succ){
      //attempt to remove a process with no outgoing edges
      //then attempt to remove a resource with no outgoing edges
      bool removed = false;
      for(int pCt = 0; pCt < lines; pCt++){
        bool deleteable = true;
        //if undeleted edge found
        if(graph[1][pCt] != -1){
          for(int pLock=0; pLock < lines; pLock++){
            if((graph[1][pLock] == 0) && (graph[0][pCt]==graph[0][pLock])){
              deleteable = false;
            }
          }
          if(deleteable){
            //remove edges involving process
            for(int remCt = 0; remCt < lines; remCt++){
              if(graph[0][pCt] == graph[0][remCt]){
                graph[1][remCt] = -1;
                deleteCount++;
              }
            }
          removed = true;
          break;
          }
        }
      }
      if(removed || succ){
        return remRec(lines, deleteCount, removed);
      }else{
        bool x = false;
        int deadCt;
        int * deads = new int[lines];
        for(int i=0; i<lines; i++){
          if(graph[1][i] != -1){
            x = true;
            deads[i] = graph[0][i];
            deadCt++;
          }
        }
        //Sort processes
        sort(deads, deads + lines);

        if(x == true){
          cout << "Deadlocked processes: " ;
          //Remove duplicates
          int current = 0;
          for(int k=0; k<lines; k++){
            if(deads[k]>current){
              current = deads[k];
              cout << current << " ";
            }
          }
          cout << endl;

        }else{
          cout << "Deadlocked processes: none" << endl;
        }
        return 0;

    }
  }

    int remRec(int lines, int deleteCount, bool succ){
      bool removed = false;
      for(int rCt = 0; rCt < lines; rCt++){
        bool deleteable = true;
        //if undeleted edge found
        if(graph[1][rCt] != -1){
          for(int rLock=0; rLock < lines; rLock++){
            if((graph[1][rLock] == 1)  && (graph[2][rCt]==graph[2][rLock])){
              deleteable = false;
            }
          }
          if(deleteable){
            //remove edges involving process
            for(int remCt = 0; remCt < lines; remCt++){
              if(graph[2][rCt] == graph[2][remCt]){
                graph[1][remCt] = -1;
                deleteCount++;
              }
          }
          removed = true;
          break;
          }
        }
      }
       if(removed || succ){
        return remProc(lines, deleteCount, removed);
      }else{
        bool x = false;
        int deadCt = 0;
        int * deads = new int[lines];
        //Store deadlocked processes
        for(int i=0; i<lines; i++){
          if(graph[1][i] != -1){
            x = true;
            deads[i] = graph[0][i];
            deadCt++;
          }
        }
        //Sort processes
        sort(deads, deads + lines);

        if(x == true){
          cout << "Deadlocked processes: " ;
          //Remove duplicates
          int current = 0;
          for(int k=0; k<lines; k++){
            if(deads[k]>current){
              current = deads[k];
              cout << current << " ";
            }
          }
          cout << endl;
        }else{
            cout << "Deadlocked processes: none" << endl;
          }
        return 0;
      }
    }


int main(int argc, char * const argv[]){
  parseIn(argc, argv);

}
