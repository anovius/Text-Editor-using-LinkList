#pragma once
#include "Node.h"
class TextEditor;
class LinkList
{
	friend TextEditor;
	Node* head;
	Node* tail;
public:
	LinkList();
	void insertData(string d, Node* n);
	void deleteNode(Node* n);
	Node* getNodeByNumber(int num);
};

