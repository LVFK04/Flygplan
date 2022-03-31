#include "Airplane.h"

bool Airplane::wait() {
	if (inAir) {
		fuel--;
		waitTimeAir += 5;
		return fuel;
	}
	else
		waitTimeGround += 5;
		return true;
}

void Airplane::info() {
	
}