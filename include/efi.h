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
#define OPTIONAL

/* ========================================================================== *
 * Special UEFI Data Types:
 */

/* UEFI intentionally made EFI_HANDLE a black box so... */
typedef void*                                   EFI_HANDLE;

/* UEFI also made events a black box :< */
typedef void*                                   EFI_EVENT;

/* A boolean for UEFI :> */
typedef uint8_t                                 efi_bool;

/* UEFI uses 16-bit characters... */
typedef uint16_t                                uchar16_t;

/* -------------------------------------------------------------------------- *
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

/* UEFI has... quite the error code system ._. */
typedef uintptr_t                               EFI_STATUS;

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

/*
 * The entry point of an EFI binary.
 *
 * EFI_HANDLE is an opaque pointer we're not supposd to tamper with.
 * EFI_SYSTEM_TABLE is where the useful functions and data are!
 */
typedef EFI_STATUS (EFI_API *EFI_IMAGE_ENTRY_POINT)(
     IN EFI_HANDLE                              ImageHandle,
     IN EFI_SYSTEM_TABLE                       *SystemTable
);

/* -------------------------------------------------------------------------- *
 * EFI_SYSTEM_TABLE contents:
 */

#define EFI_SYSTEM_TABLE_SIGNATURE              0x5453595320494249
#define EFI_2_100_SYSTEM_TABLE_REVISION         ((2<<16) | (100))
#define EFI_2_90_SYSTEM_TABLE_REVISION          ((2<<16) | (90))
#define EFI_2_80_SYSTEM_TABLE_REVISION          ((2<<16) | (80))
#define EFI_2_70_SYSTEM_TABLE_REVISION          ((2<<16) | (70))
#define EFI_2_60_SYSTEM_TABLE_REVISION          ((2<<16) | (60))
#define EFI_2_50_SYSTEM_TABLE_REVISION          ((2<<16) | (50))
#define EFI_2_40_SYSTEM_TABLE_REVISION          ((2<<16) | (40))
#define EFI_2_31_SYSTEM_TABLE_REVISION          ((2<<16) | (31))
#define EFI_2_30_SYSTEM_TABLE_REVISION          ((2<<16) | (30))
#define EFI_2_20_SYSTEM_TABLE_REVISION          ((2<<16) | (20))
#define EFI_2_10_SYSTEM_TABLE_REVISION          ((2<<16) | (10))
#define EFI_2_00_SYSTEM_TABLE_REVISION          ((2<<16) | (00))
#define EFI_1_10_SYSTEM_TABLE_REVISION          ((1<<16) | (10))
#define EFI_1_02_SYSTEM_TABLE_REVISION          ((1<<16) | (02))
#define EFI_SPECIFICATION_VERSION               EFI_SYSTEM_TABLE_REVISION
#define EFI_SYSTEM_TABLE_REVISION               EFI_2_100_SYSTEM_TABLE_REVISION

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
        uintptr_t                               NumberOfTableEntries;
        EFI_CONFIGURATION_TABLE                *ConfigurationTable;
}EFI_SYSTEM_TABLE;

typedef struct{
        uint64_t                                Signature;
        uint32_t                                Revision;
        uint32_t                                HeaderSize;
        uint32_t                                CRC32;
        uint32_t                                Reserved;
}EFI_TABLE_HEADER;

/* -------------------------------------------------------------------------- *
 * EFI_SIMPLE_TEXT_INPUT_PROTOCOL contents:
 */

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID                                   \
        {0x387477c1,0x69c7,0x11d2,                                            \
        {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef struct{
        EFI_INPUT_RESET                         Reset;
        EFI_INPUT_READ_KEY                      ReadKeyStroke;
        EFI_EVENT                               WaitForKey;
}EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_INPUT_RESET)(
     IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL         *This,
     IN efi_bool                                ExtendedVerification
);

typedef EFI_STATUS (EFI_API *EFI_INPUT_READ_KEY)(
     IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL         *This,
    OUT EFI_INPUT_KEY                          *Key
);

typedef struct{
        uint16_t                                ScanCode;
        uchar16_t                               UnicodeChar;
}EFI_INPUT_KEY;

/* -------------------------------------------------------------------------- *
 * EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL contents:
 */

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID                                  \
        {0x387477c2,0x69c7,0x11d2,                                            \
        {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

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
}EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_TEXT_RESET)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN efi_bool                                ExtendedVerification
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_STRING)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN uint16_t                               *String
);

/* -------------------------------------------------------------------------- *
 * UNICODE DRAWING CHARACTERS
 */

#define BOXDRAW_HORIZONTAL                      0x2500
#define BOXDRAW_VERTICAL                        0x2502
#define BOXDRAW_DOWN_RIGHT                      0x250c
#define BOXDRAW_DOWN_LEFT                       0x2510
#define BOXDRAW_UP_RIGHT                        0x2514
#define BOXDRAW_UP_LEFT                         0x2518
#define BOXDRAW_VERTICAL_RIGHT                  0x251c
#define BOXDRAW_VERTICAL_LEFT                   0x2524
#define BOXDRAW_DOWN_HORIZONTAL                 0x252c
#define BOXDRAW_UP_HORIZONTAL                   0x2534
#define BOXDRAW_VERTICAL_HORIZONTAL             0x253c

#define BOXDRAW_DOUBLE_HORIZONTAL               0x2550
#define BOXDRAW_DOUBLE_VERTICAL                 0x2551
#define BOXDRAW_DOWN_RIGHT_DOUBLE               0x2552
#define BOXDRAW_DOWN_DOUBLE_RIGHT               0x2553
#define BOXDRAW_DOUBLE_DOWN_RIGHT               0x2554
#define BOXDRAW_DOWN_LEFT_DOUBLE                0x2555
#define BOXDRAW_DOWN_DOUBLE_LEFT                0x2556
#define BOXDRAW_DOUBLE_DOWN_LEFT                0x2557

#define BOXDRAW_UP_RIGHT_DOUBLE                 0x2558
#define BOXDRAW_UP_DOUBLE_RIGHT                 0x2559
#define BOXDRAW_DOUBLE_UP_RIGHT                 0x255a
#define BOXDRAW_UP_LEFT_DOUBLE                  0x255b
#define BOXDRAW_UP_DOUBLE_LEFT                  0x255c
#define BOXDRAW_DOUBLE_UP_LEFT                  0x255d

#define BOXDRAW_VERTICAL_RIGHT_DOUBLE           0x255e
#define BOXDRAW_VERTICAL_DOUBLE_RIGHT           0x255f
#define BOXDRAW_DOUBLE_VERTICAL_RIGHT           0x2560

#define BOXDRAW_VERTICAL_LEFT_DOUBLE            0x2561
#define BOXDRAW_VERTICAL_DOUBLE_LEFT            0x2562
#define BOXDRAW_DOUBLE_VERTICAL_LEFT            0x2563

#define BOXDRAW_DOWN_HORIZONTAL_DOUBLE          0x2564
#define BOXDRAW_DOWN_DOUBLE_HORIZONTAL          0x2565
#define BOXDRAW_DOUBLE_DOWN_HORIZONTAL          0x2566

#define BOXDRAW_UP_HORIZONTAL_DOUBLE            0x2567
#define BOXDRAW_UP_DOUBLE_HORIZONTAL            0x2568
#define BOXDRAW_DOUBLE_UP_HORIZONTAL            0x2569

#define BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE      0x256a
#define BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL      0x256b
#define BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL      0x256c

/* -------------------------------------------------------------------------- *
 * EFI Required Block Elements Code Chart
 */

#define BLOCKELEMENT_FULL_BLOCK                 0x2588
#define BLOCKELEMENT_LIGHT_SHADE                0x2591

/* -------------------------------------------------------------------------- *
 * EFI Required Geometric Shapes Code Chart
 */

#define GEOMETRICSHAPE_UP_TRIANGLE              0x25b2
#define GEOMETRICSHAPE_RIGHT_TRIANGLE           0x25ba
#define GEOMETRICSHAPE_DOWN_TRIANGLE            0x25bc
#define GEOMETRICSHAPE_LEFT_TRIANGLE            0x25c4

/* -------------------------------------------------------------------------- *
 * EFI Required Arrow shapes
 */

#define ARROW_UP                                0x2191
#define ARROW_DOWN                              0x2193

typedef EFI_STATUS (EFI_API *EFI_TEXT_TEST_STRING)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN uchar16_t                              *String
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_QUERY_MODE)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN uintptr_t                               ModeNumber,
    OUT uintptr_t                              *Columns,
    OUT uintptr_t                              *Rows
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_SET_MODE)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN uintptr_t                               ModeNumber
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_SET_ATTRIBUTE)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN uintptr_t                               Attribute
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_CLEAR_SCREEN)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_SET_CURSOR_POSITION)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN uintptr_t                               Column,
     IN uintptr_t                               Row
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_ENABLE_CURSOR)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN efi_bool                                Visible
);

typedef struct {
        int32_t                                 MaxMode;

        /* current settings (UEFI said this, not me xD) */
        int32_t                                 Mode;
        int32_t                                 Attribute;
        int32_t                                 CursorColumn;
        int32_t                                 CursorRow;
        efi_bool                                CursorVisible;
}SIMPLE_TEXT_OUTPUT_MODE;

/* -------------------------------------------------------------------------- *
 * EFI_RUNTIME_SERVICES contents:
 */

#define EFI_RUNTIME_SERVICES_SIGNATURE          0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION           EFI_SPECIFICATION_VERSION

typedef struct{
        EFI_TABLE_HEADER                        Hdr;
        
        /* Omitted functions */
        void                                   *padding__[14];
}EFI_RUNTIME_SERVICES;

/* -------------------------------------------------------------------------- *
 * EFI_BOOT_SERVICES contents:
 */

#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION

typedef struct{
        EFI_TABLE_HEADER                        Hdr;

        /* Omitted functions */
        void                                   *padding__[44];
}EFI_BOOT_SERVICES;

/* -------------------------------------------------------------------------- *
 * EFI_CONFIGURATION_TABLE contents:
 */

typedef struct{
        EFI_GUID                                VendorGuid;
        void                                   *VendorTable;
}EFI_CONFIGURATION_TABLE;

typedef struct{
        uint32_t                                d1;
        uint16_t                                d2;
        uint16_t                                d3;
        uint8_t                                 d4[8];
}EFI_GUID;

#endif /* ROSE_EFI_H */