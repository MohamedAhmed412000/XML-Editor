// substring.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include"substring.h"

int checking_errors(vector<string>&strr, vector<string>&modified, vector<int>&error)
{
    int Error_count = 0;
	int current = 0;
	bool check = false;
	stack<string> s;
	string nn = "";
    for (unsigned int i = 0; i < strr.size(); i++)
	{
		if (current == i - 2)
			check = false;
		if (strr[i][0] != '<')
		{
			modified.push_back(strr[i]);
		}
        if ((strr[i][0] == '<'&&strr[i][1] == '!')|| (strr[i][0] == '<'&&strr[i][1] == '?'))
        {
            modified.push_back(strr[i]);
        }
        if (strr[i][0] == '<'&&strr[i][1] != '/'&&strr[i][1]!='!')
		{
			if (i != 0 && strr[i - 1][0] != '<')
			{
                error.push_back(i-1);
                Error_count++;
				nn = s.top();
				nn.insert(1, "/");
				modified.push_back(nn);
				s.pop();
			}
			s.push(strr[i]);
			modified.push_back(strr[i]);
		}
		if (strr[i][0] == '<'&&strr[i][1] == '/')
		{
			string er = s.top();
			//strr[i].erase(1, 1);
			if (Compare_Tags(er, strr[i]))
			{
				s.pop();
				modified.push_back(strr[i]);
			}
			else
			{
				current = i;
				string er = s.top();
				string app = er.insert(1, "/");
				modified.push_back(app);
				s.pop();
				if (!check)
				{
					error.push_back(i);
                    Error_count++;
				}
				check = true;
			}
		}
	}
    for (unsigned int i = 0; i < strr.size(); i++)
	{
		if (s.empty())
			break;
		string m = s.top();
		m.insert(1, "/");
		modified.push_back(m);
		s.pop();
	}
    return Error_count;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
