#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include <stdint.h>

// Peripheral Controller
struct peripheral_con
{
    uint8_t  selector; // Which device to communicate with
    uint8_t  request;  // Whether or not you are requesting info or to send info
    uint32_t data;     // Data I/O
};


// Peripheral Device
struct peripheral_dev
{
    uint8_t  enable; // Wheter or not the device is currently being used
    uint32_t data;   // Data I/O
    uint8_t  irq;    // IRQ line
};

// Peripheral PHI
struct peripheral_phi
{
    uint32_t phi_version;  // Version of PHI
    uint32_t hw_version;   // Version of hardware
    char     name[32];     // Name of device
    uint32_t type;         // Type of device
    uint32_t subtype;      // Subtype of device
    uint32_t manufacturer; // Device manufacturer
};

// Initialize peripheral controller
int init_peripherals(struct cpu *bacpu);

#endif // PERIPHERALS_H
