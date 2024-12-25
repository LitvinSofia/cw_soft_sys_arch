#ifndef SUPPLY_H
#define SUPPLY_H
#include <chrono>
#include "factory.h"
class Factory;
class Supply {
private:
	size_t id_;
	size_t factoryPriority_;
	Factory* pointerToFactory_;
	std::chrono::system_clock::time_point time_ = std::chrono::system_clock::now();
public:
	Supply(size_t factPriority, size_t id, Factory* ptr);
	size_t getId();
	size_t getFactoryPriority();
	Factory* getPointerToFactory();
	std::chrono::system_clock::time_point getTime();
};
#endif
