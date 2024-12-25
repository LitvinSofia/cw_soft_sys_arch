#ifndef FACTORY_H
#define FACTORY_H
#include <random>
#include <vector>
#include <Windows.h>
class Supply;
#include "system_for_placing_products.h"
class SystemForPlacingProducts;
extern std::mutex mutexForCout;
struct FactoryStatistic {
	size_t allRequests{};
	size_t successfulRequests{};
	size_t failedRequests{};
	std::vector<double> durationsProcess{};//время которое заявка обслуживалась
	std::vector<double> durationsWait{};//время до обслуживания заявки чтобы среднее считать
};
class Factory {
private:
	static size_t id_;
	size_t priority_;
	SystemForPlacingProducts* ptrToPlacing_;
	FactoryStatistic statistic_{};
public:
	Factory(size_t priority, SystemForPlacingProducts* ptr);
	void setAllRequests(size_t all);
	size_t getAllRequests();
	void setSuccessfulRequests(size_t successful);
	size_t getSuccessfulRequests();
	void setFailedRequests(size_t failed);
	size_t getFailedRequests();
	void addDurationsProcess(double process);
	void addDurationsWait(double wait);
	void supplyProducts();
};
#endif