#pragma once
class Factory;
class Supply {
private:
	size_t id_;
	size_t factoryPriority_;
	Factory* pointerToFactory_;
public:
	Supply(size_t factPriority, size_t id, Factory* ptr) :
		factoryPriority_(factPriority),
		id_(id),
		pointerToFactory_(ptr)
	{}
	size_t getId()
	{
		return id_;
	}
	size_t getFactoryPriority()
	{
		return factoryPriority_;
	}
	Factory* getPointerToFactory()
	{
		return pointerToFactory_;
	}
};

