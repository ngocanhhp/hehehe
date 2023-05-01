/*
* hashmap.cpp
*
* Authors: Toki Eashir and Anh Hoang
* 4/20/2023
* COMP 15 Project 4
* gerp
* 
* Purpose: Holds the function definitions of hashmap.h
           This file defines functions and its helpers that deal with
           query commands from Gerp. 
*
*/

#include "hashmap.h"
#include <chrono>

using namespace std::chrono;
using namespace std;


// CONSTRUCTOR
// Purpose: Initiates an instance of HashMap object.
HashMap::HashMap() {

    for (size_t i = 0; i < capacity; i++) {
        vector<Value> val;
        hashTable.push_back(val);
    }

}

/*
* insert()
* Purpose:
* Effect:
*/
void HashMap::insert(string key, Location fileinfo) {
    checkLoad();
    bool found = false;
    size_t h_index = getHashIndex(toLowerCase(key));
    if (hashTable[h_index].empty()) {
        Value val = insertValue(key, fileinfo);
        hashTable[h_index].push_back(val);
    } else { // if hashTable's h_index has already stored one value
        int idx = value_exist(key);
        if (idx < 0) { // if value doesn't exist in hashTable's h_index
            Value val = insertValue(key, fileinfo);
            hashTable[h_index].push_back(val);
        } else { // if value exists at index idx in hashTable's h_index
            size_t var_size = hashTable[h_index][idx].variation.size();
            for (size_t i = 0; i < var_size; i++) {
                Entry &entry = hashTable[h_index][idx].variation[i];
                if (key == entry.word) {
                    for (size_t j = 0; j < entry.info.size(); j++) {
                        Location &location = entry.info[j];
                        if (entry_exist(fileinfo, location)) {
                            found = true; // set found to true here
                        }
                    }
                }
            }
            if (not found) { // if entry was not found, insert a new one
                Entry e = insertEntry(key, fileinfo);
                hashTable[h_index][idx].variation.push_back(e);
                found = true;
            }
        }
    }
}

/*
* insertValue()
* Purpose: adds an instance of Value (as it is not yet initialized when called) 
*          into the hashTable and add the first instance of Entry into Value's 
*          variation vector (which is why it calls insertEntry).   
* Parameters: key and location info of the value to 
* Effects: 
*/
Value HashMap::insertValue(string key, Location fileInfo) {
    Value val;
    val.word = stripNonAlphaNum(toLowerCase(key));
    Entry e = insertEntry(key, fileInfo);
    val.variation.push_back(e);
    return val;
}

/*
* insertEntry()
* Purpose: adds an instance of Entry into its corresponding Value's variation 
*          vector.     
* Parameters: 
* Effects:
*/
Entry HashMap::insertEntry(string key, Location fileInfo) {
    Entry e;
    e.word = key;
    e.info.push_back(fileInfo);
    size++;
    return e;
}

/*
* checkLoad()
* Purpose: Checks load factor and expands 
*          if load-factor limit has been hit.
*/
void HashMap::checkLoad() {
    if (is_loaded()) {
       // expand and rehash
       expand();
    }
}

/*
* Expand()
* Purpose: Rehashes values and copies them over to an expanded hashtable.  
* Effects: This function creates a temporary table of double capacity.
*/
void HashMap::expand() {
    capacity = (capacity * 2) + 2;
    vector<vector<Value>> new_table;

    for (size_t i = 0; i < capacity; i++) {
        vector<Value> val;
        new_table.push_back(val);
    }

    for (size_t i = 0; i < hashTable.size(); i++) {
        for (size_t j = 0; j < hashTable[i].size(); j++) {
            Value v = hashTable[i][j];
            int idx = getHashIndex(v.word);
            new_table[idx].push_back(v);
        }
    }

    hashTable = new_table;
}

/*
* getHashIndex()
* Purpose: Generates an index for a given word Value.
* Return: Returns the index of Value in the hashtable.
*/
size_t HashMap::getHashIndex(string word) {
    hash<string> str_hash;
    size_t hashIndex = str_hash(word) % capacity;
    return hashIndex;
}

/*
* value_exist()
* Purpose: Checks if a value exists in a vector at h_index in hashTable
* Return: Returns the index of Value in the hashtable.
*/
int HashMap::value_exist(string word) {
    size_t h_index = getHashIndex(toLowerCase(word));
    for (size_t i = 0; i < hashTable[h_index].size(); i++) {
        if (hashTable[h_index].at(i).word == toLowerCase(word)) {
            return i;
        }
    }
    return -1;
}

// Purpose: Checks if an already Exists in the Hashtable.
// Return: True if entry_exists, false otherwise.
bool HashMap::entry_exist(Location l1, Location l2) {
    return (l1.fileIndex == l2.fileIndex and l1.lineIndex == l2.lineIndex);
}

// Purpose: Checks if the load factor is significant enough or not.
// Return: True if load factor is greater than 0.75, false if less.
bool HashMap::is_loaded() {
    return (size/capacity > load_factor);
}

// Purpose: Converts every character in a string to lowercase.
// Returns: A lowercase string version of the passed in string.
string HashMap::toLowerCase(string word) {
    for (auto &lower : word) {
        lower = tolower(lower);
    }
    return word;
}

/*
* traverseTree()
* Purpose: Traverses the tree to search for file paths.      
* Parameters: Pointer to the root node & string to store file path.
* Effects: This is a recursive function.
*/
void HashMap::traverseTree(DirNode *curr, string currPath) {
    if (curr->hasFiles()) {
        for (int i = 0; i < curr->numFiles(); i++) {
            string filePath = currPath + "/" + curr->getFile(i);
            buildFileVector(filePath);
        }
    }
    if (curr->hasSubDir()) {
        for (int i = 0; i < curr->numSubDirs(); i++) {
            traverseTree(curr->getSubDir(i), currPath + "/" 
            + curr->getSubDir(i)->getName());
        }
    }
}

/*
* buildFileVector()
* Purpose: Opens a file and populates the vector of Files called dir.   
* Parameters: String representing the filepath.
* Effects: This function opens a file and reads from it, and stores lines
*          in dir.
*/
void HashMap::buildFileVector(string file_path) {
    Files f;
    f.file_path = file_path;

    string line;
    ifstream infile;
    openFile(infile, file_path);
    while (getline(infile, line)) {
        f.lines.push_back(line);
    }
    dir.push_back(f);
    infile.close();
}

/*
* addData()
* Purpose: Go through each file to update location.
* NoTE: This function calls a helper function called addDataHelper.
*/
void HashMap::addData() {
    for (size_t i = 0; i < dir.size(); i++) {
        Files f = dir[i];
        addDataHelper(f, i);
    }
}

/*
* addDataHelper()
* Purpose: Helper function for addData(). Populates the location struct
*          for each filepath.
* Parameters: A Files object and the index of the filepath in dir.
*/
void HashMap::addDataHelper(Files f, int dir_index) {
    for (size_t i = 0; i < f.lines.size(); i++) {
        string curr_line = f.lines[i];
        //skip empty lines
        if (curr_line.size() == 0) {
            continue;
        }
        string sentence = stripNonAlphaNum(curr_line);
        istringstream iss(sentence);
        string word;
        while (iss >> word) {
            // Populate Location struct
            Location loc;
            loc.fileIndex = dir_index;
            loc.lineIndex = i;
            insert(word, loc);
        }
    }
}


/*
* search()
* Purpose: Searches for a word based on sensitive or insensitive command. 
* Parameters: Word to search for, an output stream to print results to, 
*             and a boolean to flag if search is Sensitive.
* Effects: This function prints to an output file or calls functions
*          that may print to an output file.
*/
void HashMap::search(string word, ostream &output, bool isSensitive) {
    int idx = getHashIndex(toLowerCase(word));
    Value val;
    for (size_t i = 0; i < hashTable[idx].size(); i++) {
        if (hashTable[idx].at(i).word == toLowerCase(word)) {
            val = hashTable[idx].at(i);
        }
    }
    if (hashTable[idx].empty()) {
        output << word << " Not Found." << endl;
    }
    if (isSensitive) {
        querySensitive(val, word, output);
    } 
    else {
        queryInsensitive(val, toLowerCase(word), output);
    }
}

/*
* queryInsensitive()
* Purpose: Prints information to output file when user runs insensitive search.
*          Program outputs every string variable of the provided word.
* Parameters: Value struct of the given word, user provided word, and
*             an output stream to print data to.
* Effects: Prints data to an output file in the order:
*          [Filepath]:[lineNumber]:[Line]
*/
void HashMap::queryInsensitive(Value val, string word, ostream &output) {
    set<string> lowercasedWords;  // create a set to store lowercased words
    for (auto &vars : val.variation) {
        for (auto &infos : vars.info) {
            string lowerCLine = 
                   toLowerCase(dir[infos.fileIndex].lines[infos.lineIndex]);
            if (lowercasedWords.find(lowerCLine) == lowercasedWords.end()) {
                // if the lowercased line is not in the set, print it
                output << dir[infos.fileIndex].file_path << ":";
                output << infos.lineIndex + 1 << ": ";
                output << dir[infos.fileIndex].lines[infos.lineIndex] << endl;
                // insert the lowercased line into the set
                lowercasedWords.insert(lowerCLine);  
            }
        }
    }
    if (lowercasedWords.empty()) {
        output << word << " Not Found." << endl;
    }
}

/*
* query_Sensitive()
* Purpose: Prints information to output file when user inputs a word
*          or runs Sensitive search.
* Parameters: Value struct of the given word, user provided word, and an
*             output stream to print data to.
* Effects: Prints data to an output file in the order:
*          [Filepath]:[lineNumber]:[Line]
*/
void HashMap::querySensitive(Value val, string word, ostream &output) {
    for (auto &entry : val.variation) {
        if (entry.word == word) {
            for (auto &info : entry.info) {
                output << dir[info.fileIndex].file_path << ":";
                output << info.lineIndex + 1 << ": ";
                output << dir[info.fileIndex].lines[info.lineIndex] << endl;
            }
        }
    }
    if (val.variation.empty()) {
        output << word << " Not Found. Try with @insensitive or @i." << endl;
    }
}

// void HashMap::printTable() {
//     // Print out all occurrences of the hashTable
//     for (size_t o = 0; o < hashTable.size(); o++) {
//         for (size_t j = 0; j < hashTable.at(o).size(); j++) {
//             for (size_t k = 0; k < hashTable.at(o).at(j).variation.size();
//                  k++) {
//                 for (size_t m = 0; m < 
//                     hashTable[o].at(j).variation[k].info.size(); m++) {
//                     cout << dir[hashTable.at(o).at(j).variation[k].info[m]. \
//                     fileIndex].file_path << ": ";
//                     cout << hashTable.at(o).at(j).variation.at(k).info. \
//                     at(m).lineIndex + 1 << ": ";
//                     cout << dir[hashTable[o].at(j).variation[k].info[m]. \
//                     fileIndex].lines[hashTable[o].at(j).variation[k]. \
//                     info[m].fileIndex] << ": ";
//                     cout << hashTable[o].at(j).variation.at(k).word;
//                     cout << ": ";  
//                     cout << hashTable[o].at(j).word << " (Value)" ;
//                     cout << endl;          
//                 }                   
//             }
//         }
//     }
// }

/*
* name:      openFile()
* purpose:   open filestream
* arguments: streamtype &stream, string file_name
* effects:   Program closes with Exit failure if file fails to open.
*/
template<typename streamtype>
void HashMap::openFile(streamtype &stream, string file_name) {
        stream.open(file_name);
        if (not stream.is_open()) {
            cerr << "Error: could not open file " << file_name << endl;
            exit(EXIT_FAILURE);
        }
}