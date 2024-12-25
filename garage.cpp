#include "garage.h"
Garage::Garage(Truck arr[]) :
	pointerToNextTruck_(garage_)
{
	std::copy(arr, arr + capacityOfGarage, garage_);
}
Truck* Garage::getGarage()
{
	return garage_;
}
Truck* Garage::getPointerToNextTruck()
{
	return this->pointerToNextTruck_;
}
Truck* Garage::chooseTruck()
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
		return garage_ + capacityOfGarage - 1;
	}
	for (Truck* i = garage_; i < pointerToNextTruck_; i++)
	{
		if (i->isAvailable() == true)
		{
			if (pointerToNextTruck_ == garage_ + capacityOfGarage - 1)
			{
				pointerToNextTruck_ = garage_;
			}
			else
			{
				pointerToNextTruck_++;
			}
			return i;
		}
	}
	std::cout << "there is no free trucks\n";
	return nullptr;
}
bool Garage::atLeastOneIsAvailable()
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