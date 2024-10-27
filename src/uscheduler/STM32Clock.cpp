#include <uscheduler/STM32Clock.hpp>

#include <gpio.h>

namespace uscheduler
{
std::chrono::milliseconds uscheduler::STM32Clock::GetTick()
{
    return std::chrono::milliseconds{HAL_GetTick()};
}

}
