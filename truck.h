#ifndef TRUCK_H
#define TRUCK_H
#include <random>
#include <mutex>
#include <chrono>
#define capacityOfGarage 10
class Supply;
extern std::mutex mutexForCout;
class Truck {
private:
	size_t id_ = 0;
	bool available_ = true;
	Supply* supplyToDeliver_ = nullptr;
	std::chrono::system_clock::time_point time_begin = std::chrono::system_clock::now();
	size_t allTime;
public:
	void setId(size_t id);
	size_t getId();
	void deliverSupply(Supply* supply);
	bool isAvailable();
	void setAvailable(bool available);
	void setSupply(Supply* supply);
	void run();
};
#endif
