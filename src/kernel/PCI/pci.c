#pragma once

void PCI_SelectRegister(uint8_t bus, uint8_t slot, uint8_t func, uint8_t reg) 
{ 
    uint32_t address = 
    ( PCI_ENABLE_BIT    
    | ((uint32_t)bus << 16)
    | ((uint32_t)(slot & 0b11111) << 11)
    | (((uint32_t)func & 0b111) << 8)
    | (((uint32_t)reg * 4) & 0xff)
    );
 
    outd(PCI_CONFIG_ADDRESS, address);
}

uint32_t PCI_ReadSelectedRegister() 
{ 
    return ind(PCI_CONFIG_DATA);
}

uint32_t PCI_ReadRegister(uint8_t bus, uint8_t slot, uint8_t func, uint8_t reg) 
{ 
    PCI_SelectRegister(bus, slot, func, reg);
    return PCI_ReadSelectedRegister();
}

void PCI_CheckDevice(
    uint8_t bus, uint8_t device, uint8_t function, 
    struct PCI_Common* commonHeader, uint16_t* subVendorID, uint16_t* subDeviceID) 
{
    *(uint32_t*)commonHeader =          PCI_ReadRegister(bus, device, function, 0);
    *((uint32_t*)commonHeader + 1) =    PCI_ReadRegister(bus, device, function, 1);
    *((uint32_t*)commonHeader + 2) =    PCI_ReadRegister(bus, device, function, 2);
    *((uint32_t*)commonHeader + 3) =    PCI_ReadRegister(bus, device, function, 3);

    if((commonHeader->headerType & 0b111111) == 2)
    {
        if (subVendorID)
            *subVendorID = (PCI_ReadRegister(bus, device, function, 0x10) >> 16);
        if (subDeviceID)
            *subDeviceID = PCI_ReadRegister(bus, device, function, 0x10) & 0xffff;
    }
    else if((commonHeader->headerType & 0b111111) == 0)
    {
        if (subVendorID)
            *subVendorID = PCI_ReadRegister(bus, device, function, 0xb) & 0xffff;
        if (subDeviceID)
            *subDeviceID = (PCI_ReadRegister(bus, device, function, 0xb) >> 16);
    }
    else 
    {
        if (subVendorID)
            *subVendorID = 0;
        if (subDeviceID)
            *subDeviceID = 0;
    }
}

void PCI_ScanBus(uint8_t bus)
{    
    bool anyDevices = false;
    for(uint8_t j = 0; j < 32; j++)     // 32 devices per bus
    {
        bool multipleFuncDevice;
        uint8_t k = 0;
        do
        {
            uint16_t subVendorID = 0, subDeviceID = 0;
            struct PCI_Common commonHeader;
            PCI_CheckDevice(bus, j, k, &commonHeader, &subVendorID, &subDeviceID);
            multipleFuncDevice = commonHeader.headerType >> 7;
            if(commonHeader.deviceID != 0xffff && commonHeader.vendorID != 0xffff)
            {
                if(!anyDevices)
                {
                    printf("Bus %u:\n", bus);
                    anyDevices = true;
                }
                char* classStr = PCI_class_str[commonHeader.classCode];
                if(!classStr)
                    classStr = "Reserved";
                printf("%x.%x \t %d \t | %x \t %x %x:%x %x:%x | %s\n", 
                j, k, commonHeader.headerType & 0b1111111, commonHeader.classCode, commonHeader.subClass, commonHeader.vendorID, commonHeader.deviceID, subVendorID, subDeviceID, classStr);
            }
            else
                multipleFuncDevice = false;
            k++;
        } while(k < 8 && multipleFuncDevice);         // 8 functions per device
    }
}

void PCI_ScanBuses()
{
    // printf("Device.Func Header | Class SubClass VendID:DevID SubSysVendID:SubSysDevID\n");
    
    struct PCI_Common commonHeader;
    PCI_CheckDevice(0, 0, 0, &commonHeader, NULL, NULL);

    if (commonHeader.headerType >> 7) // Single PCI host controller
        PCI_ScanBus(0);
    else        // Multiple PCI host controllers
    {
        for (uint8_t i = 0; i < 8; i++) 
        {
            PCI_CheckDevice(0, 0, i, &commonHeader, NULL, NULL);
            if (commonHeader.vendorID == 0xffff) break;
            PCI_ScanBus(i);
        }
    }
}