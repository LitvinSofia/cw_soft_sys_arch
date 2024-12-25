#pragma once
#include <iostream>
#include <mutex>
extern std::mutex mutexForCout;
#include "truck.h"
constexpr size_t capacityOfGarage = 10;
class Garage {
private:
	Truck* pointerToNextTruck_;
	Truck garage_[capacityOfGarage];
	bool available_ = false;
public:
	Garage(Truck arr[]) :
		pointerToNextTruck_(garage_)
	{
		std::copy(arr, arr + capacityOfGarage, garage_);
	}
	Truck* getGarage()
	{
		return garage_;
	}
	Truck* chooseTruck()
	{
		for (Truck* i = pointerToNextTruck_; i < garage_ + capacityOfGarage - 1; i++)
		{
			if (i->isAvailable() == true)
			{
				pointerToNextTruck_ = i + 1;
				return i;
			}
		}
		if (garage_[capacityOfGarage - 1].isAvailable() == true)
		{
			pointerToNextTruck_ = garage_;
			return &garage_[capacityOfGarage - 1];
		}
		for (Truck* i = garage_; i < pointerToNextTruck_; i++)
		{
			if (i->isAvailable() == true)
			{
				pointerToNextTruck_++;
				return i;
			}
		}
		std::cout << "there is no free trucks\n";
		return nullptr;
	}
	bool atLeastOneIsAvailable()
	{
		bool flag = false;
		for (size_t i = 0; i < capacityOfGarage; i++)
		{
			flag = flag || garage_[i].isAvailable();
			if (flag == true)
			{
				return flag;
			}
		}
		return flag;
	}
};