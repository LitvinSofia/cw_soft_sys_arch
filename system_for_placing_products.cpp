#include "system_for_placing_products.h"
SystemForPlacingProducts::SystemForPlacingProducts(Warehouse* ptr) :
	ptrToWarehouse(ptr)
{}
void SystemForPlacingProducts::run()
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
Supply** SystemForPlacingProducts::checkPlaceForSupply()
{
	Supply** ptr1 = ptrToWarehouse->getPtrToNextInserted();
	if (*ptr1 != nullptr)
	{
		Supply** ptr2 = ptrToWarehouse->findPlaceForSupply();
		if (ptr1 == ptr2)
		{
			mutexForCout.lock();
			std::cout << "!!warehouse overflow!!\n";
			mutexForCout.unlock();
		}
		return ptr2;
	}
	return ptr1;
}
bool SystemForPlacingProducts::acceptSupply(Supply* sup)
{
	mutex_.lock();
	supplyQueue.push(sup);
	mutex_.unlock();
	mutexForCout.lock();
	std::cout << "SystemForPlacingProducts: " << "supply " << sup->getId() << " was accepted\n";
	mutexForCout.unlock();
	return true;
}