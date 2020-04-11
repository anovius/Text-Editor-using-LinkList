#include "LinkList.h"
#include <iostream>
#include <string>
using namespace std;
LinkList::LinkList() {
	head = new Node();
	tail = new Node();
	head->next = tail;
	tail->prev = head;
}
void LinkList::insertData(string s, Node* n) {
	Node* newNode = new Node(s, n, n->prev);
	n->prev->next = newNode;
	n->prev = newNode;
}
void LinkList::deleteNode(Node* n) {
	n->prev->next = n->next;
	n->next->prev = n->prev;
	delete n;
}
Node* LinkList::getNodeByNumber(int num) {
	int i;
	Node* temp = head->next;
	for (i = 1; temp->next != tail && i < num; i++)
		temp = temp->next;
	if (i == num && temp != tail)
		return temp;
	else
		return NULL;
}