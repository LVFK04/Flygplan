#pragma once
#include<iostream>
#include <random>
#include "Data.h"
#include "Airplane.h"
#include "QueueObject.h"
class Controller {
public:
	Controller() : qLenghtAir(0), qLenghtGround(0), available(true), simTime(0), numLanded(0), numTakenOff(0),
		           averageWaitTimeAir(0), averageWaitTimeGround(0) {}

	~Controller(){}

private:
	unsigned int qLenghtAir;
	static QueueObject* firstAir;
	static QueueObject* lastAir;

	unsigned int qLenghtGround;
	static QueueObject* firstGround;
	static QueueObject* lastGround;
	unsigned int simTime;
	static int landTime;
	bool available;
	unsigned int numLanded;
	unsigned int numTakenOff;
	double averageWaitTimeAir;
	double averageWaitTimeGround;
	
	void addPlaneAir();
	void removePlaneAir();
	void addPlaneGround();
	void removePlaneGround();
	void crashPlane(QueueObject* ptr);

public:
	static unsigned int numCrashed;
	static unsigned int longestWaitTimeAir;
	static unsigned int longestWaitTimeGround;
	
	void tick(unsigned int r);
	void info();

	unsigned int qLengthAir() { return qLenghtAir; }
	unsigned int qLengthGround() { return qLenghtGround; }
};

