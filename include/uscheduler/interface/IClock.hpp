#pragma once

#include <chrono>

namespace uscheduler::interface
{

class IClock
{
public:
    virtual ~IClock() = default;

    virtual std::chrono::milliseconds GetTick() = 0;
};

} // namespace uscheduler::interface
