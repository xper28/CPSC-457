// CPSC457 University of Calgary
// Skeleton C++ program for Q7 of Assignment 5.
//
// The program reads in the input, then calls checkConsistency()
// function, and finally formats the output.
//
// Author: Pavol Federl (pfederl@ucalgary.ca or federl@gmail.com)
// Date: April 1, 2019
// Version: 5
// Student: Ahmad F Hassan || 30055847

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdint.h>
#include <unordered_set>
#include <map>

typedef std::string SS;
typedef std::vector<SS> VS;
using namespace std;

struct DEntry {
    SS fname = SS( 4096, 0);
    int size = 0;
    int ind = 0;
    bool tooManyBlocks = false;
    bool tooFewBlocks = false;
    bool hasCycle = false;
    bool sharesBlocks = false;
};

static SS join( const VS & toks, const SS & sep) {
    SS res;
    bool first = true;
    for( auto & t : toks) { res += (first ? "" : sep) + t; first = false;}
    return res;
}

// re-implement this function
//
// Parameters:
//   blockSize - contains block size as read in from input
//   files - array containing the entries as read in from input
//   fat - array representing the FAT as read in from input
// Return value:
//   the function should return the number of free blocks
//   also, for ever entry in the files[] array, you need to set the appropriate flags:
//      i.e. tooManyBlocks, tooFewBlocks, hasCycle and sharesBlocks
int checkConsistency( int blockSize, std::vector<DEntry> & files, std::vector<int> & fat)
{
    int need = 0;
    unordered_set<int> notFree;
    //unordered_set<int> shared;
    multimap<int, int> shared;
    int flag=0;
    for(int i=0; i<files.size(); i++){
      //check how many blocks required
      unordered_set<int> visited;
      bool cycle = false;
      if(files[i].size%blockSize == 0){
        need =files[i].size/blockSize;
      }else{
        need = files[i].size/blockSize +1 ;
      }
      //check how many blocks file actually has and detect cycles
      int pointer = files[i].ind;
      //cout << files[i].fname << " initially points to " << pointer<<endl;
      int blockCt = 0;
      while(pointer != -1){
        //check if node was not previously visited
        if(visited.find(pointer) == visited.end()){
          visited.insert(pointer);
          notFree.insert(pointer);
          shared.insert(pair <int, int> (pointer,i));
          blockCt++;
        }else{
          cycle = true;
          break;
        }
        pointer = fat[pointer];
      }

      //Check need against owned
      if(blockCt > need){
        files[i].tooManyBlocks = true;
      }else if(blockCt < need){
        files[i].tooFewBlocks = true;
      }

      //check if a cycle occured
      if(cycle){
        files[i].hasCycle = true;
      }
    }
    //Check sharesBlocks
    for(auto it=shared.begin(); it != shared.end(); it++){
      int twice = 0;
      twice = shared.count(it->first);
      if(twice>1){
        auto itp = shared.equal_range(it->first);
        for(auto itr=itp.first; itr != itp.second; itr++){
          files[itr->second].sharesBlocks = true;
        }
      }
    }


    int freeCt = 0;
    //count free blocks
    for(int k=0; k<fat.size(); k++){
      if(notFree.find(k) == notFree.end()){
        freeCt++;
      }
    }
    return freeCt;
}

int main()
{
    try {
        // read in blockSize, nFiles, fatSize
        int blockSize, nFiles, fatSize;
        if( 3 != scanf( "%d %d %d", & blockSize, & nFiles, & fatSize))
            throw "cannot read blockSize, nFiles and fatSize";
        if( blockSize < 1 || blockSize > 1024) throw "bad block size";
        if( nFiles < 0 || nFiles > 50) throw "bad number of files";
        if( fatSize < 1 || fatSize > 200000) throw "bad FAT size";
        // read in the entries
        std::vector<DEntry> entries;
        for( int i = 0 ; i < nFiles ; i ++ ) {
            DEntry e;
            if( 3 != scanf( "%s %d %d", (char *) e.fname.c_str(), & e.ind, & e.size))
                throw "bad file entry";
            e.fname = e.fname.c_str();
            if( e.fname.size() < 1 || e.fname.size() > 16)
                throw "bad filename in file entry";
            if( e.ind < -1 || e.ind >= fatSize) throw "bad first block in fille entry";
            if( e.size < 0 || e.size > 1073741824) throw "bad file size in file entry";
            entries.push_back( e);
        }
        // read in the FAT
        std::vector<int> fat( fatSize);
        for( int i = 0 ; i < fatSize ; i ++ ) {
            if( 1 != scanf( "%d", & fat[i])) throw "could not read FAT entry";
            if( fat[i] < -1 || fat[i] >= fatSize) throw "bad FAT entry";
        }

        // run the consistency check
        int nFreeBlocks = checkConsistency( blockSize, entries, fat);

        // format the output
        size_t maxflen = 0;
        for( auto & e : entries ) maxflen = std::max( maxflen, e.fname.size());
        SS fmt = "  %" + std::to_string( maxflen) + "s: %s\n";

        printf( "Issues with files:\n");
        for( auto & e : entries ) {
            VS issues;
            if( e.tooFewBlocks) issues.push_back( "not enough blocks");
            if( e.tooManyBlocks) issues.push_back( "too many blocks");
            if( e.hasCycle) issues.push_back( "contains cycle");
            if( e.sharesBlocks) issues.push_back( "shares blocks");
            printf( fmt.c_str(), e.fname.c_str(), join( issues, ", ").c_str());
        }
        printf( "Number of free blocks: %d\n", nFreeBlocks);
    }
    catch( const char * err) {
        fprintf( stderr, "Error: %s\n", err);
    }
    catch( ... ) {
        fprintf( stderr, "Errro: unknown.\n");
    }
    return 0;
}
