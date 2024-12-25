#include "warehouse_unloading_system.h"
WarehouseUnloadingSystem::WarehouseUnloadingSystem(Garage* g, Warehouse* w) :
	pointerToGarage_(g),
	pointerToWarehouse_(w)
{}
void WarehouseUnloadingSystem::run()
{
	while (true) {

		if (pointerToGarage_->atLeastOneIsAvailable() && (!pointerToWarehouse_->isEmpty()))
		{
			pointerToWarehouse_->mutexLock();
			pointerToWarehouse_->printWarehouse();
			Supply* supplyToDeliver = pointerToWarehouse_->chooseSupply();
			mutexForCout.lock();
			std::cout << supplyToDeliver->getId() << " was chosen\n";
			mutexForCout.unlock();
			pointerToWarehouse_->printWarehouse();
			Truck* truckToDeliver = pointerToGarage_->chooseTruck();
			truckToDeliver->setSupply(supplyToDeliver);
			truckToDeliver->setAvailable(false);
			pointerToWarehouse_->mutexUnlock();
		}
		else
		{
			Sleep(1);
		}
	}
}