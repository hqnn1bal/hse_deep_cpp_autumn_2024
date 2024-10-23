#pragma once
#include "allocator.h"
#include<iostream>
#include<cstdlib>

void Allocator::makeAllocator(size_t maxSize)
{
	if (this->memory != nullptr) delete[] this->memory;
	this->memory = new char[int(maxSize)]();
	this->maxSize = maxSize;
	this->offset = 0;
}

char* Allocator::alloc(size_t size)
{
	if (this->memory == nullptr || this->offset + size > this->maxSize) return nullptr;

	char* ptr = this->memory + this->offset;
	offset += size;
	return ptr;
}

void Allocator::reset()
{
	this->offset = 0;
}




