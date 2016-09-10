#include <iostream>
using namespace std;

struct Job
{
	int num;//??
	int arrivetime;//????
	int requiretime;//??????
	int rettime;//????
	int leavetime;//????
	int roundtime;//????
	int runtime;//????
};
struct Node{
	Job data;
	Node* next;
};
struct LinkQueue{
	Node* front;
	Node* rear;
};
void EnQueue(LinkQueue& q, Job item)
{
	Node* n = new Node;
	n->data=item;
	n->next=NULL;
	if(q.rear==NULL)
		q.front=q.rear=n;
	else
		q.rear=q.rear->next=n;
}
Job OutQueue(LinkQueue& q)
{
	Job temp = q.front->data;
	Node* p =q.front;
	q.front=p->next;
	if(q.front==NULL)
		q.rear=NULL;
	delete p;
	return temp;
}
bool EmptyQueue(LinkQueue& q)
{
	return q.front==NULL;
}
void ClearQueue(LinkQueue& q)
{
	Node* p = q.front;
	while(p!=NULL)
	{
		q.front=q.front->next;
		delete p;
		p=q.front;
	}
	q.rear = NULL;
}
