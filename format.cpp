//Function to check if specefic char is in string or not 
bool findChar(char x, string y) {
	for (int i = 0; i < y.length(); i++) {
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
void formatting(vector<string> t) {
	int ind = 0;
	int openflag = 0;
	int closeflag = 0;
	for (int i = 0; i < t.size(); i++) {
		if (t[i][0] == '<' && (t[i][1] == '?' || t[i][1] == '!')) {
			cout << t[i] << endl;		//print output
		}
		else if (t[i][0] == '<' && !findChar('/', t[i])) {
			openflag++;
			closeflag = 0;
			if (openflag > 1) {
				ind++;
			}
			for (int j = 0; j < ind; j++) {
				cout << "\t";		//print tab
			}
			cout << t[i] << endl;	//print output
		}
		else if (t[i][0] == '<' && t[i][1] == '/') {
			closeflag++;
			openflag = 0;
			if (closeflag > 1) {
				ind--;
			}
			for (int j = 0; j < ind; j++) {
				cout << "\t";		//print tab
			}
			cout << t[i] << endl;	//print output
		}
		else if (t[i][0] == '<' && findChar('/', t[i])) {
			openflag++;
			closeflag = 0;
			if (openflag > 1) {
				ind++;
			}
			for (int j = 0; j < ind; j++) {
				cout << "\t";		//print tab
			}
			cout << t[i] << endl;	//print output
			closeflag++;
			openflag = 0;
			if (closeflag > 1) {
				ind--;
			}
		}
		else {
			for (int j = 0; j < ind; j++) {
				cout << "\t";		//print tab
			}
			cout << t[i] << endl;	//print output
		}
	}
}