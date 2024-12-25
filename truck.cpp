#include "truck.h"
#include "supply.h"
#include <map>
#include <fstream>
#define FACTORY_AMOUNT 3
std::map<uint32_t, uint64_t> statDevice;
std::map<size_t, Factory*> statFactory;
void Truck::setId(size_t id)
{
	id_ = id;
}
size_t Truck::getId()
{
	return id_;
}
void Truck::deliverSupply(Supply* supply)
{
	auto start = std::chrono::system_clock::now();
	mutexForCout.lock();
	std::cout << "TRUCK " << id_ << ": delivers supply with id = " << supply->getId() << "\n";
	mutexForCout.unlock();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::exponential_distribution<> dis1(1.2);
	double random_number = dis1(gen);
	Sleep(random_number * 1000);
	mutexForCout.lock();
	std::cout << " supply " << supply->getId() << " was delivered by truck " << id_ << "\n";
	mutexForCout.unlock();
	auto end = std::chrono::system_clock::now();
	statDevice[this->id_] += std::chrono::duration_cast<std::chrono::milliseconds>((end - start)).count();
	if (supply != nullptr && supply->getId() % 10 == 0) {
		std::ofstream out;
		out.open("devices.txt");
		for (int i = 0; i < capacityOfGarage; i++)
		{
			end = std::chrono::system_clock::now();
			allTime = (std::chrono::duration_cast<std::chrono::milliseconds>((end - time_begin)).count());
			out << "DEVICE " << i << ": " << (long double)statDevice[i] / allTime << '\n';
		}
		out.close();
	}

	supply->getPointerToFactory()->addDurationsWait(
		std::chrono::duration_cast<std::chrono::milliseconds>(start - (supply->getTime())).count());
	supply->getPointerToFactory()->addDurationsProcess(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

	size_t req = supply->getPointerToFactory()->getSuccessfulRequests();
	supply->getPointerToFactory()->setSuccessfulRequests(req + 1);

	size_t req1 = supply->getPointerToFactory()->getAllRequests();
	supply->getPointerToFactory()->setAllRequests(req1 + 1);
	statFactory[supply->getPointerToFactory()->getId()] = supply->getPointerToFactory();
	if ((supply->getPointerToFactory()->getAllRequests()) % 10 == 0 && supply->getPointerToFactory()->getAllRequests() != 0) {
		std::ofstream out;
		out.open("factories.txt");
		for (uint32_t i = 0; i < FACTORY_AMOUNT; i++) {
			out << "FACTORY " << i << " statistic: ALL: " << statFactory[i]->getAllRequests() << " success: "
				<< statFactory[i]->getSuccessfulRequests() << " declined: " << statFactory[i]->getFailedRequests() << '\n';
			out << "waitDurations: ";
			for (double j : statFactory[i]->getDurationsWait()) {
				out << j << ' ';
			}
			out << '\n' << "Processing durations: ";
			for (double j : statFactory[i]->getDurationsProcess()) {
				out << j << ' ';
			}
			out << '\n';
		}
		out.close();
	}
	delete supply;
	supplyToDeliver_ = nullptr;
	this->setAvailable(true);
}
bool Truck::isAvailable()
{
	return available_;
}
void Truck::setAvailable(bool available)
{
	available_ = available;
}
void Truck::setSupply(Supply* supply)
{
	this->supplyToDeliver_ = supply;
}
void Truck::run()
{
	while (true)
	{
		if (this->available_ == false && this->supplyToDeliver_ != nullptr)
		{
			this->deliverSupply(supplyToDeliver_);
		}
		else
		{
			Sleep(1);
		}
	}
}