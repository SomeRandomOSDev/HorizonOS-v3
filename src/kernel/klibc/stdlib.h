#pragma once

extern void halt();

void abort();

// void* mapLinearAddressToAvailableMemory(uint32_t address);
// uint32_t mapAvailableMemoryToLinearAddress(void* ptr);
// bool isPtrAvailable(void* ptr);

// uint32_t totalBlocks;
// uint32_t blockSize;
// uint32_t bitmapSize;
// uint32_t freeMemAddress;

// void initMemAlloc(uint16_t _blockSize);
// void setBlockFree(uint32_t blockNumber, bool isFree);
// void setBlockAsFirstBlock(uint32_t blockNumber, bool isFirstBlock);
// bool isBlockFree(uint32_t blockNumber);
// bool isBlockAFirstBlock(uint32_t blockNumber);
// void printMemState(uint32_t block);
// void* malloc(size_t size);
// void* calloc(size_t nitems, size_t size);
// void free(void* ptr);
// void* realloc(void* ptr, size_t size);