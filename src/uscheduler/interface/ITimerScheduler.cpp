#include <uscheduler/interface/IClock.hpp>
#include <uscheduler/interface/ITimerScheduler.hpp>

namespace uscheduler::interface
{

ITimerScheduler::Awaiter::Awaiter(ITimerScheduler& scheduler, IClock& clock, std::chrono::milliseconds delay) :
m_scheduler{scheduler},
m_clock{clock},
m_delay{delay}
{
}

bool ITimerScheduler::Awaiter::await_ready()
{
    return false;
}

void ITimerScheduler::Awaiter::await_suspend(std::coroutine_handle<> caller_handle)
{
    m_scheduler.AddConsumer({caller_handle, m_clock.GetTick() + m_delay});
}

void ITimerScheduler::Awaiter::await_resume()
{
}

} // namespace uscheduler::interface