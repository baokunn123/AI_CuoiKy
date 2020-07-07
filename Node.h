#if !defined(NODE_H)
#define NODE_H

#define MAXCONN 100

#include "Point.h"
#include <deque>

class Node
{
	int i;
public:
	
	std::deque<Node*> ElementList;
	std::deque<Node*> ParentList;
	std::deque<Node*> Path;

	char AList[100];
	char BList[100];

	char name;
	int ConnNum;
	double f;
	double g;
	double h;
	Point* point;
	Node* Connect[MAXCONN];
	Node* Next, * Back;
	Node* Parent;
	void FindBFS(Node * target);

	
	Node();
	Node(char namechar, int x, int y);
	virtual ~Node();
	void SetNode(char namechar, int x, int y);
	void ConnectTo(Node* node);
	void DisconnectTo(Node* node);
	void BiConnectTo(Node* node);
	void BiDisconnectTo(Node* node);
	bool IsConnectedTo(Node* node);
	double Distance(Node* other);
};

#endif

