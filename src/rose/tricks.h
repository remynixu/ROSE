#ifndef TRICKS_H

/**
 * Tricking (or cooperating with) the compiler :>
 *
 * Also more!
 */
#define TRICKS_H                                0x524f5345 /* "ROSE" */

/**
 * Also acts as a little sanity-check for ROSE files :D
 */
#if (__SIZEOF_POINTER__ != 8) || (_WIN64 != 1) || (__x86_64__ != 1)
#error "ROSE strictly requires a 64-bit architecture!"
#endif /* architecture checking */

/**
 * Freestanding libraries! :D
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

/**
 * This is for "inline" versioning... and signature of course.
 */
#define ROSE_H_MAGIC__(mjr, mnr, b)                                           \
        ((uint64_t)TRICKS_H << 32) | ((mjr) << 16) | ((mnr) << 8) | (b)

/**
 * Note:
 *
 * Please know what you're doing before using any of these...
 */

/**
 * Prevents the compiler from doing *any* form of optimization to block of code.
 */
#define NO_OPTIMIZE__                                                         \
        __asm__ __volatile__ ("" ::: "memory")

/**
 * Used for unused variables and stop compiler from complaining.
 */
#define UNUSED__(x)                             (void)(x)

#endif /* TRICKS_H */