#pragma once

#include <functional>

#include <uscheduler/Task.hpp>
#include <uscheduler/scheduler/TimerScheduler.hpp>

namespace uscheduler
{

namespace interface
{
class IClock;
}

class Scheduler
{
public:
    Scheduler(interface::IClock& clock);

    void Run(std::vector<std::function<Task(interface::ITimerScheduler&)>> tasks);

private:
    scheduler::TimerScheduler m_timer_scheduler;
};

} // namespace uscheduler