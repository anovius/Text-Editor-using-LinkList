#include<iostream>
#include "TextEditor.h"
using namespace std;
int main() {
	cout << "Edit (filename): ";
	string s;
	getline(cin,s);
	string fileName = "";
	for (int i = 5; i < s.length(); i++)
		fileName = fileName + s[i];
	TextEditor* file = new TextEditor(fileName);
	return 0;
}