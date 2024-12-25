#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <windows.h>
#include <memory>
#include <map>
#include <fstream>
#include "warehouse.h"
#include "supply.h"
#include "system_for_placing_products.h"
#include "factory.h"
#include "garage.h"
#include "warehouse_unloading_system.h"
#include "truck.h"
std::mutex mutexForCout;
struct FactoryStatistic {
	uint32_t allRequests{};
	uint32_t successfulRequests{};
	uint32_t failedRequests{};
	std::vector<double> durationsProcess{};
	std::vector<double> durationsWait{};
};
std::map<uint32_t, FactoryStatistic> statisticByUser;
std::mutex statMut;
int main() {
	Warehouse h{};
	SystemForPlacingProducts sys1(&h);
	Factory f1(1, &sys1);
	Factory f2(2, &sys1);
	Factory f3(3, &sys1);
	Truck arr[capacityOfGarage] = { Truck{} };
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
		g.getGarage()[i].setId(i);
	}
	for (size_t i = 0; i < capacityOfGarage; i++)
	{
		threads[i] = std::thread{ &Truck::run, &(g.getGarage()[i]) };
	}
	thread1.join();
	return 0;
}