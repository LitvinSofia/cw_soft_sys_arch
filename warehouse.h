#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include <limits>
#include <mutex>
#include "supply.h"
#undef max
class Supply;
extern std::mutex mutexForCout;
constexpr size_t capacityOfWarehouse = 15;
constexpr size_t max_priority = std::numeric_limits<size_t>::max();
constexpr size_t max_id = std::numeric_limits<size_t>::max();
class Warehouse {
private:
	size_t size_ = 0;
	Supply* warehouse_[capacityOfWarehouse] = {};
	Supply** pointerToNextInserted;
	std::mutex warehouseMutex_;
public:
	Warehouse();
	void mutexLock();
	void mutexUnlock();
	Supply* chooseSupply();
	Supply** findPlaceForSupply();
	Supply** getPtrToNextInserted();
	bool isEmpty();
	void printWarehouse();
	void placeSupply(Supply** place, Supply* newSupply);
	void rejectSupply(Supply** placeToReject);
};
#endif
