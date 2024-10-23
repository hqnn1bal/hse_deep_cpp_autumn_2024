#pragma once
#include<stddef.h>

class Allocator {
private:
	char* memory;
	size_t maxSize;
	size_t offset;
public:
	Allocator() : memory(nullptr), maxSize(0), offset(0) {};
	void makeAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
	~Allocator() { if (this->memory != nullptr) delete[] this->memory; };
	friend class AllocatorTest;
};