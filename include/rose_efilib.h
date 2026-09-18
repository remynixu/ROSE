#ifndef ROSE_EFILIB_H

/* 
 * Just a bunch of utility functions that are actually just wrappers for UEFI's
 * functions :>
 */
#define ROSE_EFILIB_H

#include <rose_types.h>
#include <efi.h>

/*
 * NOTES:
 * - There is no guarantee that each functions are fast, in fact, please expect
 *   the functions to be slow for the sake of catching errors.
 * - refi is now a claimed identifier which stands for: ROSE EFI
 */

/*
 * Expects an empty black tty-esque basic screen similar to VGA, except in UEFI.
 * Prints the `*str` argument onto said screen.
 * 
 * Returns the amount of characters printed successfully in the lower 30 bits:
 *   vv vvvv vvvv vvvv vvvv vvvv vvvv vvvv
 * 0000 0000 0000 0000 0000 0000 0000 0000
 * ^^
 * While the higher 2 bits are for errors:
 * - bit 30                                     = DEVICE ERROR
 * - bit 31                                     = TOO BIG
 * - bit 30 + 31                                = BAD ARGUMENT
 */
rose_bit32_t refi_print(EFI_SYSTEM_TABLE *efi_systab, char *str);

#endif /* ROSE_EFILIB_H */