#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include "HashTable.h"
#include "LexicalAnalyzer.h"
#include "ParsingTree.h"


int main()
{
	vector<string>keywords = {"int", "float", "return"};
	vector<string>operations = { "+", "-", "*", "/", "%", "="};
	vector<string>servicies_commands = {";", "{", "}", "(", ")"};
	ifstream inFile("input.txt");
	ofstream outFile("output.txt");
	string text = "", str;
	
	if (!inFile.is_open()) {
		cout << "File not found";
		return 0;
	}

	while (!inFile.eof()) {
		getline(inFile, str);
		text += str + "\n";
	}

	LexicalAnalyzer lextanalyzator(keywords, operations, servicies_commands, text);

	HashTable res = lextanalyzator.analysis();
	int n = res.get_size();
	outFile << "Leksema" << setw(20) << " Type leksem " << setw(20) << " Id in HastTable " << setw(20) << "\n";
	for (int i = 0; i < n; i++)
	{

		pair<string, string> pr = res.get_pair(i);
		if (pr.first != "")
			outFile << pr.second << setw(25) << pr.first << setw(20) << i << "\n";
	}

	inFile.close();
	outFile.close();
	return 0;
}