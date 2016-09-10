#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include "process.cpp"
using namespace std;

vector <Process*> processes;

void readFile() {
	ifstream inputFile;
	inputFile.open("config.txt");
	string pID;
	int arrivalTime;
	int serviceTime;
	int priority;
	while( inputFile.good() ) {
		
		inputFile >> pID;
		inputFile >> arrivalTime;
		inputFile >> serviceTime;
		inputFile >> priority;
		Process* p = new Process( pID, arrivalTime, serviceTime, priority );
		processes.push_back( p );
		
	}
	inputFile.close();
	
}

void writeFile( char* file ) {
	ofstream outFile;
	outFile.open(file);
	outFile << "Process ID 	Arrival Time 	Service Time 	Priority 	Finish Time 	Turn around Time    Total Wait Time" << endl;
	for( int i = 0; i < processes.size()-1;i++ ) {
		//cout << i << " ";
		outFile << processes[i]->pID << " 		" << processes[i]->arrivalTime << " 		" << processes[i]->serviceTime << " 		" << processes[i]->priority << " 		" << processes[i]->finishTime << " 		" << processes[i]->TAT << "		 	" << processes[i]->waitTime << endl;
	}
	outFile.close();
}

void assign() {
	
	//setting finish times and wait times;
	//it is assumed that the first process arrives at time 0 and not some other instant
	processes[0]->finishTime = processes[0]->serviceTime;
	processes[0]->waitTime = 0;
	processes[0]->TAT = processes[0]->serviceTime;

	for( int i = 1; i < processes.size()-1; i++ ) {
		
		processes[i]->finishTime = processes[i-1]->finishTime + processes[i]->serviceTime;
		processes[i]->waitTime = processes[i-1]->finishTime - processes[i]->arrivalTime;
		if( processes[i]->waitTime < 0 )
			processes[i]->waitTime = 0;
		processes[i]->TAT = processes[i]->finishTime - processes[i]->arrivalTime;
	}
}

class SJFCompare {
	
	public:
		bool operator()( Process* p1, Process* p2 ) {
	
			if( p1->serviceTime < p2->serviceTime )	
				return true;
			else
				return false;
		}
};

void SJF() {
	
	//this method assumes that the process appear in increasing order of arrival time
	priority_queue <Process*, vector<Process*>, SJFCompare> queue;
	vector <Process*> sjf;
	int currentTime = 0;
	int i;
	for( i = 0; i < processes.size(); i++ ) {
		if( processes[i]->arrivalTime <= currentTime ) {
			queue.push( processes[i] );
		}
		Process* current = queue.top();
		queue.pop();
		currentTime += current->serviceTime;
		sjf.push_back( current );
	}
	
	for( int i = 0; i < sjf.size() - 1; i++ ) {
			processes[i] = sjf[i];
	}
	assign();
	writeFile( (char*)("SJFOutput.txt") );
		
}

bool FCFSCompare( Process* p1, Process* p2 ) {
	
	if( p1->arrivalTime < p2->arrivalTime )
		return true;
	if( p1->arrivalTime == p2->arrivalTime ) {
		if( p1->priority < p2->priority )
			return true;
		else
			return false;
	}
	return false;
}
		
void FCFS() {
	
	sort( processes.begin(), processes.end(), FCFSCompare );
	assign();
	writeFile( (char*)("FCFSOutput.txt") );
}

int main() {

	readFile();
	//FCFS();
	SJF();
	return 0;
}
