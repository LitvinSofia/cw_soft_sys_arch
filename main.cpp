#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <string>
#include <vector>
#include <random>
#include <windows.h>
#include <memory>
class Product {
private:
	std::string name_;
	float price_;
	float weight_;
	float priceForKg_;
public:
	Product(std::string name, float price, float weight):
		name_(name),
		price_(price),
		weight_(weight),
		priceForKg_(price*weight)
	{}
};
class Supply {
private:
	std::string date_;
	std::vector<Product> products_;
	int factoryPriority_;
public:
	Supply(std::string date, std::vector<Product> products, int factPriority) :
		date_(date),
		products_(products),
		factoryPriority_(factPriority)
	{}
};
class Warehouse {
private:
	std::vector<Supply*> warehouse;
	Supply** pointerToNextInserted;
public:
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
	SystemForPlacingProducts() :
		supplyQueue()
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
			std::uniform_int_distribution<> dis(1, 100);
			int random_number = dis(gen);
			Sleep(random_number*10);
			std::string date = "";
			std::vector<Product> products{};
			int factoryPriority = 1;
			ptrToPlacing_->acceptSupply(Supply{ date, products, factoryPriority });
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
	SystemForPlacingProducts sys;
	Factory f(1, &sys);
	std::thread thread1(&Factory::supplyProducts, &f);
	thread1.join();
	return 0;
}