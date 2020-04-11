#include "Node.h"
#include<string>
using namespace std;
Node::Node(string d, Node* n, Node* p) {
	data = d;
	next = n;
	prev = p;
}