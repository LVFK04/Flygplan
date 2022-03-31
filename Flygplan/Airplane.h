#pragma once
#include "Data.h"
#include <iostream>
class Airplane : public Data{
public:
	Airplane(unsigned int f, bool iA) : waitTimeAir(0), waitTimeGround(0), fuel(f), inAir(iA) {}
	~Airplane(){}

private:
	unsigned int fuel;
	unsigned int waitTimeAir;
	unsigned int waitTimeGround;
	bool inAir;

public:
	unsigned int WaitTimeAir() { return waitTimeAir; }
	unsigned int WaitTimeGround() { return waitTimeGround; }
	unsigned int Fuel() { return fuel; }
	bool InAir() { return inAir; }

	void Fuel(unsigned int x) { fuel = x; }
	void InAir(bool x) { inAir = x; }
	void info();
	bool wait();
};

