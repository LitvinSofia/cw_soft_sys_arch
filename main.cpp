#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <string>
#include <vector>
#include <random>
#include <windows.h>
#include <memory>
constexpr size_t capacity = 20;
class Supply {
private:
	size_t factoryPriority_;
public:
	Supply(size_t factPriority) :
		factoryPriority_(factPriority)
	{}
};
class Warehouse {
private:
	size_t size_;
	Supply* warehouse_[capacity] = {};
	Supply** pointerToNextInserted;
public:
	Warehouse():
		pointerToNextInserted(warehouse_)
	{}
	Supply* chooseSupply() {};
	Supply** findPlaceForSupply() 
	{
		std::cout << "find\n";
		for (Supply** i = pointerToNextInserted; i < &warehouse_[capacity]; i++)
		{
			if (*i == nullptr)
			{
				return i;
			}
		}
		for(Supply** i = &warehouse_[0]; i < pointerToNextInserted; i++)
		{ 
			if (*i == nullptr)
			{
				return i;
			}
		}
		return pointerToNextInserted;
	};
	Supply** getPtrToNextInserted() {
		return pointerToNextInserted;
	};
	bool isEmpty() 
	{
		for (size_t i = 0; i < capacity; i++)
		{
			if (warehouse_[i] != nullptr)
			{
				return false;
			}
		}
		return true;
	};
	void placeSupply(Supply** place, Supply* newSupply) 
	{
		//*place = 
	}
	void rejectSupply(Supply**)
	{

	}
};
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
				Supply** ptr = checkPlaceForSupply();
				if (*ptr == nullptr) {
					ptrToWarehouse->rejectSupply(ptr);
					std::cout << "reject\n";
				}
				mutex_.lock();
				ptrToWarehouse->placeSupply(ptr, supplyQueue.front());
				std::cout << "place\n";
				supplyQueue.pop();
				mutex_.unlock();
			}
		}
	}
	Supply** checkPlaceForSupply()
	{
		std::cout << "check place for supply\n";
		Supply** ptr1 = ptrToWarehouse->getPtrToNextInserted();
		std::cout <<ptr1 << ": get ptr1\n";
		if (ptr1 != nullptr)
		{
			Supply** ptr2 = ptrToWarehouse->findPlaceForSupply();
			std::cout << ptr2 << ": get ptr2\n";
			if (ptr1 == ptr2)
			{
				std::cout << "warehouse overflow\n";
			}
			return ptr2;
		}
	};
	bool acceptSupply(Supply* sup)
	{
		mutex_.lock();
		supplyQueue.push(sup);
		mutex_.unlock();
		std::cout << "pushed\n";
		return true;
	};
};

class Factory {
private:
	size_t priority_;
	SystemForPlacingProducts* ptrToPlacing_;
public:
	Factory(size_t priority, SystemForPlacingProducts* ptr) :
		priority_(priority),
		ptrToPlacing_(ptr)
	{}
	void supplyProducts() {
		while (true) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis1(1, 100);
			int random_number = dis1(gen);
			Sleep(random_number * 50);
			std::cout << priority_<<'\n';
			ptrToPlacing_->acceptSupply(new Supply{ priority_ });
		}
	};
};
class Truck {
private:
	bool available;
public:
	void deliverSupply() {
		//delete
	};
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

int main() {
	Warehouse h;
	SystemForPlacingProducts sys(&h);
	Factory f1(1, &sys);
	Factory f2(2, &sys);
	Factory f3(3, &sys);
	std::thread thread1(&Factory::supplyProducts, &f1);
	std::thread thread2(&Factory::supplyProducts, &f2);
	std::thread thread3(&Factory::supplyProducts, &f3);
	thread1.join();
	return 0;
}