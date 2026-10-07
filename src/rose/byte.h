#ifndef BYTE_H

#include <rose/tricks.h>

/*
 * Bytes and more helpers for ROSE!
 */
#define BYTE_H                                  ROSE_H_VERSION(1, 0, 0)

/**
 * Each odd byte always use bit 0 to signify '1', hence making bytes
 * who toggle bit 0 automatically odd!
 *
 * Note:
 * 
 * We're not supporting `struct` data types. Just... why would we?
 */

/**
 * Is a piece of data, which is not a `struct`, odd?
 */
#define is_odd(n)                               ((n) & 0x1)

/**
 * Is a piece of data, which is not a `struct`, even?
 */
#define is_even(n)                              (!is_odd(n))

/**
 * Aligns `n` by `x`, which is assumed to be a power of 2, downwards.
 */
#define align_down(n, x)                        ((n) & ~((x) - 1))

/**
 * Aligns `n` by `x`, which is assumed to be a power of 2, upwards.
 */
#define align_up(n, x)                          (((n) + (x - 1)) & ~((x) - 1))

#endif /* BYTE_H */