#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class Process
	{
	public:
	string pid;
	int at, st, wt, ft, start_time, tat, pr;
	};

bool operator<(const Process &p1, const Process &p2)
	{
	return p1.pr < p2.pr;
	}

void priority(vector<Process> processes)
	{
	vector<Process> processQueue;
	int i = 0, timeCount = 0, totalWt = 0,totalTat = 0, counter = 0;
	float avgWt, avgTat;
	//ofstream ofile ("output.txt");
	while(counter < processes.size())
		{
		for (int j = i; j < processes.size(); j++)
			{
			if(processes[j].at <= timeCount)
				{
				processQueue.push_back(processes[j]);
				i++; //thus at any inst i's value is equal to the index of the next process to be appended
				}	
			}
		//cout<<i<<endl;
		sort(processQueue.begin(), processQueue.end());
		processQueue[0].start_time = timeCount; 
		timeCount = timeCount + processQueue[0].st;
		processQueue[0].wt = processQueue[0].start_time - processQueue[0].at;
		processQueue[0].ft = processQueue[0].start_time + processQueue[0].st;
		processQueue[0].tat = processQueue[0].ft - processQueue[0].at;
		totalWt = totalWt + processQueue[0].wt;
		totalTat = totalTat + processQueue[0].tat;
		cout<<processQueue[0].pid<<" "<<processQueue[0].ft<<" "<<processQueue[0].wt<<" "<<processQueue[0].tat<<" "<<endl;
		processQueue[0].pr = 9999999;
		counter++;
		}
	avgWt = float((totalWt*1.0)/processes.size());
	avgTat = float((totalTat*1.0)/processes.size());
	cout<<avgWt<<" "<<avgTat<<endl;
	}

int main()
	{
	ifstream ifile ("test1.txt");
	vector<Process> processes;
	Process newprocess;
	while(!ifile.eof())
		{
		if(ifile.eof())
			break;
		ifile>>newprocess.pid>>newprocess.at>>newprocess.st>>newprocess.pr;
		processes.push_back(newprocess);
		}
	/*for (int i = 0; i < processes.size(); i++)
	{
		cout<<processes[i].pid<<processes[i].at<<processes[i].st<<endl;
	}*/
	ifile.close();
	priority(processes);
	return 0;
	}