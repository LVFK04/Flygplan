#include "Controller.h"
QueueObject* Controller::firstAir = nullptr;
QueueObject* Controller::lastAir = nullptr;
QueueObject* Controller::firstGround = nullptr;
QueueObject* Controller::lastGround = nullptr;
unsigned int Controller::numCrashed = 0;
unsigned int Controller::longestWaitTimeAir = 0;
unsigned int Controller::longestWaitTimeGround = 0;
int Controller::landTime = 0;

void Controller::addPlaneAir() {
	qLenghtAir++;
	srand(time(nullptr));
	QueueObject* newPlane = new QueueObject(new Airplane(rand() % 10 + 1, true)); //Creates a QueueObject and a flight with at least two rounds worth of fuel
	if (!firstAir) {
		firstAir = newPlane;
		newPlane->Prev(nullptr);
	}
	else
		newPlane->Prev(lastAir);
	
	lastAir = newPlane;
}

void Controller::removePlaneAir() {
	QueueObject* ptr = firstAir;
	delete firstAir->Owner();
	firstAir = ptr->Next();
	qLenghtAir--;
	numLanded++;
	averageWaitTimeAir += ((Airplane*)ptr->Owner())->WaitTimeAir();
	averageWaitTimeAir /= numLanded;
	averageWaitTimeAir *= 5;
}

void Controller::addPlaneGround() {
	qLenghtGround++;
	srand(time(nullptr));
	QueueObject* newPlane = new QueueObject(new Airplane(rand() % 10 + 1, false)); //Creates a QueueObject and a flight with at least two rounds worth of fuel
	if (!firstGround) {
		firstGround = newPlane;
		newPlane->Prev(nullptr);
	}
	else
		newPlane->Prev(lastGround);

	lastGround = newPlane;
}

void Controller::removePlaneGround() {
	QueueObject* ptr = firstGround;
	delete firstGround->Owner();
	firstGround = ptr->Next();
	qLenghtGround--;
	numTakenOff++;
	averageWaitTimeGround += ((Airplane*)ptr->Owner())->WaitTimeGround();
	averageWaitTimeGround /= numTakenOff;
	averageWaitTimeGround *= 5;
}

void Controller::tick(unsigned int r) {
	simTime += 5;

	if (!(rand() % 10))
		addPlaneAir();
	
	if (!(rand() % 10)) 
		addPlaneGround();
	
	
	if (qLenghtAir) {
		QueueObject* ptr = firstAir; //Creates a QueueObject pointer which points at the first flight in air
		while (ptr) {
			if (!ptr->Owner()->wait()) { //The airplane does the wait-function. If it is false:
				numCrashed++;          //numCrashed increases by one
				crashPlane(ptr);
			}
			if (((Airplane*)ptr->Owner())->WaitTimeAir() > longestWaitTimeAir)  //Checks if the flight ptr is pointing at has a longer waitTime than "longestWaitTime"
				longestWaitTimeAir = ((Airplane*)ptr->Owner())->WaitTimeAir();  //If this is true, whe change the longesWaitTime to that flights waitTime
			
			ptr = ptr->Next();
		}
	}

	if (qLenghtGround) {
		QueueObject* ptr = firstGround; //A QueueObject pointer which points at the first flight, waiting to take off
		while (ptr) {
			ptr->Owner()->wait();

			if (((Airplane*)ptr->Owner())->WaitTimeGround() > longestWaitTimeGround)  //Checks if the flight ptr is pointing at has a longer waitTime than "longestWaitTime"
				longestWaitTimeGround = ((Airplane*)ptr->Owner())->WaitTimeGround();  //If this is true, whe change the longesWaitTime to that flights waitTime

			ptr = ptr->Next(); //Makes the pointer point at the next flight in the list
		}
	}

	if (available && qLenghtAir) {
		available = false;
		landTime = simTime + 15;
	}

	if (simTime == landTime && simTime && qLenghtAir) {
		available = true;
		removePlaneAir();
	}

	if (available && qLenghtGround) {
		available = false;
		landTime = simTime + 15;
	}

	if (simTime == landTime && simTime && qLenghtGround) {
		available = true;
		removePlaneGround();
	}

	std::cout << "From minute " << r*5 << "-" << (r+1) * 5 << ": " << std::endl
		<< "Planes in air: " << qLenghtAir << std::endl
		<< "Planes on ground: " << qLenghtGround << std::endl;
}

void Controller::info() {
	std::cout << "Crashed: " << numCrashed << std::endl
		<< "Longest wait-time in air: " << longestWaitTimeAir << std::endl
		<< "Longest wait-time on ground: " << longestWaitTimeGround << std::endl
		<< "Average wait-time in air: " << averageWaitTimeAir << std::endl
		<< "Average wait-time on ground: " << averageWaitTimeGround << std::endl
		<< "Number of flights landed: " << numLanded << std::endl 
		<< "Number of flights taken off: " << numTakenOff << std::endl << std::endl << std::endl << std::endl << std::endl;
}

void Controller::crashPlane(QueueObject* ptr) {
	QueueObject* tmp = firstAir;
	while (tmp) {
		if (tmp == ptr) {
			tmp->Next(tmp->Prev());
			tmp->Prev(tmp->Next());
			delete tmp->Owner();
		}

		tmp = tmp->Next();
	}
	qLenghtAir--;
}