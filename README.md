# CppRingContainer

CppRingContainer

This project is for work on an STL-Compatible ringbuffer-type container.  This is also known as a circular buffer.

The basic premise is that there is a shared maximum size of this container, and if a push() request is made
after reaching that limit, it will overwrite the oldest entry.

The major difference between this and something like deque is that 
memory is contiguous, allocated at construction, and accessible through random access.
