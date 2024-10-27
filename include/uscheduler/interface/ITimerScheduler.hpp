#pragma once

#include <chrono>
#include <coroutine>

namespace uscheduler::interface
{

class IClock;

class ITimerScheduler
{
public:
    virtual ~ITimerScheduler() = default;

    struct Awaiter
    {
        Awaiter(ITimerScheduler& scheduler, IClock& clock, std::chrono::milliseconds delay);
        bool await_ready();
        void await_suspend(std::coroutine_handle<> caller_handle);
        void await_resume();

    private:
        ITimerScheduler&          m_scheduler;
        IClock&                   m_clock;
        std::chrono::milliseconds m_delay;
    };

    virtual Awaiter Delay(std::chrono::milliseconds delay) = 0;

protected:
    struct Consumer
    {
        std::coroutine_handle<>   handle;
        std::chrono::milliseconds fire_tick;
    };

    virtual void    AddConsumer(Consumer consumer)         = 0;
};

} // namespace uscheduler::interface
