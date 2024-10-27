#include <gpio.h>

#include <uscheduler/STM32Clock.hpp>

namespace uscheduler
{
std::chrono::milliseconds uscheduler::STM32Clock::GetTick()
{
    return std::chrono::milliseconds{HAL_GetTick()};
}

} // namespace uscheduler
