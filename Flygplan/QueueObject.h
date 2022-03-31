#pragma once
#include "Airplane.h"
#include "Data.h"
class QueueObject {
public: 
	QueueObject(Airplane* ptr) : next(nullptr), prev(nullptr), owner(ptr) {}
	~QueueObject() { delete owner; *this = nullptr; }

private:
	QueueObject* next, *prev;
	Data* owner;


public:
	QueueObject* Next() { return next; }
 	QueueObject* Prev() { return prev; }
	Data* Owner() { return owner; }

	void Next(QueueObject* ptr) { next = ptr; }
	void Prev(QueueObject* ptr) { prev = ptr; }
	void Owner(Data* ptr) { owner = ptr; }
};

