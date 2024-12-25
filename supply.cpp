#include "supply.h"
Supply::Supply(size_t factPriority, size_t id, Factory* ptr) :
	factoryPriority_(factPriority),
	id_(id),
	pointerToFactory_(ptr)
{}
size_t Supply::getId()
{
	return id_;
}
size_t Supply::getFactoryPriority()
{
	return Supply::factoryPriority_;
}
Factory* Supply::getPointerToFactory()
{
	return pointerToFactory_;
}
std::chrono::system_clock::time_point Supply::getTime()
{
	return time_;
}