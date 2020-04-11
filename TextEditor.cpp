#include "TextEditor.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
TextEditor::TextEditor(string fileName) {
	this->fileName = fileName;
	totalLines = 0;
	ifstream input(fileName + ".txt", ios::app);
	string line;
	while (!input.eof()) {
		getline(input, line);
		if (line != "") {
			file.insertData(line, file.tail);
			totalLines++;
		}
	}
	input.close();
	if (totalLines == 0) {
		Template();
		currNode = file.tail;
	}
	else
		showFile(1, totalLines);
	lineNum = totalLines + 1;
	currNode = file.tail;
	takeInput();
}
void TextEditor::Template() {
	cout << "\t\tI line No || A for append || D start end || L start end || E to Exit\n";
}
void TextEditor::showFile(int start, int end) {
	Node* temp = file.getNodeByNumber(start);
	while (temp != file.tail && start <= end) {
		cout << start << ">  " << temp->data << endl;
		temp = temp->next;
		start++;
	}
}
void TextEditor::takeInput() {
	string s = "";
	char ch;
	while (s != "E") {
		cout << lineNum << "> ";
		getline(cin, s);
		ch = s[0];
		switch (ch)
		{
		case 'I':
			if (isValidCommand(s))
				insertLine(s);
			break;
		case 'D':
			if (isValidCommand(s))
				deleteData(s);
			break;
		case 'L':
			if (isValidCommand(s))
				listData(s);
			break;
		case 'A':
			if (isValidCommand(s))
				append();
			break;
		case 'E':
			if (isValidCommand(s))
				saveData();
			break;
		default:
			file.insertData(s, currNode);
			totalLines++;
			lineNum++;
			break;
		}
	}
}
int TextEditor::stringToInt(string s) {
	int num = s[0]-48;
	for (int i = 1; i < s.length(); i++) {
		num *= 10;
		num = num + s[i] - 48;
	}
	return num;
}
void TextEditor::insertLine(string s) {
	string num="";
	for (int i = 2; i < s.length(); i++)
		num = num + s[i];
	string input;
	cout << num << "> ";
	getline(cin, input);
	if (stringToInt(num) > totalLines) {
		lineNum = totalLines + 2;
		file.insertData(input, file.tail);
		currNode = file.tail;
		totalLines++;
		return;
	}
	if (num != "") {
		lineNum = stringToInt(num);
		currNode = file.getNodeByNumber(stringToInt(num));
		if (input.length() == 1 && input[0] == 'A') {
			append();
			currNode = currNode->next;
			return;
		}
	}
	lineNum++;
	file.insertData(input, currNode);
	totalLines++;
}
void TextEditor::listData(string s) {
	if (totalLines == 0) {
		cout << "\nFile is Empty\n";
		return;
	}
	if (s.length() == 1) {
		showFile(1, totalLines);
		return;
	}
	string s1 = "";
	string s2 = "";
	int i = 2;
	for (; s[i] != ' ' && i < s.length(); i++)
		s1 = s1 + s[i];
	for (i = i + 1; i < s.length(); i++)
		s2 = s2 + s[i];
	if (s2 == "")
		showFile(stringToInt(s1), totalLines);
	else 
		showFile(stringToInt(s1), stringToInt(s2));
}
void TextEditor::deleteData(string s) {
	Node* temp = currNode->prev;
	if (s.length() == 1) {
		file.deleteNode(currNode);
		currNode = temp;
		lineNum--;
		return;
	}
	string s1 = "";
	string s2 = "";
	int i = 2;
	for (; s[i] != ' ' && i < s.length(); i++)
		s1 = s1 + s[i];
	for (i = i + 1; i < s.length(); i++)
		s2 = s2 + s[i];
	if (s2 == "") {
		if (stringToInt(s1) > totalLines || stringToInt(s1) == 0) {
			cout << "Inavlid!\n";
			return;
		}
		currNode = file.getNodeByNumber(stringToInt(s1))->prev;
		file.deleteNode(file.getNodeByNumber(stringToInt(s1)));
		totalLines--;
		lineNum--;
	}
	else {
		int n1 = stringToInt(s1);
		int n2 = stringToInt(s2);
		if (n1 > n2 || n1 > totalLines || n2 > totalLines) {
			cout << "Inavlid!\n";
			return;
		}
		for (; n1<=n2; n2--) {
			currNode = file.getNodeByNumber(n1)->prev;
			file.deleteNode(file.getNodeByNumber(n1));
			totalLines--;
			lineNum--;
		}
	}
	if (totalLines == 0) currNode = file.tail;
}
void TextEditor::append() {
	string s;
	cout << lineNum << "> ";
	getline(cin, s);
	Node* tempNode = currNode;
	if (currNode == file.tail) {
		tempNode = file.tail->prev;
		lineNum--;
	}
	tempNode->data += ' ' + s;
	lineNum++;
}
void TextEditor::saveData() {
	ofstream output(fileName + ".txt");
	Node* temp = file.head->next;
	while (temp != file.tail) {
		output << temp->data << '\n';
		temp = temp->next;
	}
}
bool TextEditor::isValidCommand(string s) {
	if (s.length() > 1 && (s[2] < '0' || s[2] > '9')) {
		file.insertData(s, currNode);
		totalLines++;
		lineNum++;
		return false;
	}
	return true;
}