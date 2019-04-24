#pragma once
#include "InputManager.h"

class ServiceLocator
{
public:
	static void Init()
	{
		p1InputService = defaultInput;
		p2InputService = defaultInput;
	}
	static void RegisterInputP1Service(std::shared_ptr<Input> service) { p1InputService = (service == nullptr) ? defaultInput : service; }
	static void RegisterInputP2Service(std::shared_ptr<Input> service) { p2InputService = (service == nullptr) ? defaultInput : service; }
	static std::shared_ptr<Input>& GetInputP1() { return p1InputService; }
	static std::shared_ptr<Input>& GetInputP2() { return p2InputService; }
	static std::shared_ptr<Input> GetDefault() { return defaultInput; }

private:
	static std::shared_ptr<Input> p1InputService;
	static std::shared_ptr<Input> p2InputService;
	static std::shared_ptr<NullInput> defaultInput;
};

