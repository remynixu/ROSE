#ifndef ROSE_EFI_H

/*
 * This header is primarily for loading the rOSe kernel using the UEFI
 * specifications for its bootloader.
 *
 * All of the header's code is derived from this link:
 * - https://uefi.org/specs/UEFI/2.10
 */
#define ROSE_EFI_H

/*
 * Since stdint.h doesn't exist in C89, we use our own data types :<
 */
#include <rose_types.h>

/*
 * To make sure the compiler doesn't do any unexpected magic... please add this
 * before the name of every EFI function :<
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
typedef rose_bit8_t                             efi_bool;

/* UEFI uses 16-bit characters... */
typedef rose_bit16_t                            uchar16_t;

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
typedef rose_native_t                           EFI_STATUS;

#define EFI_SUCCESS                             ((EFI_STATUS)0)

#define ERRORCODE_BITMASK__                     ((EFI_STATUS)1 << 63)
#define ERRORCODE__(ec__)                                                     \
        ((EFI_STATUS)(ec__) | ERRORCODE_BITMASK__)

/*
 * ERROR/WARNING HELPERS:
 */

#define EFI_ISERROR(ec__)                                                     \
        ((EFI_STATUS)(ec__) & ERRORCODE_BITMASK__)
#define EFI_ISWARNING(ec__)                                                   \
        ((EFI_STATUS)(ec__) != EFI_SUCCESS) && !EFI_ISERROR((EFI_STATUS)(ec__))

/*
 * ERRORS:
 */

#define EFI_LOAD_ERROR                          ERRORCODE__(1)
#define EFI_INVALID_PARAMETER                   ERRORCODE__(2)
#define EFI_UNSUPPORTED                         ERRORCODE__(3)
#define EFI_BAD_BUFFER_SIZE                     ERRORCODE__(4)
#define EFI_BUFFER_TOO_SMALL                    ERRORCODE__(5)
#define EFI_NOT_READY                           ERRORCODE__(6)
#define EFI_DEVICE_ERROR                        ERRORCODE__(7)
#define EFI_WRITE_PROTECTED                     ERRORCODE__(8)
#define EFI_OUT_OF_RESOURCES                    ERRORCODE__(9)
#define EFI_VOLUME_CORRUPTED                    ERRORCODE__(10)
#define EFI_VOLUME_FULL                         ERRORCODE__(11)
#define EFI_NO_MEDIA                            ERRORCODE__(12)
#define EFI_MEDIA_CHANGED                       ERRORCODE__(13)
#define EFI_NOT_FOUND                           ERRORCODE__(14)

/* ========================================================================== *
 * UEFI Functions:
 */

/*
 * Since these data are already defined by UEFI, it's all just mostly just
 * copy-pasted code below...
 */

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

#define EFI_SYSTEM_TABLE_REVISION               EFI_2_100_SYSTEM_TABLE_REVISION
#define EFI_SPECIFICATION_VERSION               EFI_SYSTEM_TABLE_REVISION

typedef struct{
        rose_bit64_t                            Signature;
        rose_bit32_t                            Revision;
        rose_bit32_t                            HeaderSize;
        rose_bit32_t                            CRC32;
        rose_bit32_t                            Reserved;
}EFI_TABLE_HEADER;

/* -------------------------------------------------------------------------- *
 * EFI_SIMPLE_TEXT_INPUT_PROTOCOL contents:
 */

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID                                   \
        {0x387477c1,0x69c7,0x11d2,                                            \
        {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL  EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_INPUT_RESET)(
     IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL         *This,
     IN efi_bool                                ExtendedVerification
);

typedef struct{
        rose_bit16_t                            ScanCode;
        uchar16_t                               UnicodeChar;
}EFI_INPUT_KEY;

typedef EFI_STATUS (EFI_API *EFI_INPUT_READ_KEY)(
     IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL         *This,
    OUT EFI_INPUT_KEY                          *Key
);

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL{
        EFI_INPUT_RESET                         Reset;
        EFI_INPUT_READ_KEY                      ReadKeyStroke;
        EFI_EVENT                               WaitForKey;
}EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

/* -------------------------------------------------------------------------- *
 * EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL contents:
 */

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID                                  \
        {0x387477c2,0x69c7,0x11d2,                                            \
        {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL                               \
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_TEXT_RESET)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN efi_bool                                ExtendedVerification
);

/*
 * Returns:
 * - EFI_SUCCESS
 * - EFI_DEVICE_ERROR
 * - EFI_UNSUPPORTED
 * - EFI_WARN_UNKNOWN_GLYPH
 */
typedef EFI_STATUS (EFI_API *EFI_TEXT_STRING)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN rose_bit16_t                           *String
);

/*
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

/*
 * EFI Required Block Elements Code Chart
 */

#define BLOCKELEMENT_FULL_BLOCK                 0x2588
#define BLOCKELEMENT_LIGHT_SHADE                0x2591

/*
 * EFI Required Geometric Shapes Code Chart
 */

#define GEOMETRICSHAPE_UP_TRIANGLE              0x25b2
#define GEOMETRICSHAPE_RIGHT_TRIANGLE           0x25ba
#define GEOMETRICSHAPE_DOWN_TRIANGLE            0x25bc
#define GEOMETRICSHAPE_LEFT_TRIANGLE            0x25c4

/*
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
     IN rose_native_t                           ModeNumber,
    OUT rose_native_t                          *Columns,
    OUT rose_native_t                          *Rows
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_SET_MODE)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN rose_native_t                           ModeNumber
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_SET_ATTRIBUTE)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN rose_native_t                           Attribute
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_CLEAR_SCREEN)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_SET_CURSOR_POSITION)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN rose_native_t                           Column,
     IN rose_native_t                           Row
);

typedef EFI_STATUS (EFI_API *EFI_TEXT_ENABLE_CURSOR)(
     IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
     IN efi_bool                                Visible
);

typedef struct {
        rose_sbit32_t                           MaxMode;

        /* current settings (UEFI said this, not me xD) */
        rose_sbit32_t                           Mode;
        rose_sbit32_t                           Attribute;
        rose_sbit32_t                           CursorColumn;
        rose_sbit32_t                           CursorRow;
        efi_bool                                CursorVisible;
}SIMPLE_TEXT_OUTPUT_MODE;

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL{
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

/* -------------------------------------------------------------------------- *
 * EFI_RUNTIME_SERVICES contents:
 */

typedef struct{
        rose_bit16_t                            Year;
        rose_bit8_t                             Month;
        rose_bit8_t                             Day;
        rose_bit8_t                             Hour;
        rose_bit8_t                             Minute;
        rose_bit8_t                             Second;
        rose_bit8_t                             padding__1;
        rose_bit32_t                            Nanosecond;
        rose_sbit16_t                           TimeZone;
        rose_bit8_t                             Daylight;
        rose_bit8_t                             padding__2;
}EFI_TIME;

typedef struct{
        rose_bit32_t                            Resolution;
        rose_bit32_t                            Accuracy;
        efi_bool                                SetsToZero;
}EFI_TIME_CAPABILITIES;

/*
 * Returns;
 * - EFI_SUCCESS
 * - EFI_INVALID_PARAMETER
 * - EFI_DEVICE_ERROR
 */
typedef EFI_STATUS (EFI_API *EFI_GET_TIME)(
    OUT EFI_TIME                               *Time,
    OUT EFI_TIME_CAPABILITIES                  *Capabilities OPTIONAL
);

#define EFI_RUNTIME_SERVICES_SIGNATURE          0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION           EFI_SPECIFICATION_VERSION

typedef struct{
        EFI_TABLE_HEADER                        Hdr;

        EFI_GET_TIME                            GetTime;
        
        /* Omitted functions */
        void                                   *padding__1[13];
}EFI_RUNTIME_SERVICES;

/* -------------------------------------------------------------------------- *
 * EFI_BOOT_SERVICES contents:
 */

/* -------------------------------------------------------------------------- *
 * MEMORY SERVICES:
 */

#define EFI_BOOT_SERVICES_SIGNATURE             0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION              EFI_SPECIFICATION_VERSION

typedef enum{
        AllocateAnyPages,
        AllocateMaxAddress,
        AllocateAddress,
        MaxAllocateType
}EFI_ALLOCATE_TYPE;

typedef enum{
        EfiReservedMemoryType = 0, /* This drove me crazy lmao xD */
        EfiLoaderCode,
        EfiLoaderData,
        EfiBootServicesCode,
        EfiBootServicesData,
        EfiRuntimeServicesCode,
        EfiRuntimeServicesData,
        EfiConventionalMemory,
        EfiUnusableMemory,
        EfiACPIReclaimMemory,
        EfiACPIMemoryNVS,
        EfiMemoryMappedIOPortSpace,
        EfiPalCode,
        EfiPersistentMemory,
        EfiUnacceptedMemoryType,
        EfiMaxMemoryType
}EFI_MEMORY_TYPE;

typedef rose_bit64_t                            EFI_PHYSICAL_ADDRESS;

typedef EFI_STATUS (EFI_API *EFI_ALLOCATE_PAGES)(
     IN EFI_ALLOCATE_TYPE                       Type,
     IN EFI_MEMORY_TYPE                         MemoryType,
     IN rose_native_t                           Pages,
 IN OUT EFI_PHYSICAL_ADDRESS                   *Memory
);

typedef EFI_STATUS (EFI_API *EFI_FREE_PAGES)(
     IN EFI_PHYSICAL_ADDRESS                   *Memory,
     IN rose_native_t                           Pages
);

#define EFI_MEMORY_UC                           0x0000000000000001
#define EFI_MEMORY_WC                           0x0000000000000002
#define EFI_MEMORY_WT                           0x0000000000000004
#define EFI_MEMORY_WB                           0x0000000000000008
#define EFI_MEMORY_UCE                          0x0000000000000010
#define EFI_MEMORY_WP                           0x0000000000001000
#define EFI_MEMORY_RP                           0x0000000000002000
#define EFI_MEMORY_XP                           0x0000000000004000
#define EFI_MEMORY_NV                           0x0000000000008000
#define EFI_MEMORY_MORE_RELIABLE                0x0000000000010000
#define EFI_MEMORY_RO                           0x0000000000020000
#define EFI_MEMORY_SP                           0x0000000000040000
#define EFI_MEMORY_CPU_CRYPTO                   0x0000000000080000
#define EFI_MEMORY_HOT_PLUGGABLE                0x0000000000100000
#define EFI_MEMORY_RUNTIME                      0x8000000000000000
#define EFI_MEMORY_ISA_VALID                    0x4000000000000000
#define EFI_MEMORY_ISA_MASK                     0x0FFFF00000000000

typedef rose_bit64_t                            EFI_VIRTUAL_ADDRESS;

#define EFI_MEMORY_DESCRIPTOR_VERSION           1

typedef struct{
        rose_bit32_t                            Type;
        EFI_PHYSICAL_ADDRESS                    PhysicalStart;
        EFI_VIRTUAL_ADDRESS                     VirtualStart;
        rose_bit64_t                            NumberOfPages;
        rose_bit64_t                            Attribute;
}EFI_MEMORY_DESCRIPTOR;

typedef EFI_STATUS (EFI_API *EFI_GET_MEMORY_MAP)(
 IN OUT rose_native_t                          *MemoryMapSize,
    OUT EFI_MEMORY_DESCRIPTOR                  *MemoryMap,
    OUT rose_native_t                          *MapKey,
    OUT rose_native_t                          *DescriptorSize,
    OUT rose_bit32_t                           *DescriptorVersion
);

typedef EFI_STATUS (EFI_API *EFI_ALLOCATE_POOL)(
     IN EFI_MEMORY_TYPE                         PoolType,
     IN rose_native_t                           Size,
    OUT void                                  **Buffer
);

typedef EFI_STATUS (EFI_API *EFI_FREE_POOL)(
     IN void                                   *Buffer
);

typedef struct{
        EFI_TABLE_HEADER                        Hdr;

        /* Omitted functions */
        void                                   *padding__1[2];

        EFI_ALLOCATE_PAGES                      AllocatePages;
        EFI_FREE_PAGES                          FreePages;
        EFI_GET_MEMORY_MAP                      GetMemoryMap;
        EFI_ALLOCATE_POOL                       AllocatePool;
        EFI_FREE_POOL                           FreePool;

        /* Omitted functions */
        void                                   *padding__2[38];
}EFI_BOOT_SERVICES;

/* -------------------------------------------------------------------------- *
 * EFI_CONFIGURATION_TABLE contents:
 */

typedef struct{
        rose_bit32_t                            d1;
        rose_bit16_t                            d2;
        rose_bit16_t                            d3;
        rose_bit8_t                             d4[8];
}EFI_GUID;

typedef struct{
        EFI_GUID                                VendorGuid;
        void                                   *VendorTable;
}EFI_CONFIGURATION_TABLE;

typedef struct{
        EFI_TABLE_HEADER                        Hdr;
        rose_bit16_t                           *FirmwareVendor;
        rose_bit32_t                            FirmwareRevision;
        EFI_HANDLE                              ConsoleInHandle;
        EFI_SIMPLE_TEXT_INPUT_PROTOCOL         *ConIn;
        EFI_HANDLE                              ConsoleOutHandle;
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *ConOut;
        EFI_HANDLE                              StandardErrorHandle;
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *StdErr;
        EFI_RUNTIME_SERVICES                   *RuntimeServices;
        EFI_BOOT_SERVICES                      *BootServices;
        rose_native_t                           NumberOfTableEntries;
        EFI_CONFIGURATION_TABLE                *ConfigurationTable;
}EFI_SYSTEM_TABLE;

/*
 * The entry porose_sbit of an EFI binary.
 *
 * EFI_HANDLE is an opaque porose_sbiter we're not supposd to tamper with.
 * EFI_SYSTEM_TABLE is where the useful functions and data are!
 */
typedef EFI_STATUS (EFI_API *EFI_IMAGE_ENTRY_POINT)(
     IN EFI_HANDLE                              ImageHandle,
     IN EFI_SYSTEM_TABLE                       *SystemTable
);

#endif /* ROSE_EFI_H */