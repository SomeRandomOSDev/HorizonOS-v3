#pragma once

#define PCI_CONFIG_ADDRESS  0xcf8
#define PCI_CONFIG_DATA     0xcfc
#define PCI_ENABLE_BIT      ((uint32_t)1 << 31)       

struct PCI_Common
{
// Register 0
    uint16_t vendorID;
    uint16_t deviceID;

// Register 1
    uint16_t command;
    uint16_t status;

// Register 2
    uint8_t revisionID;
    uint8_t progIF;
    uint8_t subClass;
    uint8_t classCode;

// Register 3
    uint8_t cacheLineSize;
    uint8_t latencyTimer;

    // struct 
    // {
    //     uint8_t MF      : 1;
    //     uint8_t type    : 7;
    // } headerType;// __attribute__((packed));
    uint8_t headerType;

    uint8_t BIST;
};

char* PCI_class_str[256] = 
{
    "Unclassified", "Mass Storage Controller", "Network Controller", "Display Controller", "Multimedia Controller", "Memory Controller", "Bridge", "Simple Communication Controller", "Base System Peripheral", "Input Device Controller", "Docking Station", "Processor", "Serial Bus Controller", "Wireless Controller", "Intelligent Controller", "Satellite Communication Controller",
    "Encryption Controller", "Signal Processing Controller", "Processing Accelerator", "Non-Essential Instrumentation", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    "Co-Processor", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "Unassigned Class"
};