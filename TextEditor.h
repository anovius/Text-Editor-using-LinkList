#pragma once
#include<string>
#include"LinkList.h"
#include"Node.h"
using namespace std;
class TextEditor
{
	string fileName;
	LinkList file;
	int totalLines;
	Node* currNode;
	int lineNum;
public:
	TextEditor(string fileName);
	static void Template();
	void showFile(int start, int end);
	void takeInput();
	int stringToInt(string s);
	void insertLine(string s);
	void deleteData(string s);
	void append();
	void listData(string s);
	bool isValidCommand(string s);
	void saveData();
};

