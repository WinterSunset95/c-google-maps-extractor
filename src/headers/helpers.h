#ifndef HELPERS_H
#define HELPERS_H

#include <stddef.h>

struct MemoryStruct {
	char *memory;
	size_t size;
};

size_t writeFunction(void *ptr, size_t size, size_t nmemb, void *userData);

#endif
