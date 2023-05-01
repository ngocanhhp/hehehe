/*
 * gerp.h
 * Authors: Toki Eashir (ttoki1) & Anh Hoang (ahoang05)
 * 4/20/2023
 * COMP 15 Project 4: Gerp
 *
 * Purpose: This file holds the function declarations for the Gerp class.
            The Gerp class has only one public function called run which
            deals with the query loop.
            The private HashMap object is an instance of of the HashMap class
            and is used to build the data-structure.
 */


#ifndef __GERP_
#define __GERP_
#include <string>
#include <iostream>
#include <vector>
#include "DirNode.h"
#include "hashmap.h"
#include "FSTree.h"
#include "stringProcessing.h"

class Gerp {
public:
    Gerp();

    void run(FSTree &tree, std::ofstream &outputFile);

private:
    HashMap table;
    
    // Open or Die
    template<typename streamtype>
    void openFile(streamtype &stream, std::string file_name);
};

#endif 
