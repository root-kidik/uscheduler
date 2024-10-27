#pragma once

#include <chrono>

#include <uscheduler/interface/IClock.hpp>

namespace uscheduler
{

class STM32Clock final : public interface::IClock
{
public:
    std::chrono::milliseconds GetTick() override;
};

} // namespace uscheduler