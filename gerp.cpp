/*
 * gerp.cpp
 * Authors: Toki Eashir (ttoki1) & Anh Hoang (ahoang05)
 * 4/20/2023
 * COMP 15 Project 4: Gerp
 *
 * Purpose: This file contains the function definitions from gerp.h.
            The only public function run() performs the query-loop
            functionality for the gerp program.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>

#include "gerp.h"


using namespace std;

// Constructor
Gerp::Gerp() {
    
}

/*
* run()
* Purpose: Performs the query loop functionality for the gerp program.
            Calls functions on the HashMap object to build the data structure
            and run the user commands.
* Parameters: Takes in a reference to FSTree and an output stream to 
*             print results to.
* Effects: Query-loop prompts for queries using a print statement and
           Prints a Goodbye message when the user quits the program.
*/
void Gerp::run(FSTree &tree, std::ofstream &outputFile) {
    // Search for file paths and create a vector of file paths
    table.traverseTree(tree.getRoot(), tree.getRoot()->getName());
    table.addData();
    //table.printTable();

    // Query-loop
    cout << "Query? ";
    string command;
    while (cin >> command and not cin.eof()) {
        if (command == "@q" or command == "@quit") {
            cout << "Goodbye! Thank you and have a nice day." << endl;
            return;
        }
        if (command == "@f") {
            cin >> command;
            ofstream outstream;
            openFile(outstream, command);
            outputFile.swap(outstream);
        }
        if (command == "@i" or command == "@insensitive") {
            // Get word
            cin >> command;
            string word = stripNonAlphaNum(command);
            table.search(word, outputFile, false);
        }
        else {
            string word = stripNonAlphaNum(command);
            table.search(word, outputFile, true);
        }
        cout << "Query? ";
    }
    if (cin.eof()) {
        cout << "Goodbye! Thank you and have a nice day." << endl;
    }
    outputFile.close();
}

/*
* name:      openFile()
* purpose:   open filestream
* arguments: streamtype &stream, string file_name
* effects:   Program closes with Exit failure if file fails to open.
*/
template<typename streamtype>
void Gerp::openFile(streamtype &stream, string file_name) {
        stream.open(file_name);
        if (not stream.is_open()) {
            cerr << "Error: could not open file " << file_name << endl;
            exit(EXIT_FAILURE);
        }
}


