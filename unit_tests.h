/*
 *  unit_tests.h
 *  Authors: Toki Eashir(ttoki1) & Anh Hoang(ahoang05)
 *  4/16/2023
 *  COMP 15 Project 4: Gerp
 *
 *  Purpose: unit testing for stringProcessing
 *
 */

#include "stringProcessing.h"
#include "gerp.h"
#include "hashmap.h"
#include <string>
#include <cassert>

using namespace std;

// tests the stripNonAlphaNum function.
void stringmanipulation_test1() {
    string test = "&**&& - the-fuck%%^&";
    //cout << stripNonAlphaNum(test) << endl;
    assert(stripNonAlphaNum(test) == "the-fuck");
}

// tests the stripNonAlphaNum function.
void stringmanipulation_test2() {
    string test = "()!4/14/23()";
    assert(stripNonAlphaNum(test) == "4/14/23");
}

// Tests the getHashIndex function in hashmap.h to check if the same word
// provides the same hash value.
void test_hashkey() {
    string word1 = "test";
    string word2 = "test";
    HashMap hash;

    assert(hash.getHashIndex(word1) == hash.getHashIndex(word2));
}

/* ---------- PRIVATE FUNCTION TESTS -------------


// Purpose: Tests the entry_exist function in HashMap class.
// NOTE: This is a private member function, so this test has to be 
//       commented out.
void Entry_exist_test() {
    Location l1;
    Location l2;
    Location l3;
    HashMap hash;

    // l1
    l1.fileIndex = 3;
    l1.lineIndex = 6;

    // l2
    l2.fileIndex = 3;
    l2.lineIndex = 6;

    // l3
    l3.fileIndex = 8;
    l3.lineIndex = 8;

    assert(hash.entry_exist(l1, l2) == true);
    assert(hash.entry_exist(l1, l3) == false);    
}

// Purpose: Tests the Value_exist function in HashMap class.
// Note: This is a private member function, so this test has to be 
//       commented out.
void Value_Exist_test() {
    HashMap table;
    Location l1;
    l1.fileIndex = 3;
    l1.lineIndex = 6;


    table.insert("word", l1);
    assert(table.value_exist("word") == 0);
    assert(table.value_exist("notword") == -1);
    
}

*/

// Purpose: Tests the insertValue() function.
void insertValue_test() {

}

// Purpose: Builds a hashmap from the tinyData directory that is copied
//          on our halligan accoutn.
void buildfile() {
    HashMap table;
    table.buildFileVector("tinyData/");
}
