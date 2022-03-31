#include <iostream>
#include <Windows.h>
#include "Data.h"
#include "Controller.h"
#include "Airplane.h"
#include "QueueObject.h"
using namespace std;

int main() {
	srand(time(nullptr));
	Controller a;
	unsigned int numRounds;
	cout << "How many minutes do you wish to simulate?" << endl;
	cin >> numRounds;
	numRounds /= 5;
	for (int i = 0; i < numRounds; i++) 
		a.tick(i);
	a.info();
}