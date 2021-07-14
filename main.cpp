#include "substring.h"

int main()
{
	
	int errors = 0;
	string str = "<users>                                           "
		"    <user>                                                 "
		"        <id>1                                              "
		"        <name>user1</name>                                 "
		"        <posts>                                            "
		"            <post>                                         "
		"			    Lorem and me have gone to paris.            "
		"			</post>                                         "
		"			<post>                                          "
		"			     me,and my 2friends have gone to home       "
		"			</post>                                         "
		"		 </posts>                                           "
		"		 <followers>                                        "
		"                <follower>                                 "
		"			    <name> 2 </id>                              "
		"			</follower>                                     "
		"			<follower>                                      "
		"			    <id> 4 </id>                                "
		"			</follower>                                     "
		"	  </user>                                               "
		"</users>                                                   ";
	vector<string> strr;
	int total = 0;
	int counter = 0;
	int k = 0;
	vector<string>modified;
	total=vector_parse(str,strr);
	errors = checking_errors(strr,modified,counter);
/*	for (int i = 0; i < total; i++)
	{
		cout << strr[i] << endl;
	}*/
	cout << "modified vector" << endl;
	
	for (int i = 0; i < counter; i++)
	{
		cout << modified[i] << endl;
	}
	cout << errors << endl;

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
