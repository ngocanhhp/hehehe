/*
* hashmap.h
*
* 4/20/2023
* COMP 15 Project 4
* gerp
*
* Purpose:
*
*/

#ifndef __HASHMAP__
#define __HASHMAP__

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <list>
#include <functional>
#include <set>

#include "DirNode.h"
#include "FSTree.h"
#include "stringProcessing.h"


struct Entry;

struct Files {
    std::string file_path;
    std::vector<std::string> lines;
};

struct Location {
    //the index of the line in the vector
    int lineIndex;
    // used to lookup File vector quickly in gerp.h
    int fileIndex;
    bool operator == (const Location & another) const {
        return (lineIndex == another.lineIndex 
        and fileIndex == another.fileIndex);
    }
};

//Base Entry
struct Value {
    std::string word; 
    std::vector<Entry> variation;
};

struct Entry {
    std::string word;
    std::vector<Location> info;
};

class HashMap {
public:
    // Global Constants
    const float LOAD_FACTOR_LIMIT = 0.75f;
    const size_t INIT_CAPACITY = 27059;

    // Constructor
    HashMap();

    // Operation functions
    void insert(std::string key, Location fileinfo);
    void traverseTree(DirNode *curr, std::string hehe);
    void addData();
    void search(std::string word, std::ostream &output, bool isSensitive);
    
    // MOVE TO PRIVATE LATER
    size_t getHashIndex(std::string word);
    bool is_loaded();
    void printTable();  
    // void PushEntry(Entry entry);
    Value insertValue(std::string key, Location fileInfo);

    


    void buildFileVector(std::string file_path);

private:
    std::vector<std::vector<Value>> hashTable;
    std::vector<Files> dir;

    void addDataHelper(Files f, int dir_index);
    //Value insertValue(std::string key, Location fileInfo);
    Entry insertEntry(std::string key, Location fileInfo);
    int value_exist(std::string word);
    bool entry_exist(Location l1, Location l2);
    void checkLoad();
    void expand();
    void querySensitive(Value val, std::string word, std::ostream &output);
    void queryInsensitive(Value val, std::string word, std::ostream &output);

    // Open or Die
    template<typename streamtype>
    void openFile(streamtype &stream, std::string file_name);
    
    std::string toLowerCase(std::string word);

    const float load_factor = LOAD_FACTOR_LIMIT;
    size_t capacity = INIT_CAPACITY;
    size_t size = 0;
};


#endif