#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <string>
#include <vector>
#include <random>
#include <windows.h>
#include <memory>
#include <limits>
#undef max
constexpr size_t capacityOfWarehouse = 20;
constexpr size_t capacityOfGarage = 10;
constexpr size_t max_priority = std::numeric_limits<size_t>::max();
constexpr size_t max_id = std::numeric_limits<size_t>::max();
class Supply {
private:
	size_t id_;
	size_t factoryPriority_;
public:
	Supply(size_t factPriority, size_t id) :
		factoryPriority_(factPriority),
		id_(id)
	{}
	size_t getId()
	{
		return id_;
	}
	size_t getFactoryPriority()
	{
		return factoryPriority_;
	}
};
class Warehouse {
private:
	size_t size_ = 0;
	Supply* warehouse_[capacityOfWarehouse] = {};
	Supply** pointerToNextInserted;
public:
	Warehouse() :
		pointerToNextInserted(warehouse_)
	{}
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
		std::cout << "find place for supply\n";
		for (Supply** i = pointerToNextInserted; i < &warehouse_[capacityOfWarehouse]; i++)
		{
			if (*i == nullptr)
			{
				return i;
			}
		}
		for (Supply** i = &warehouse_[0]; i < pointerToNextInserted; i++)
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
		if (size_ > 0)
		{
			return false;
		}
		return true;
	};
	void placeSupply(Supply** place, Supply* newSupply)
	{
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
		std::cout << "inserted new supply to warehouse\n";
	}
	void rejectSupply(Supply** placeToReject)
	{
		size_--;
		std::cout << "supply was rejected from warehouse\n";
		delete* placeToReject;
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
				if (*ptr != nullptr) {
					size_t id = 0;
					id = (*ptr)->getId();
					ptrToWarehouse->rejectSupply(ptr);
					std::cout << "rejected supply with id = " << id << "\n";
				}
				mutex_.lock();
				ptrToWarehouse->placeSupply(ptr, supplyQueue.front());
				supplyQueue.pop();
				mutex_.unlock();
			}
		}
	}
	Supply** checkPlaceForSupply()
	{
		std::cout << "check place for supply\n";
		Supply** ptr1 = ptrToWarehouse->getPtrToNextInserted();
		std::cout << ptr1 << ": get ptr1\n";
		if (*ptr1 != nullptr)
		{
			Supply** ptr2 = ptrToWarehouse->findPlaceForSupply();
			std::cout << ptr2 << ": get ptr2\n";
			if (ptr1 == ptr2)
			{
				std::cout << "warehouse overflow\n";
			}
			return ptr2;
		}
		return ptr1;
	}
	bool acceptSupply(Supply* sup)
	{
		mutex_.lock();
		supplyQueue.push(sup);
		mutex_.unlock();
		std::cout << "supply " << sup->getId() << " was accepted\n";
		return true;
	}
};
class Factory {
private:
	static size_t id_;
	size_t priority_;
	SystemForPlacingProducts* ptrToPlacing_;
public:
	Factory(size_t priority, SystemForPlacingProducts* ptr) :
		priority_(priority),
		ptrToPlacing_(ptr)
	{}
	void supplyProducts()
	{
		while (true) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis1(1, 5);
			int random_number = dis1(gen);
			Sleep(random_number * 1000);
			std::cout << id_ << '\n';
			ptrToPlacing_->acceptSupply(new Supply{ priority_, id_++ });
		}
	};
};
size_t Factory::id_ = 0;
class Truck {
private:
	bool available_ = true;
	Supply* supplyToDeliver_ = nullptr;
public:
	void deliverSupply(Supply* supply)
	{
		this->setAvailable(false);
		std::cout << "deliver supply with id = " << supply->getId() << "\n";
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis1(1, 100);
		int random_number = dis1(gen);
		Sleep(random_number * 50);
		std::cout << " supply " << supply->getId() << " was delivered\n";
		delete supply;
		supplyToDeliver_ = nullptr;
		this->setAvailable(true);
	};
	bool isAvailable()
	{
		return available_;
	}
	void setAvailable(bool available)
	{
		available_ = available;
	}
	void setSupply(Supply* supply)
	{
		this->supplyToDeliver_ = supply;
	}
	void run()
	{
		while (true)
		{
			if (this->available_ == true && this->supplyToDeliver_ != nullptr)
			{
				this->deliverSupply(supplyToDeliver_);
			}
			else
			{
				Sleep(1);
			}
		}
	}
};
class Garage {
private:
	Truck* pointerToNextTruck_;
	Truck garage_[capacityOfGarage];
	bool available_ = false;
public:
	Garage(Truck arr[]) :
		pointerToNextTruck_(garage_)
	{
		std::copy(arr, arr + capacityOfGarage, garage_);
	}
	Truck* getGarage()
	{
		return garage_;
	}
	Truck* chooseTruck()
	{
		for (Truck* i = pointerToNextTruck_; i < garage_ + capacityOfGarage - 1; i++)
		{
			if (i->isAvailable() == true)
			{
				pointerToNextTruck_ = i + 1;
				return i;
			}
		}
		if (garage_[capacityOfGarage - 1].isAvailable() == true)
		{
			pointerToNextTruck_ = garage_;
			return &garage_[capacityOfGarage - 1];
		}
		for (Truck* i = garage_; i < pointerToNextTruck_; i++)
		{
			if (i->isAvailable() == true)
			{
				pointerToNextTruck_++;
				return i;
			}
		}
		std::cout << "there is no free trucks\n";
		return nullptr;
	}
	bool atLeastOneIsAvailable()
	{
		bool flag = false;
		for (size_t i = 0; i < capacityOfGarage; i++)
		{
			flag = flag || garage_[i].isAvailable();
			if (flag == true)
			{
				return flag;
			}
		}
		return flag;
	}
};
class WarehouseUnloadingSystem {
private:
	Garage* pointerToGarage_;
	Warehouse* pointerToWarehouse_;
public:
	WarehouseUnloadingSystem(Garage* g, Warehouse* w) :
		pointerToGarage_(g),
		pointerToWarehouse_(w)
	{}
	void run()
	{
		while (true) {
			if (pointerToGarage_->atLeastOneIsAvailable() && (!pointerToWarehouse_->isEmpty()))
			{
				Supply* supplyToDeliver = pointerToWarehouse_->chooseSupply();
				Truck* truckToDeliver = pointerToGarage_->chooseTruck();
				truckToDeliver->setSupply(supplyToDeliver);
			}
			else
			{
				Sleep(1);
			}
		}
	}
};

int main() {
	Warehouse h{};
	SystemForPlacingProducts sys1(&h);
	Factory f1(1, &sys1);
	Factory f2(2, &sys1);
	Factory f3(3, &sys1);
	Truck truck1{};
	Truck truck2{};
	Truck truck3{};
	Truck truck4{};
	Truck truck5{};
	Truck truck6{};
	Truck truck7{};
	Truck truck8{};
	Truck truck9{};
	Truck truck10{};
	Truck arr[capacityOfGarage] = { truck1 , truck2, truck3, truck4, truck5, truck6, truck7, truck8, truck9, truck10};
	Garage g(arr);
	WarehouseUnloadingSystem sys2(&g, &h);
	std::thread thread1(&Factory::supplyProducts, &f1);
	std::thread thread2(&Factory::supplyProducts, &f2);
	std::thread thread3(&Factory::supplyProducts, &f3);
	std::thread thread4(&SystemForPlacingProducts::run, &sys1);
	std::thread thread5(&WarehouseUnloadingSystem::run, &sys2);
	std::thread threads[capacityOfGarage] = {};
	for (size_t i = 0; i < capacityOfGarage; i++)
	{
		threads[i] = std::thread{ &Truck::run, &(g.getGarage()[i]) };
	}
	thread1.join();
	return 0;
}