#ifndef ROSE_EFI_H

/*
 * This header is primarily for loading the rOSe kernel using the UEFI
 * specifications for its bootloader.
 *
 * All of the header's code is derived from this link:
 * - https://uefi.org/specs/UEFI/2.10
 */
#define ROSE_EFI_H

/* A little help from the standard library won't hurt right? :> */
#include <stdint.h>

/*
 * To make sure the compiler doesn't do any unexpected magic... please add this
 * before the name of every function :<
 */
#define EFI_API                                 __attribute((ms_abi))

/*
 * Just some fancy touch-ups UEFI loves <3
 * (they mean absolutely nothing xD)
 */

#define IN
#define OUT

/* ========================================================================== *
 * UEFI Data Types:
 */

/* UEFI intentionally made EFI_HANDLE a black box so... */
typedef void*                                   EFI_HANDLE;

/* UEFI also made events a black box :< */
typedef void*                                   EFI_EVENT;

/* UEFI has... quite the error code system ._. */
typedef uint64_t                                EFI_STATUS;

/* My boolean for UEFI :> */
typedef uint8_t                                 efi_bool;

/* ========================================================================== *
 * UEFI Error codes:
 */

/*
 * According to UEFI specifications, the high bit is 1 if something went wrong
 * and 0 if it's a success or just a warning. It goes something like this:
 *
 * High bit                                              Actual error code
 * v                                                     vvvv vvvv vvvv vvvv
 * 0000 0000 0000 0000 ... [skipping 48 more zeroes] ... 0000 0000 0000 0000
 *
 * I don't know why it has a lot of zeroes but it's not my problem so...
 */

#define EFI_SUCCESS                             ((EFI_STATUS)0)

#define ERRORCODE_BITMASK__                     ((EFI_STATUS)1 << 63)
#define ERRORCODE__(ec__)                                                     \
        ((EFI_STATUS)(ec__) | ERRORCODE_BITMASK__)

#define EFI_NOT_FOUND                           ERRORCODE__(14)

/* ========================================================================== *
 * UEFI Functions:
 */

/*
 * Since these data are already defined by UEFI, it's all just mostly just
 * copy-pasted code below...
 */

typedef EFI_STATUS (EFI_API *EFI_INPUT_RESET)(
     IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL         *This,
     IN efi_bool                                ExtendedVerification
);

typedef EFI_STATUS (EFI_API *EFI_INPUT_READ_KEY)(
     IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL         *This,
    OUT EFI_INPUT_KEY                          *Key
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_RESET)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN efi_bool                                ExtendedVerification
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_STRING)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN uint16_t                               *String
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_TEST_STRING)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN uint16_t                               *String
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_QUERY_MODE)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN uint64_t                                ModeNumber,
    OUT uint64_t                               *Columns,
    OUT uint64_t                               *Rows
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_SET_MODE)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN uint64_t                                ModeNumber
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_SET_ATTRIBUTE)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN uint64_t                                Attribute
);

/* ========================================================================== *
 * UEFI Data Structures:
 */

typedef struct{
        uint16_t                                ScanCode;
        uint16_t                                UnicodeChar;
}EFI_INPUT_KEY;

typedef struct{
        uint64_t                                Signature;
        uint32_t                                Revision;
        uint32_t                                HeaderSize;
        uint32_t                                CRC32;
        uint32_t                                Reserved;
}EFI_TABLE_HEADER;

typedef struct{
        EFI_INPUT_RESET                         Reset;
        EFI_INPUT_READ_KEY                      ReadKeyStroke;
        EFI_EVENT                               WaitForKey;
}EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef struct{
        EFI_TEXT_RESET                          Reset;
        EFI_TEXT_STRING                         OutputString;
        EFI_TEXT_TEST_STRING                    TestString;
        EFI_TEXT_QUERY_MODE                     QueryMode;
        EFI_TEXT_SET_MODE                       SetMode;
        EFI_TEXT_SET_ATTRIBUTE                  SetAttribute;
        EFI_TEXT_CLEAR_SCREEN                   ClearScreen;
        EFI_TEXT_SET_CURSOR_POSITION            SetCursorPosition;
        EFI_TEXT_ENABLE_CURSOR                  EnableCursor;
        SIMPLE_TEXT_OUTPUT_MODE                 *Mode;
}EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL

typedef struct{
        EFI_TABLE_HEADER                        Hdr;
        uint16_t                               *FirmwareVendor;
        uint32_t                                FirmwareRevision;
        EFI_HANDLE                              ConsoleInHandle;
        EFI_SIMPLE_TEXT_INPUT_PROTOCOL         *ConIn;
        EFI_HANDLE                              ConsoleOutHandle;
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *ConOut;
        EFI_HANDLE                              StandardErrorHandle;
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *StdErr;
        EFI_RUNTIME_SERVICES                   *RuntimeServices;
        EFI_BOOT_SERVICES                      *BootServices;
        uint64_t                                NumberOfTableEntries;
        EFI_CONFIGURATION_TABLE                *ConfigurationTable;
}EFI_SYSTEM_TABLE;

/*
 * I see a little sillhouetto of a man,
 * Scaramouche! Scaramouche! Will you do the Fandango?
 *
 * Thunderbolt and lightning, very very frightening me!
 */

#endif /* ROSE_EFI_H */