#pragma once

#include "emblib/emblib.hpp"
#include "emblib/drivers/serial_device.hpp"

namespace emblib::drivers {

struct uart_config {
    uart::baud_rate baud_rate;
    uart::data_bits data_bits;
    uart::stop_bits stop_bits;
    uart::parity_bit parity;
};

class uart : private serial_device {

public:
    enum class baud_rate : uint32_t {
        BR9600      = 9600,
        BR115200    = 115200
    };

    enum class data_bits : uint8_t {
        DB7 = 7,
        DB8 = 8,
        DB9 = 9
    };

    enum class stop_bits : uint8_t {
        SB1 = 1,
        SB2 = 2
    };

    enum class parity_bit {
        NONE,
        EVEN,
        ODD
    };

public:
    explicit uart() = default;
    ~uart() override = default;

    /**
     * Send an array of bytes
     * @note This function acquires the inhertied serial_device::mutex
     * @note Exits once the write operation is complete
    */
    status send(const uint8_t* data, const size_t size)
    {
        return serial_device::write(data, size);
    }

    /**
     * Wait to receive `size` bytes
     * @note This function acquires the inhertied serial_device::mutex
     * @note Exits once the receive operation is complete
    */
    status receive(uint8_t* buffer, const size_t size)
    {
        return serial_device::read(buffer, size);
    }

};

}