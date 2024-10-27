#include <uscheduler/Scheduler.hpp>

namespace uscheduler
{

Scheduler::Scheduler(interface::IClock& clock, std::vector<std::function<Task(interface::ITimerScheduler&)>> tasks) :
m_timer_scheduler{clock, m_active_tasks}
{
    for (auto& task : tasks)
        m_tasks.push_back(task(m_timer_scheduler));

    for (auto& task : m_tasks)
        m_active_tasks.insert(task.handle);
}

void Scheduler::Run()
{
    for (;;)
    {
        m_timer_scheduler.Tick();

        for (auto& task : m_active_tasks)
            task.resume();
    }
}

} // namespace uscheduler
