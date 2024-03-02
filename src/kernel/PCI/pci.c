#pragma once

void PCI_SelectRegister(uint8_t bus, uint8_t slot, uint8_t func, uint8_t reg) 
{ 
    uint32_t address = 
    ( ((uint32_t)1 << 31)
    | ((uint32_t)bus << 16)
    | ((uint32_t)slot << 11)
    | ((uint32_t)func << 8)
    | ((uint32_t)reg * 4)
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

void PCI_CheckDevice(uint8_t bus, uint8_t device, uint8_t fonction, uint16_t* deviceId, uint16_t* vendorId, uint16_t* classCode, uint8_t* headerType, uint16_t* subVendorId, uint16_t* subDeviceId) 
{
    *deviceId = (PCI_ReadRegister(bus, device, fonction, 0) >> 16);
    *vendorId = (PCI_ReadRegister(bus, device, fonction, 0) & 0xffff);

    *classCode = (PCI_ReadRegister(bus, device, fonction, 2) >> 16);
 
    // if(*vendorId == 0xffff)
    //     return;

    uint8_t _headerType = (PCI_ReadRegister(bus, device, fonction, 3) >> 16) & 0xff;

    *headerType = _headerType;

    if(_headerType == 2)
    {
        *subVendorId = (PCI_ReadRegister(bus, device, fonction, 0x10) >> 16);
        *subDeviceId = PCI_ReadRegister(bus, device, fonction, 0x10) & 0xffff;
    }
    else if(_headerType == 0)
    {
        *subDeviceId = (PCI_ReadRegister(bus, device, fonction, 0xb) >> 16);
        *subVendorId = PCI_ReadRegister(bus, device, fonction, 0xb) & 0xffff;
    }
    else 
    {
        *subVendorId = 0;
        *subDeviceId = 0;
    }
}

uint16_t PCI_ScanBuses()
{
    uint16_t deviceCount = 0;
    for(uint16_t i = 0; i < 256; i++)       // 256 buses
	{
		for(uint8_t j = 0; j < 32; j++)     // 32 devices per bus
		{
            for(uint8_t k = 0; k < 8; k++)  // 8 functions per device
            {
                uint8_t headerType = 0;
                uint16_t deviceId = 0, vendorId = 0, pciClass = 0, subVendorId = 0, subDeviceId = 0;
                PCI_CheckDevice(i, j, k, &deviceId, &vendorId, &pciClass, &headerType, &subVendorId, &subDeviceId);
                if(deviceId != 0xffff && vendorId != 0xffff)
                {
                    deviceCount++;
                    printf("%x:%x.%x | %x: %x:%x %x:%x\n", i, j, k, pciClass, vendorId, deviceId, subVendorId, subDeviceId);
                }
            }
		}
	}

    return deviceCount;
}