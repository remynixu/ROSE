#ifndef EFI_UTILS_H

/**
 * Not supposed to work in hosted environments.
 */
#if __STDC_HOSTED__ == 0

#include <rose/tricks.h>

/**
 * A *thin* wrapper around efi.h for ROSE :<
 */
#define EFI_UTILS_H                             ROSE_H_MAGIC__(1, 0, 0)

#include <efi/efi.h>

extern EFI_STATUS global_efi_status;

/* Simple EFI text output to screen. */
bool efi_output(
        EFI_SYSTEM_TABLE                       *ctx,
        const uint16_t                         *utf16
);

/* Basic putchar for EFI. */
bool efi_printc(
        EFI_SYSTEM_TABLE                       *ctx,
        const uint16_t                          c
);

/* Basic puts for EFI. */
bool efi_prints(
        EFI_SYSTEM_TABLE                       *ctx,
        const char                             *str
);

/* Simple EFI keyboard input. */
bool efi_input(
        EFI_SYSTEM_TABLE                       *ctx,
        EFI_INPUT_KEY                           key             [static 1]
);

/* Simple EFI keyboard input (Less user-handling needed). */
bool efi_keystroke(
        EFI_SYSTEM_TABLE                       *ctx,
        uint16_t                                scancode        [static 1],
        uint16_t                                unicode         [static 1]
);

#endif /* __STDC_HOSTED__ */

#endif /* EFI_UTILS_H */