#ifndef COMPRESS_H
#define COMPRESS_H

#include "Headers.h"

//Encoding function need string that is to be encoded
vector<int> encoding(string s1);	

//Decoding function output string that will be printed 
//Need vector of int
string decoding(vector<int> op);

//Function to write the encoded values to .dat file
void writeFile(string f, vector<int> a);

//Function to read the encoded values to .dat file
vector<int> readFile(string f);

#endif // COMPRESS_H
