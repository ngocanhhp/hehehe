/*
* main.cpp
*
* Authors: Toki Eashir and Anh Hoang
* 4/14/2023
* COMP 15 Project 4
* gerp
*
*
* Purpose: main function for gerp
*
*/

#include <string>
#include <iostream>
#include <fstream>

#include "FSTree.h"
#include "gerp.h"

using namespace std;

// Function Declaration
template<typename streamtype>
void openFile(streamtype &stream, string file_name);

// Purpose: This function takes in command line inputs
//          and declares and instance of the gerp Class to run the 
//          gerp program.
// Effect: May print an error if incorrect command-line inputs are
//         provided.
int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        return (EXIT_FAILURE);
    }
    FSTree directory = FSTree(argv[1]);
    string outputFile = argv[2];

    ofstream outstream;
    openFile(outstream, outputFile);

    Gerp gerp;
    gerp.run(directory, outstream);

    return 0;
}

/*
* name:      openFile()
* purpose:   open filestream
* arguments: streamtype &stream, string file_name
* effects:   Program closes with Exit failure if file fails to open.
*/
template<typename streamtype>
void openFile(streamtype &stream, string file_name) {
        stream.open(file_name);
        if (not stream.is_open()) {
            cerr << "Error: could not open file " << file_name << endl;
            exit(EXIT_FAILURE);
        }
}
