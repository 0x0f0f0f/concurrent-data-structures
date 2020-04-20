# Concurrent Data Structures
A small C library containing mostly utility functions (a logger) and generic
data structures, with concurrent wrappers for linked list and fixed size
static buffers that rely on pthread for mutexes and condition variables.
All data structures except hash table keep pointers to (void*), so memory
management must be done externally.

Uses clang and builds as a static library by default. Used for
the operating systems course @ UniPi.