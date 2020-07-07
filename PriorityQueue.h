#if !defined(PRIORITYQUEUE_H)
#define PRIORITYQUEUE_H

#include "Node.h"

class PriorityQueue
{
private:
	Node* First;
	Node* Last;

public:
	PriorityQueue();
	~PriorityQueue();
	void AddPriority(Node* NewItem);
	void AddNormal(Node* NewItem);
	void MakeEmpty();
	bool IsEmpty();
	bool InList(Node* Item);
	Node* GetTop();
};

#endif
