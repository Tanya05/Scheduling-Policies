#include "process.h"
#include <iostream>
using namespace std;

Process :: Process( string pid, int arrivaltime, int servicetime, int pr ) {
	
	pID = pid;
	arrivalTime = arrivaltime;
	serviceTime = servicetime;
	priority = pr;
	
}
	
