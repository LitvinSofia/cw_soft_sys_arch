#pragma once
#include <random>
#include <mutex>
#include "supply.h"
extern std::mutex mutexForCout;
class Truck {
private:
	size_t id_ = 0;
	bool available_ = true;
	Supply* supplyToDeliver_ = nullptr;
public:
	void setId(size_t id)
	{
		id_ = id;
	}
	size_t getId()
	{
		return id_;
	}
	void deliverSupply(Supply* supply)
	{
		mutexForCout.lock();
		std::cout << "TRUCK " << id_ << ": delivers supply with id = " << supply->getId() << "\n";
		mutexForCout.unlock();
		std::random_device rd;
		std::mt19937 gen(rd());
		std::exponential_distribution<> dis1(0.01);
		double random_number = dis1(gen);
		Sleep(random_number * 1000);
		mutexForCout.lock();
		std::cout << " supply " << supply->getId() << " was delivered by truck " << id_ << "\n";
		mutexForCout.unlock();
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
};
