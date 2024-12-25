#include "warehouse.h"
Warehouse::Warehouse() :
	pointerToNextInserted(warehouse_)
{}
void Warehouse::mutexLock()
{
	warehouseMutex_.lock();
}
void Warehouse::mutexUnlock()
{
	warehouseMutex_.unlock();
}
Supply* Warehouse::chooseSupply()
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
Supply** Warehouse::findPlaceForSupply()
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
Supply** Warehouse::getPtrToNextInserted() {
	return pointerToNextInserted;
};
bool Warehouse::isEmpty()
{
	if (size_ > 0)
	{
		return false;
	}
	return true;
};
void Warehouse::printWarehouse()
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
void Warehouse::placeSupply(Supply** place, Supply* newSupply)
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
	std::cout << "Pointer to next inserted supply: "<< pointerToNextInserted - warehouse_ <<"\n";
	mutexForCout.unlock();
	printWarehouse();
}
void Warehouse::rejectSupply(Supply** placeToReject)
{
	size_--;
	printWarehouse();
	mutexForCout.lock();
	std::cout << "supply  with id = " << (*placeToReject)->getId() << " was rejected\n";
	mutexForCout.unlock();
	Supply* ptr = *placeToReject;
	size_t req = ptr->getPointerToFactory()->getFailedRequests();
	ptr->getPointerToFactory()->setFailedRequests(req + 1);
	size_t req1 = ptr->getPointerToFactory()->getAllRequests();
	ptr->getPointerToFactory()->setAllRequests(req1 + 1);
	*placeToReject = nullptr;
	delete ptr;
	printWarehouse();
}