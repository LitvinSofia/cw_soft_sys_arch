#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <string>
#include <vector>
#include <random>
class Product {
private:
	std::string name;
	float price;
	float weight;
	float priceForKg;
};
class Supply {
private:
	std::string date;
	std::vector<Product> products;
	int factoryPriority;
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
	Warehouse* ptrToWareHouse;
	std::queue<Supply*> supplyQueue;
public:
	Supply** checkPlaceForSupply() {};
};

class Factory {
private:
	size_t priority;
	SystemForPlacingProducts* ptrToPlacing;
public:
	void supplyProducts() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(1, 100);
		int random_number = dis(gen);
		int arr[101] = {};
		
			arr[dis(gen)]++;
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
	Factory f;
	f.supplyProducts();
	return 0;
}