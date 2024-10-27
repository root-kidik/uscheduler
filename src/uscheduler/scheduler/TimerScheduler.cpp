#include <uscheduler/scheduler/TimerScheduler.hpp>

#include <uscheduler/interface/IClock.hpp>

namespace uscheduler::scheduler
{

TimerScheduler::TimerScheduler(interface::IClock& clock) : m_clock{clock}
{
}

void TimerScheduler::Tick()
{
    for (auto it = m_delay_consumers.begin(); it != m_delay_consumers.end();)
    {
        if (m_clock.GetTick() > it->fire_tick)
        {
            it->handle.resume();
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
}

} // namespace uscheduler::scheduler
