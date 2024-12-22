#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <string>
#include <vector>
#include <random>
#include <windows.h>
#include <memory>
class Supply {
private:
	int factoryPriority_;
public:
	Supply(int factPriority) :
		factoryPriority_(factPriority)
	{}
};
class Warehouse {
private:
	std::vector<Supply*> warehouse{};
	std::vector<Supply*>::iterator pointerToNextInserted;
public:
	Warehouse():
		pointerToNextInserted(warehouse.begin())
	{}
	Supply* chooseSupply() {};
	Supply** findPlaceForSupply() {};
	Supply** getPtrToNextInserted() {};
	bool isEmpty() {};
	void placeSupply(Supply** place, Supply* newSupply) {};
	void rejectSupply(Supply**) {};
};
class SystemForPlacingProducts {
private:
	Warehouse* ptrToWarehouse;
	std::queue<Supply> supplyQueue{};
public:
	SystemForPlacingProducts(Warehouse* ptr) :
		ptrToWarehouse(ptr)
	{}
	Supply** checkPlaceForSupply() {};
	bool acceptSupply(Supply sup)
	{
		supplyQueue.push(sup);
		std::cout << "pushed\n";
		return true;
	};
};

class Factory {
private:
	size_t priority_;
	SystemForPlacingProducts* ptrToPlacing_;
public:
	Factory(size_t priority, SystemForPlacingProducts* ptr):
		priority_(priority),
		ptrToPlacing_(ptr)
	{}
	void supplyProducts() {
		while (true) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis1(1, 100);
			int random_number = dis1(gen);
			Sleep(random_number*10);
			std::normal_distribution<> dis2(1, 1);
			int factoryPriority = static_cast<int>(dis2(gen));
			std::cout << factoryPriority << '\n';
			ptrToPlacing_->acceptSupply(Supply{factoryPriority});
		}
	};
};
class Truck {
private:
	bool available;
public:
	void deliverSupply() {};
	bool isAvailable() {};
};
class Garage {
private:
	Truck* pointerToNextTruck;
	std::vector<Truck> garage;
	bool available = false;
public:
	Truck* chooseTruck() {};
	bool atLeastOneIsAvailable() {};
};
class WarehouseUnloadingSystem {
private:
	Garage* pointerToGarage;
	Warehouse* pointerToWarehouse;
};

int main(){
	Warehouse h;
	SystemForPlacingProducts sys(&h);
	Factory f(1, &sys);
	std::thread thread1(&Factory::supplyProducts, &f);
	thread1.join();
	return 0;
}