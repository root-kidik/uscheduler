#pragma once

#include <coroutine>

namespace uscheduler
{

struct Task
{
    struct promise_type
    {
        auto get_return_object()
        {
            return std::coroutine_handle<promise_type>::from_promise(*this);
        }

        auto initial_suspend()
        {
            return std::suspend_always();
        }

        auto final_suspend() noexcept
        {
            return std::suspend_always();
        }

        void unhandled_exception()
        {
        }
    };

    Task(std::coroutine_handle<promise_type> handle) : handle{handle}
    {
    }

    std::coroutine_handle<promise_type> handle;
};


} // namespace uscheduler