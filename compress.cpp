#include<iostream>
#include<string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<int> encoding(string s1)
{
	unordered_map<string, int> table;
	for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		table[ch] = i;
	}

	string p = "", c = "";
	p += s1[0];
	int code = 256;
	vector<int> output_code;
	for (int i = 0; i < s1.length(); i++) {
		if (i != s1.length() - 1)
			c += s1[i + 1];
		if (table.find(p + c) != table.end()) {
			p = p + c;
		}
		else {
			output_code.push_back(table[p]);
			table[p + c] = code;
			code++;
			p = c;
		}
		c = "";
	}
	output_code.push_back(table[p]);
	return output_code;
}
string decoding(vector<int> op)
{
	string out = "";
	unordered_map<int, string> table;
	for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		table[i] = ch;
	}
	int old = op[0], n;
	string s = table[old];
	string c = "";
	c += s[0];
	cout << s;
	int count = 256;
	for (int i = 0; i < op.size() - 1; i++) {
		n = op[i + 1];
		if (table.find(n) == table.end()) {
			s = table[old];
			s = s + c;
		}
		else {
			s = table[n];
		}
		out += s;
		c = "";
		c += s[0];
		table[count] = table[old] + c;
		count++;
		old = n;
	}
	return out;
}
void writeFile(string f,vector<int> a) {
	ofstream file(f, ios::binary | ios::out);
	for (int i = 0; i < a.size(); i++) {
		int num = a[i];
		file.write((char *)&num, sizeof(int));
	}
	file.close();
}

vector<int> readFile(string f) {
	ifstream file(f, ios::binary | ios::in);
	vector<int>b;
	while (!file.eof()) {
		int num;
		file.read((char *)&num, sizeof(int));
		b.push_back(num);
	}
	file.close();
	return b;
}
int main()
{
	vector<string> t;
	string text;
	string x = "";
	ifstream fileRead("hi.xml");
	while (getline(fileRead, text)) {
		size_t i = text.find('<');
		text.erase(0, i);
		t.push_back(text);
		x += t.back();
	}
	fileRead.close();
	vector<int> a = encoding(x);
	writeFile("hi.dat", a);
	vector<int>b;
	b = readFile("hi.dat");
	b.pop_back();
	string s = decoding(b);
	cout << s;
	return 0;
}