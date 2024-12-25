#pragma once
#include <queue>
#include <mutex>
#include <iostream>
#include "warehouse.h"
#include "supply.h"
extern std::mutex mutexForCout;
class SystemForPlacingProducts {
private:
	Warehouse* ptrToWarehouse;
	std::queue<Supply*> supplyQueue{};
	std::mutex mutex_;
public:
	SystemForPlacingProducts(Warehouse* ptr) :
		ptrToWarehouse(ptr)
	{}
	void run()
	{
		while (true)
		{
			if (!supplyQueue.empty())
			{
				ptrToWarehouse->mutexLock();
				Supply** ptr = checkPlaceForSupply();
				if (*ptr != nullptr) {
					ptrToWarehouse->rejectSupply(ptr);
				}
				mutex_.lock();
				ptrToWarehouse->placeSupply(ptr, supplyQueue.front());
				supplyQueue.pop();
				mutex_.unlock();
				ptrToWarehouse->mutexUnlock();
			}
		}
	}
	Supply** checkPlaceForSupply()
	{
		Supply** ptr1 = ptrToWarehouse->getPtrToNextInserted();
		if (*ptr1 != nullptr)
		{
			Supply** ptr2 = ptrToWarehouse->findPlaceForSupply();
			if (ptr1 == ptr2)
			{
				std::cout << "!!warehouse overflow!!\n";
			}
			return ptr2;
		}
		return ptr1;
	}
	bool acceptSupply(Supply* sup)
	{
		mutex_.lock();
		supplyQueue.push(sup);
		mutex_.unlock();
		mutexForCout.lock();
		std::cout << "SystemForPlacingProducts: " << "supply " << sup->getId() << " was accepted\n";
		mutexForCout.unlock();
		return true;
	}
};
