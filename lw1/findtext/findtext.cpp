#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool fsearchSubstr(ifstream& input, string substr)
{
	bool isFound = false;
	string inputstr;

	for (int i = 1; !input.eof(); i++)
	{
		getline(input, inputstr);
		if (inputstr.find(substr) != string::npos)
		{
			cout << i << endl;
			isFound = true;
		}
	}

	return isFound;
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "Input data is not enough\n";
		return 1;
	}
	else
	{
		string substr = argv[2];
		ifstream fin(argv[1]);
		if (!fin.is_open())
		{
			cout << "Failed to open file\n";
			return 1;
		}
		else
		{
			bool result = fsearchSubstr(fin, substr);
		}
	}
}