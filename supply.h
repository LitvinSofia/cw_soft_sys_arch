#pragma once
class Supply {
private:
	size_t id_;
	size_t factoryPriority_;
public:
	Supply(size_t factPriority, size_t id) :
		factoryPriority_(factPriority),
		id_(id)
	{}
	size_t getId()
	{
		return id_;
	}
	size_t getFactoryPriority()
	{
		return factoryPriority_;
	}
};

