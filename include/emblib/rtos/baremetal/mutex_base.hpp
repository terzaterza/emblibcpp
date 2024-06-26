#pragma once

#include "emblib/emblib.hpp"
#include "emblib/common/status.hpp"
#include "emblib/common/time.hpp"

namespace emblib::rtos::baremetal {

constexpr time::tick MUTEX_MAX_TICKS{time::millisec(1)};

class mutex_base {

protected:
    explicit mutex_base() = default;
    virtual ~mutex_base() = default;

public:
    /**
     * Baremetal stub implementation for RTOS lock
     * @note Always returns `status::OK`
    */
    status lock(time::tick ticks)
    {
        return status::OK;
    }

    /**
     * Baremetal stub implementation for RTOS unlock
     * @note Always returns `status::OK`
    */
    status unlock()
    {
        return status::OK;
    }
    
};

}