#include "MiniginPCH.h"
#include "ServiceLocator.h"

std::shared_ptr<Input> ServiceLocator::p1InputService;
std::shared_ptr<Input> ServiceLocator::p2InputService;
std::shared_ptr<NullInput> ServiceLocator::defaultInput;