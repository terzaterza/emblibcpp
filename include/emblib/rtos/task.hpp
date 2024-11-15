#pragma once

#include "emblib/emblib.hpp"
#include "emblib/common/time.hpp"

#if EMBLIB_RTOS_USE_FREERTOS
    #include "./freertos/task.hpp"
#else
    
#endif

namespace emblib::rtos {

/**
 * Statically allocated stack
 */
template <size_t SIZE_IN_BYTES>
using task_stack_t = uint8_t[SIZE_IN_BYTES];

/**
 * OOP style API for a thread
 */
class task {
public:
#if EMBLIB_RTOS_USE_FREERTOS
    using native_task_t = freertos::task;
#else
    #error "Thread implementation missing"
#endif

public:
    template <size_t STACK_SIZE_BYTES>
    explicit task(
        const char* name,
        size_t priority,
        task_stack_t<STACK_SIZE_BYTES>& stack
    );

    /* Copy operations not allowed */
    task(const task&) = delete;
    task& operator=(const task&) = delete;

    /* Move operations not allowed */
    task(task&&) = delete;
    task& operator=(task&&) = delete;

    /**
     * Start the scheduler
     */
    static inline void start_tasks() noexcept;

    /**
     * Put the currently running thread to sleep
     * @note Static since can be called even baremetal and implemented using HAL
     */
    static inline void sleep(time::millisec duration);

#if EMBLIB_RTOS_SUPPORT_NOTIFICATIONS
    /**
     * Wait for this task to get notified
     * @note Lightweight version of a semaphore which can be
     * taken only by this task
     */
    bool wait_notification(time::millisec timeout = time::MAX_MILLIS) noexcept;

    /**
     * Increment this task's notification value
     * @note Unblocks this task if is currently waiting on notification
     */
    void notify() noexcept;
#endif

    /**
     * Get reference to the underlying implementation object
     */
    native_task_t& get_native_task() noexcept
    {
        return m_native_task;
    }

private:
    /**
     * Task executable
     */
    virtual void run() noexcept = 0;

private:
    native_task_t m_native_task;

};

#if EMBLIB_RTOS_USE_FREERTOS

template <size_t STACK_SIZE_BYTES>
inline task::task(const char *name, size_t priority, task_stack_t<STACK_SIZE_BYTES> &stack) :
    m_native_task([this] {this->run();}, name, priority, (freertos::task_stack_t<sizeof(stack) / sizeof(freertos::task_stack_t<1>)>&)stack)
{
}

inline void task::start_tasks() noexcept
{
    freertos::start_scheduler();
}

inline void task::sleep(time::millisec duration)
{
    freertos::delay(duration);
}

#if EMBLIB_RTOS_SUPPORT_NOTIFICATIONS
inline bool task::wait_notification(time::millisec timeout) noexcept
{
    return freertos::notify_take(false, timeout);
}

inline void task::notify() noexcept
{
    m_native_task.notify();
}
#endif

#else
    #error "Thread implementation missing"
#endif

}

#if EMBLIB_UNNEST_NAMESPACES
namespace emblib {
    using namespace rtos;
}
#endif