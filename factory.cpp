#include "factory.h"
size_t Factory::id_ = 0;
Factory::Factory(size_t priority, SystemForPlacingProducts* ptr) :
	priority_(priority),
	ptrToPlacing_(ptr)
{}
void Factory::setAllRequests(size_t all)
{
	this->statistic_.allRequests = all;
}
size_t Factory::getAllRequests()
{
	return this->statistic_.allRequests;
}
void Factory::setSuccessfulRequests(size_t successful)
{
	this->statistic_.successfulRequests = successful;
}
size_t Factory::getSuccessfulRequests()
{
	return this->statistic_.successfulRequests;
}
void Factory::setFailedRequests(size_t failed)
{
	this->statistic_.failedRequests = failed;
}
size_t Factory::getFailedRequests()
{
	return this->statistic_.failedRequests;
}
void Factory::addDurationsProcess(double process)
{
	this->statistic_.durationsProcess.emplace_back(process);
}
void Factory::addDurationsWait(double wait)
{
	this->statistic_.durationsWait.emplace_back(wait);
}
void Factory::supplyProducts()
{
	while (true) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis1(1, 5);
		int random_number = dis1(gen);
		Sleep(random_number * 1000);
		std::cout << "FACTORY " << priority_ << ": supply " << id_ << '\n';
		ptrToPlacing_->acceptSupply(new Supply{ priority_, id_++ , this });
	}
}