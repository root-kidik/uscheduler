#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>

namespace usheduler
{

template <std::size_t Size>
class LinearStackAllocator
{
public:
    LinearStackAllocator();

    void* Allocate(std::size_t size);
    void  Deallocate(void* ptr);

private:
    std::array<std::byte, Size> m_buffer;
    std::size_t                 m_allocated_size;
};

} // namespace usheduler

#include <usheduler/LinearStackAllocator.inl>