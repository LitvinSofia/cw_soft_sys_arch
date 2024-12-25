#pragma once
#include <limits>
#include <mutex>
#include "supply.h"
#undef max
extern std::mutex mutexForCout;
constexpr size_t capacityOfWarehouse = 5;
constexpr size_t max_priority = std::numeric_limits<size_t>::max();
constexpr size_t max_id = std::numeric_limits<size_t>::max();
class Warehouse {
private:
	size_t size_ = 0;
	Supply* warehouse_[capacityOfWarehouse] = {};
	Supply** pointerToNextInserted;
	std::mutex warehouseMutex_;
public:
	Warehouse() :
		pointerToNextInserted(warehouse_)
	{}
	void mutexLock()
	{
		warehouseMutex_.lock();
	}
	void mutexUnlock()
	{
		warehouseMutex_.unlock();
	}
	Supply* chooseSupply()
	{
		size_t priority = max_priority;
		size_t id = max_id;
		Supply* supply = nullptr;
		size_t index = 0;
		for (size_t i = 0; i < capacityOfWarehouse; i++)
		{
			if (warehouse_[i] != nullptr && warehouse_[i]->getFactoryPriority() < priority)
			{
				priority = warehouse_[i]->getFactoryPriority();
				id = warehouse_[i]->getId();
				supply = warehouse_[i];
				index = i;
			}
			else if (warehouse_[i] != nullptr && warehouse_[i]->getFactoryPriority() == priority)
			{
				if (warehouse_[i]->getId() < id)
				{
					supply = warehouse_[i];
					priority = warehouse_[i]->getFactoryPriority();
					id = warehouse_[i]->getId();
					index = i;
				}
			}
		}
		size_--;
		warehouse_[index] = nullptr;
		return supply;
	}
	Supply** findPlaceForSupply()
	{
		for (Supply** i = pointerToNextInserted; i < warehouse_ + capacityOfWarehouse; i++)
		{
			if (*i == nullptr)
			{
				return i;
			}
		}
		for (Supply** i = warehouse_; i < pointerToNextInserted; i++)
		{
			if (*i == nullptr)
			{
				return i;
			}
		}
		return pointerToNextInserted;
	}
	Supply** getPtrToNextInserted() {
		return pointerToNextInserted;
	};
	bool isEmpty()
	{
		if (size_ > 0)
		{
			return false;
		}
		return true;
	};
	void printWarehouse()
	{
		mutexForCout.lock();
		std::cout << "WAREHOUSE: ";
		for (size_t i = 0; i < capacityOfWarehouse; i++)
		{
			if (warehouse_[i] != nullptr)
			{
				std::cout << warehouse_[i]->getId() << ' ';
			}
			else {
				std::cout << " _ ";
			}
		}
		std::cout << '\n';
		mutexForCout.unlock();
	}
	void placeSupply(Supply** place, Supply* newSupply)
	{
		printWarehouse();
		*place = newSupply;
		size_++;
		if (place < warehouse_ + capacityOfWarehouse - 1)
		{
			pointerToNextInserted = place + 1;
		}
		else
		{
			pointerToNextInserted = warehouse_;
		}
		mutexForCout.lock();
		std::cout << "inserted suppply " << newSupply->getId() << " in warehouse\n";
		mutexForCout.unlock();
		printWarehouse();
	}
	void rejectSupply(Supply** placeToReject)
	{
		size_--;
		printWarehouse();
		mutexForCout.lock();
		std::cout << "supply  with id = " << (*placeToReject)->getId() << " was rejected\n";
		mutexForCout.unlock();
		Supply* ptr = *placeToReject;
		*placeToReject = nullptr;
		delete ptr;
		printWarehouse();
	}
};