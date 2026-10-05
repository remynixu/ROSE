#ifndef BASIC_MEMORY_H

/**
 * Notes:
 *
 * We are going to fully comply with Intel x86 architecture terminology :<
 *
 * Also, we are going to use C-style declarations and such instead of UEFI's...
 *
 * ...unique style.
 */

#include <rose/tricks.h>

/**
 * Basic memory helpers for ROSE :<
 *
 * Without advanced features like malloc or free.
 */
#define BASIC_MEMORY_H                          ROSE_H_MAGIC__(1, 0, 0)

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *
 *                             STANDARD FUNCTIONS                            *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/**
 * Notes:
 *
 * If I may be so blunt, one of these functions are a lie. It's redirecting you
 * to another, more explicit and predictable function.
 */

/**
 * Set a whole section of bytes into `src`.
 */
void *memset(void *dest, unsigned char byte, size_t count);

/**
 * Copies memory to a destination, byte by byte, from left to right.
 */
void *memcpy_forward(void *__restrict dest, void *__restrict source, size_t count);

/**
 * Copies memory to a destination, byte by byte, from right to left.
 */
void *memcpy_backward(void *__restrict dest, void *__restrict source, size_t count);

/**
 * Copies a whole section of bytes to another location.
 * No checking done.
 */
void *memcpy(void *__restrict dest, void *__restrict source, size_t count)       \
        __asm__("memcpy_forward"); /* simply call the forward memcpy instead */

/**
 * Safely moves memory to another location, as if it used another buffer.
 */
void *memmove(void *dest, const void *source, size_t count);

#endif /* BASIC_MEMORY_H */