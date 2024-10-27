#pragma once

#include <functional>
#include <set>

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
    Scheduler(interface::IClock& clock, std::vector<std::function<Task(interface::ITimerScheduler&)>> tasks);

    void Run();

private:
    std::vector<Task>                 m_tasks;
    std::set<std::coroutine_handle<>> m_active_tasks;

    scheduler::TimerScheduler m_timer_scheduler;
};

} // namespace uscheduler