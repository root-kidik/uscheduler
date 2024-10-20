namespace usheduler
{

template <std::size_t Size>
LinearStackAllocator<Size>::LinearStackAllocator() : m_buffer{}, m_allocated_size{}
{
}

template <std::size_t Size>
void* LinearStackAllocator<Size>::Allocate(std::size_t size)
{
    assert(m_allocated_size + size <= Size && "Out of memory in the LinearStackAllocator!");

    m_allocated_size += size;
    return &m_buffer[m_allocated_size - size];
}

template <std::size_t Size>
void LinearStackAllocator<Size>::Deallocate(void* ptr)
{
    m_allocated_size = 0;
}

}