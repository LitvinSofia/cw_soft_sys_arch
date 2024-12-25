#ifndef GARAGE_H
#define GARAGE_H
#include <iostream>
#include <mutex>
extern std::mutex mutexForCout;
#define capacityOfGarage 10
#include "truck.h"
class Garage {
private:
	Truck* pointerToNextTruck_;
	Truck garage_[capacityOfGarage];
	bool available_ = false;
public:
	Garage(Truck arr[]);
	Truck* getGarage();
	Truck* chooseTruck();
	bool atLeastOneIsAvailable();
};
#endif