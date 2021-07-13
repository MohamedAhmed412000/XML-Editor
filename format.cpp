bool findChar(char x, string y) {
	for (int i = 0; i < y.length(); i++) {
		if (y[i] == x) {
			return 1;
		}
	}
	return 0;
}

void formatting(vector<string> t) {
	int ind = 0;
	int openflag = 0;
	int closeflag = 0;
	for (int i = 0; i < t.size(); i++) {
		if (t[i][0] == '<' && (t[i][1] == '?' || t[i][1] == '!')) {
			cout << t[i] << endl;
		}
		else if (t[i][0] == '<' && !findChar('/', t[i])) {
			openflag++;
			closeflag = 0;
			if (openflag > 1) {
				ind++;
			}
			for (int j = 0; j < ind; j++) {
				cout << "\t";
			}
			cout << t[i] << endl;
		}
		else if (t[i][0] == '<' && t[i][1] == '/') {
			closeflag++;
			openflag = 0;
			if (closeflag > 1) {
				ind--;
			}
			for (int j = 0; j < ind; j++) {
				cout << "\t";
			}
			cout << t[i] << endl;
		}
		else if (t[i][0] == '<' && findChar('/', t[i])) {
			openflag++;
			closeflag = 0;
			if (openflag > 1) {
				ind++;
			}
			for (int j = 0; j < ind; j++) {
				cout << "\t";
			}
			cout << t[i] << endl;
			closeflag++;
			openflag = 0;
			if (closeflag > 1) {
				ind--;
			}
		}
		else {
			for (int j = 0; j < ind; j++) {
				cout << "\t";
			}
			cout << t[i] << endl;
		}
	}
}