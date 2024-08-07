#pragma once

#include "emblib/emblib.hpp"

#if EMBLIB_RTOS_USE_FREERTOS
#include "emblib/rtos/freertos/mutex.hpp"
#elif EMBLIB_RTOS_USE_THREADX
#include "emblib/rtos/threadx/mutex.hpp"
#else
#include "emblib/rtos/baremetal/mutex.hpp"
#endif

namespace emblib::rtos {

#if EMBLIB_RTOS_USE_FREERTOS
using freertos::mutex;
#elif EMBLIB_RTOS_USE_THREADX
using threadx::mutex;
#else
using namespace baremetal;
#endif

}