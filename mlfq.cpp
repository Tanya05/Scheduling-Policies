#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include "mlfq.h"

using namespace std;
	
int leatime[4]={2,6,14,INT_MAX};

void function(LinkQueue*x, int timing)
{
	int i=0;
	while(i<4)
	{
		if(!EmptyQueue(x[i]))
		{
			Job *t=&x[i].front->data;
			t->runtime++;
			if(t->runtime==1&&timing>=t->arrivetime)
				t->rettime=timing-t->arrivetime;
			if(t->runtime==t->requiretime)
			{
				t->leavetime=timing+1;
				t->roundtime=t->leavetime-t->arrivetime;
				cout<<"num:"<<t->num<<" "<<"rettime:"<<t->rettime<<" "<<"leavetime:"<<t->leavetime<<" "<<"roundtime:"<<t->roundtime<<endl;
				OutQueue(x[i]);
			}
			else if(t->runtime==leatime[i] && i<3)
			{
				EnQueue(x[i+1],OutQueue(x[i]));
			}
			break;
		}
		i++;
	}
}

int main()
{
	LinkQueue* x = (LinkQueue*)malloc(sizeof(LinkQueue)*4);
	for(int i = 0; i < 4; i++)
	{
		x[i].front=x[i].rear=NULL;
	}
	int timing = 0;
	cout<<"please input the number of the jobs:\n";
	int n;
	cin >> n;
	Job *jobing = new Job[n];
	cout<<"please input the num, arrivetime, requiretime of each job:\n";
	for(int i=0;i<n;i++)
	{
		cin>>jobing[i].num>>jobing[i].arrivetime>>jobing[i].requiretime;
	}
	int i=0;
	while(i != n || !(EmptyQueue(x[0])&&EmptyQueue(x[1])&&EmptyQueue(x[2])&&EmptyQueue(x[3])))
	{
		while(timing == jobing[i].arrivetime)
		{
			jobing[i].runtime=0;
			EnQueue(x[0],jobing[i]);
			i++;
		}
		function(x,timing);
		timing++;
	}
	for(i=0;i<4;i++)
	{
		ClearQueue(x[i]);
	}

	system ("pause");
	return 0;
}
