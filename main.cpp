#include <stdio.h>
#include <conio.h>
#include "Node.h"
#include "Point.h"
#include "PriorityQueue.h"
#include <math.h>
#include <stdlib.h>
#include <deque>
#include <time.h>

//class Point

Point::Point()
{

}

Point::Point(int x, int y)
{
	X = x;
	Y = y;
}

Point::~Point()
{

}

double Point::Distance(Point* other)
{
	return sqrt(pow(this->X - other->X, 2) + pow(this->Y - other->Y, 2));
}


//class PriorityQueue

PriorityQueue::PriorityQueue()
{
	First = NULL;
	Last = NULL;
}

PriorityQueue::~PriorityQueue()
{
	First = NULL;
	Last = NULL;
}

void PriorityQueue::AddPriority(Node* NewItem)
{
	Node* Current = First;
	Node* Prev = NULL;
	bool Inserted = false;
	while (!Inserted)
	{
		if ((Current == NULL) || (Current->f <= NewItem->f))
		{
			NewItem->Next = Current;
			NewItem->Back = Prev;
			if (Prev) Prev->Next = NewItem;
			if (Current) Current->Back = NewItem;
			Inserted = true;
			if (NewItem->Next == First) First = NewItem;
			if (NewItem->Back == Last) Last = NewItem;
		}
		Prev = Current;
		if (Current) Current = Current->Next;
	}
}

void PriorityQueue::AddNormal(Node* NewItem)
{
	if (Last == NULL)
	{
		First = NewItem;
		Last = NewItem;
	}
	else
	{
		Last->Next = NewItem;
		Last = Last->Next;
	}
}

Node* PriorityQueue::GetTop()
{
	Node* Temp;
	Temp = Last;
	if (Last) Last = Last->Back;
	if (Last) Last->Next = NULL;
	if (Last == NULL) First = NULL;
	return Temp;
}

void PriorityQueue::MakeEmpty()
{
	First = NULL;
	Last = NULL;
}

bool PriorityQueue::IsEmpty()
{
	if (!First)
		return true;
	return false;
}

bool PriorityQueue::InList(Node* Item)
{
	Node* Tmp;
	Tmp = First;

	while (Tmp)
	{
		if (Tmp == Item)
			return true;
		Tmp = Tmp->Next;
	}

	return false;
}


//class Node

Node::Node()
{
	ConnNum = 0;

	name = 'O';
	point = new Point();

	f = 0;
	g = 0;
	h = 0;

	Next = NULL;
	Back = NULL;
	Parent = NULL;
}

Node::Node(char namechar, int x, int y)
{
	ConnNum = 0;

	name = namechar;
	point = new Point(x, y);

	f = 0;
	g = 0;
	h = 0;

	Next = NULL;
	Back = NULL;
	Parent = NULL;
}

Node::~Node()
{
	Next = NULL;
	Back = NULL;
	Parent = NULL;
}

void Node::SetNode(char namechar, int x, int y)
{
	name = namechar;
	point->X = x;
	point->Y = y;
}

void Node::ConnectTo(Node* node)
{
	if (!IsConnectedTo(node))
	{
		Connect[ConnNum] = node;
		ConnNum++;
	}
}

void Node::DisconnectTo(Node* node)
{
	for (int i = 0; i < ConnNum; i++)
	{
		if (Connect[i] == node)
		{
			Connect[i] = NULL;
			break;
		}
	}
}

void Node::BiConnectTo(Node* node)
{
	this->ConnectTo(node);
	node->ConnectTo(this);
	ElementList.push_back(node);	
	//ParentList.push_back(this);
	
}

//std::deque<Node*> AL;
int al = 0;
//Node* pnode = *AL.begin();

void FindBFS(Node*start, Node* target) {
	std::deque<Node*> NodeList;
	std::deque<Node*> NodeList1;
	std::deque<Node*> NodeList2;

	NodeList.push_back(start);

	
	while (NodeList.size() > 0) {
		Node* pNode = *NodeList.begin();
		
		NodeList1.push_back(pNode);
		al++;
	

		for (int i = 0; i < pNode->ElementList.size(); i++) {
			NodeList.push_back(pNode->ElementList.at(i));
		}
		NodeList.pop_front();
		
		if (pNode->name == target->name) {

			Node* extraNode = target;
			for (int i = al - 1; i >= 0; i--) {

				if (extraNode->IsConnectedTo(NodeList1.at(i)) == true) {

					NodeList2.push_back(extraNode);
					extraNode = NodeList1.at(i);
				}

			}
			NodeList2.push_back(start);
			for (int i = NodeList2.size() - 1; i >= 0; i--) {
				printf("%c ", NodeList2.at(i)->name);
			}
			break;
		}
	}

}

void FindDFS(Node* start, Node* target) {
	std::deque<Node*> NodeList;
	std::deque<Node*> NodeList1;
	std::deque<Node*> NodeList2;

	NodeList.push_back(start);


	while (NodeList.size() > 0) {
		Node* pNode = *NodeList.begin();

		NodeList1.push_back(pNode);
		al++;


		for (int i = 0; i < pNode->ElementList.size(); i++) {
			NodeList.push_back(pNode->ElementList.at(i));
		}
		NodeList.pop_front();

		if (pNode->name == target->name) {

			Node* extraNode = target;
			for (int i = al - 1; i >= 0; i--) {

				if (extraNode->IsConnectedTo(NodeList1.at(i)) == true) {

					NodeList2.push_back(extraNode);
					extraNode = NodeList1.at(i);
				}

			}
			NodeList2.push_back(start);
			for (int i = NodeList2.size() - 1; i >= 0; i--) {
				printf("%c ", NodeList2.at(i)->name);
			}
		}
	}

}

void Node::BiDisconnectTo(Node* node)
{
	this->DisconnectTo(node);
	node->DisconnectTo(this);
}

bool Node::IsConnectedTo(Node* node)
{
	for (int i = 0; i < ConnNum; i++)
	{
		if (Connect[i] == node)
		{
			return true;
		}
	}

	return false;
}

double Node::Distance(Node* other)
{
	return this->point->Distance(other->point);
}

Node* A = new Node('A', 10, 2);
Node* B = new Node('B', 2, 10);
Node* C = new Node('C', 4, 18);
Node* D = new Node('D', 12, 20);
Node* E = new Node('E', 16, 10);
Node* F = new Node('F', 19, 8);
Node* G = new Node('G', 16, 20);
Node* H = new Node('H', 22, 20);
Node* I = new Node('I', 22, 13);
Node* J = new Node('J', 22, 3);
Node* K = new Node('K', 28, 2);
Node* L = new Node('L', 34, 6);
Node* M = new Node('M', 36, 3);
Node* N = new Node('N', 46, 3);
Node* O = new Node('O', 46, 18);
Node* P = new Node('P', 36, 18);
Node* R = new Node('R', 48, 5);
Node* S = new Node('S', 52, 2);
Node* T = new Node('T', 56, 3);
Node* U = new Node('U', 27, 20);
Node* V = new Node('V', 48, 19);
Node* W = new Node('W', 53, 22);
Node* X = new Node('X', 53, 28);
Node* Y = new Node('Y', 48, 31);
Node* Z = new Node('Z', 43, 28);
Node* a = new Node('a', 43, 22);
Node* b = new Node('b', 38, 21);
Node* c = new Node('c', 32, 27);
Node* d = new Node('d', 29, 15);
Node* e = new Node('e', 28, 23);
Node* f = new Node('f', 28, 31);
Node* h = new Node('h', 6, 31);
Node* i = new Node('i', 6, 23);

Node* s = new Node('s', 3, 28);

Node* g = new Node('g', 58, 3);

void DoThi() {
	//ABCD
	A->BiConnectTo(B);
	A->BiConnectTo(E);

	B->BiConnectTo(C);

	C->BiConnectTo(D);

	D->BiConnectTo(E);

	//FGH
	G->BiConnectTo(F);
	G->BiConnectTo(H);

	F->BiConnectTo(H);

	//IJKL
	I->BiConnectTo(J);
	I->BiConnectTo(L);

	J->BiConnectTo(K);

	K->BiConnectTo(L);

	//MNOP
	M->BiConnectTo(P);
	C->BiConnectTo(N);

	N->BiConnectTo(O);

	O->BiConnectTo(P);

	//RSTU
	R->BiConnectTo(U);
	R->BiConnectTo(S);

	S->BiConnectTo(T);

	T->BiConnectTo(U);

	//VWXYZA1
	V->BiConnectTo(W);
	V->BiConnectTo(a);

	W->BiConnectTo(X);

	X->BiConnectTo(Y);

	Y->BiConnectTo(Z);

	Z->BiConnectTo(a);

	//B1C1D1
	b->BiConnectTo(c);
	b->BiConnectTo(d);

	c->BiConnectTo(d);

	//E1G1H1I1
	e->BiConnectTo(f);
	e->BiConnectTo(i);

	f->BiConnectTo(h);

	h->BiConnectTo(i);

}

void BFSTree() {

	s->BiConnectTo(B);
	s->BiConnectTo(C);
	s->BiConnectTo(i);
	s->BiConnectTo(h);

	B->BiConnectTo(A);
	C->BiConnectTo(D);
	i->BiConnectTo(G);
	i->BiConnectTo(H);
	i->BiConnectTo(e);
	h->BiConnectTo(f);

	A->BiConnectTo(K);
	A->BiConnectTo(J);
	A->BiConnectTo(F);
	A->BiConnectTo(E);
	H->BiConnectTo(I);
	H->BiConnectTo(L);
	H->BiConnectTo(d);
	e->BiConnectTo(c);
	f->BiConnectTo(O);
	f->BiConnectTo(a);
	f->BiConnectTo(Z);
	f->BiConnectTo(Y);

	K->BiConnectTo(S);
	K->BiConnectTo(N);
	K->BiConnectTo(M);
	L->BiConnectTo(P);
	d->BiConnectTo(b);
	c->BiConnectTo(V);
	O->BiConnectTo(R);
	O->BiConnectTo(U);
	Y->BiConnectTo(X);

	S->BiConnectTo(g);
	S->BiConnectTo(T);
	V->BiConnectTo(W);

	printf("BFS: ");


	Node* start = s;
	Node* target = g;
	
	FindBFS(start, target);
}

void DFSTree() {

	s->BiConnectTo(B);
	B->BiConnectTo(A);
	A->BiConnectTo(K);
	K->BiConnectTo(S);

	S->BiConnectTo(g);
	S->BiConnectTo(T);

	K->BiConnectTo(N);
	K->BiConnectTo(M);

	A->BiConnectTo(J);
	A->BiConnectTo(F);
	A->BiConnectTo(E);

	s->BiConnectTo(C);

	C->BiConnectTo(D);

	s->BiConnectTo(i);

	i->BiConnectTo(G);
	i->BiConnectTo(H);

	H->BiConnectTo(I);
	H->BiConnectTo(L);

	L->BiConnectTo(P);

	H->BiConnectTo(d);

	d->BiConnectTo(b);

	i->BiConnectTo(e);

	e->BiConnectTo(c);
	
	c->BiConnectTo(V);

	V->BiConnectTo(W);

	s->BiConnectTo(h);

	h->BiConnectTo(f);

	f->BiConnectTo(O);
	
	O->BiConnectTo(R);
	O->BiConnectTo(U);
	
	f->BiConnectTo(a);
	f->BiConnectTo(Z);

	f->BiConnectTo(Y);

	Y->BiConnectTo(X);


	printf("DFS: ");


	Node* start = s;
	Node* target = g;

	FindDFS(start, target);
}

int main() {
	clock_t begin = clock();
	//BFSTree();

	DFSTree();
	
	printf("\n");
	clock_t end = clock();
	printf("Time run: %f s", (float)(end - begin) / CLOCKS_PER_SEC);
	_getch();
	return 0;
}
