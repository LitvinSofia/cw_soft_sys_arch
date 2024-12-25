#ifndef SYSTEM_FOR_PLACING_PRODUCTS_H
#define SYSTEM_FOR_PLACING_PRODUCTS_H
#include <queue>
#include <mutex>
#include <iostream>
#include "warehouse.h"
extern std::mutex mutexForCout;
class Supply;
class Warehouse;
class SystemForPlacingProducts {
private:
	Warehouse* ptrToWarehouse;
	std::queue<Supply*> supplyQueue{};
	std::mutex mutex_;
public:
	SystemForPlacingProducts(Warehouse* ptr);
	void run();
	Supply** checkPlaceForSupply();
	bool acceptSupply(Supply* sup);
};
#endif
