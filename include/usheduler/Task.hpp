#pragma once

#include <cassert>
#include <coroutine>
#include <initializer_list>

#include <usheduler/LinearStackAllocator.hpp>

namespace usheduler
{

usheduler::LinearStackAllocator<512> g_coroutine_linear_stack_allocator;

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

        void* operator new(std::size_t size)
        {
            return g_coroutine_linear_stack_allocator.Allocate(size);
        }

        void operator delete(void* ptr)
        {
        }
    };

    Task(std::coroutine_handle<promise_type> handle) : m_handle{handle}
    {
    }

    void resume() const
    {
        m_handle.resume();
    }

private:
    std::coroutine_handle<promise_type> m_handle;
};


} // namespace usheduler