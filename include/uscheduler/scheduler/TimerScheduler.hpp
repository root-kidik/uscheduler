#pragma once

#include <list>

#include <uscheduler/interface/ITimerScheduler.hpp>

namespace uscheduler::interface
{
class IClock;
}

namespace uscheduler::scheduler
{

class TimerScheduler final : public interface::ITimerScheduler
{
public:
    TimerScheduler(interface::IClock& clock);

    void Tick();

    Awaiter Delay(std::chrono::milliseconds delay);

private:
    void AddConsumer(Consumer consumer) override;

    std::list<Consumer> m_delay_consumers;

    interface::IClock& m_clock;
};

} // namespace uscheduler::scheduler