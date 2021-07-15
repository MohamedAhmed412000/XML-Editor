#include "format.h"

//Function to check if specefic char is in string or not 
bool findChar(char x, string y) {
    for (unsigned int i = 0; i < y.length(); i++) {
		if (y[i] == x) {
			return 1;
		}
	}
	return 0;
}

//Formatting function need vector of string for example:
/*
t[0] = <first>
t[1] = <h1>hi</h1>
t[2] = </fisrt>
...
*/
string formatting(vector<string> t) {
	int ind = 0;
	int openflag = 0;
	int closeflag = 0;
    string str = "";
    for (unsigned int i = 0; i < t.size(); i++) {
		if (t[i][0] == '<' && (t[i][1] == '?' || t[i][1] == '!')) {
            str += t[i] + "\n";		//print output
		}
		else if (t[i][0] == '<' && !findChar('/', t[i])) {
			openflag++;
			closeflag = 0;
			if (openflag > 1) {
				ind++;
			}
			for (int j = 0; j < ind; j++) {
                str += "\t";		//print tab
			}
            str += t[i] + "\n";	//print output
		}
		else if (t[i][0] == '<' && t[i][1] == '/') {
			closeflag++;
			openflag = 0;
			if (closeflag > 1) {
				ind--;
			}
			for (int j = 0; j < ind; j++) {
                str += "\t";		//print tab
			}
            str += t[i] + "\n";	//print output
		}
		else if (t[i][0] == '<' && findChar('/', t[i])) {
			openflag++;
			closeflag = 0;
			if (openflag > 1) {
				ind++;
			}
			for (int j = 0; j < ind; j++) {
                str += "\t";		//print tab
			}
            str += t[i] + "\n";	//print output
			closeflag++;
			openflag = 0;
			if (closeflag > 1) {
				ind--;
			}
		}
		else {
			for (int j = 0; j < ind; j++) {
                str += "\t";		//print tab
			}
            str += t[i] + "\n";	//print output
		}
	}
    return str;
}
