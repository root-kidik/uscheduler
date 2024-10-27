#include <uscheduler/Scheduler.hpp>

namespace uscheduler
{

Scheduler::Scheduler(interface::IClock& clock) : m_timer_scheduler{clock}
{
}

void Scheduler::Run(std::vector<std::function<Task(interface::ITimerScheduler&)>> tasks)
{
    for (auto& task : tasks)
        task(m_timer_scheduler).resume();

    for (;;)
    {
        m_timer_scheduler.Tick();
    }
}

} // namespace uscheduler
