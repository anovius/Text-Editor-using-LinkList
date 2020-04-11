#pragma once
#include<string>
using namespace std;
class LinkList;
class TextEditor;
class Node
{
	friend LinkList;
	friend TextEditor;
	string data;
	Node* next;
	Node* prev;
public:
	Node(string d = "", Node* n = 0, Node* p = 0);
};

