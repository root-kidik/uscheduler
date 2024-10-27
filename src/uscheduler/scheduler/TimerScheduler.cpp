#include <uscheduler/interface/IClock.hpp>
#include <uscheduler/scheduler/TimerScheduler.hpp>

namespace uscheduler::scheduler
{

TimerScheduler::TimerScheduler(interface::IClock& clock, std::set<std::coroutine_handle<>>& active_tasks) :
m_clock{clock},
m_active_tasks{active_tasks}
{
}

void TimerScheduler::Tick()
{
    for (auto it = m_delay_consumers.begin(); it != m_delay_consumers.end();)
    {
        if (m_clock.GetTick() > it->fire_tick)
        {
            m_active_tasks.insert(it->handle);
            it = m_delay_consumers.erase(it);
        }
        else
        {
            it++;
        }
    }
}

TimerScheduler::Awaiter TimerScheduler::Delay(std::chrono::milliseconds delay)
{
    return Awaiter{*this, m_clock, delay};
}

void TimerScheduler::AddConsumer(Consumer consumer)
{
    m_delay_consumers.push_back(consumer);
    m_active_tasks.erase(consumer.handle);
}

} // namespace uscheduler::scheduler
