/**
 * Author: Simon Lindholm
 * Date: 2015-09-12
 * License: CC0
 * Source: me
 * Description: When you need to dynamically allocate many objects and don't care about freeing them.
 * "new X" otherwise has an overhead of something like 0.05us + 16 bytes per allocation.
 * Do not use unless you are \_absolutely\_ sure what you are doing.
 * Status: tested
 */
#pragma once

// this code creates a warning for not defining delete(void*, size_t),	// exclude-line
// ...but does not compile with it										// exclude-line
#pragma GCC diagnostic push												// exclude-line
#pragma GCC diagnostic ignored "-Wsized-deallocation"					// exclude-line

// Either globally or in a single class:
static char buf[450 << 20];
void* operator new(size_t s) {
	static size_t i = sizeof buf;
	assert(s < i);
	return (void*)&buf[i -= s]; }
void operator delete(void*) {}

#pragma GCC diagnostic pop												// exclude-line
