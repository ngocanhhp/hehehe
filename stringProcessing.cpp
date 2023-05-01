/*
* stringProcessing.cpp
* Authors: Toki Eashir(ttoki1) & Anh Hoang(ahoang05)
* 4/16/2023
* COMP 15 Project 4: Gerp
*
* This file contains the function definitions for the stripNonAlphaNum function,
* which removes all leading and trailing non-alphanumeric characters from the 
* given string.
*  
*/

#include "stringProcessing.h"

using namespace std;


/*
* stripNonAlphaNum()
* Purpose: This function removes all leading and trailing
*          non-alphanumeric characters from the given string.
* Parameters: String to manipulate.
* Return Value: String with leading and trailing alpha-numericals removed.
*/
string stripNonAlphaNum(string input) {
    while (not isalnum(input[0])) {
        input.erase(0, 1);
        continue;
    }
    while (not isalnum(input.back())) {
        input.pop_back();
    }
    return input;
}
