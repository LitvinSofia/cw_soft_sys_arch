#ifndef WAREHOUSE_UNLOADING_SYSTEM_H
#define WAREHOUSE_UNLOADING_SYSTEM_H
#include <Windows.h>
#include <mutex>
extern std::mutex mutexForCout;
#include "garage.h"
#include "warehouse.h"
class WarehouseUnloadingSystem {
private:
	Garage* pointerToGarage_;
	Warehouse* pointerToWarehouse_;
public:
	WarehouseUnloadingSystem(Garage* g, Warehouse* w);
	void run();
};
#endif