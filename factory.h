#pragma once
#include <random>
#include <vector>
#include <Windows.h>
#include "supply.h"
#include "system_for_placing_products.h"
extern std::mutex mutexForCout;
struct FactoryStatistic {
	size_t allRequests{};
	size_t successfulRequests{};
	size_t failedRequests{};
	std::vector<double> durationsProcess{};
	std::vector<double> durationsWait{};
};
class Factory {
private:
	static size_t id_;
	size_t priority_;
	SystemForPlacingProducts* ptrToPlacing_;
	FactoryStatistic statistic_{};
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
			std::cout << "FACTORY " << priority_ << ": supply " << id_ << '\n';
			ptrToPlacing_->acceptSupply(new Supply{ priority_, id_++ , this});
		}
	};
};
size_t Factory::id_ = 0;