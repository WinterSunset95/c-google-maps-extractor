#include "headers/helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t writeFunction(void *ptr, size_t size, size_t nmemb, void *userData) {
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userData;
	char *tstptr = realloc(mem->memory, mem->size + realsize + 1);
	if (!ptr) {
		printf("Out of memory!!\n");
		return 0;
	}

	mem->memory = tstptr;
	memcpy(&(mem->memory[mem->size]), ptr, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}
