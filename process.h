#include <iostream>
#include <string>
using namespace std;

class Process {
	
	public : 	string pID;
				int arrivalTime;
				int serviceTime;
				int priority;
				int waitTime;
				int finishTime;
				int TAT;
				
				Process( string p, int, int, int );
				
			};
	
