#ifndef ELF_H

/*
 * ELF parser :<
 */
#define ELF_H

#include <stdint.h>

/* 0x7f, 0x45, 0x4c, 0x46 */
#define ELF_MAGIC                               4

enum elf_bitness{
        ELF_BITNESS_32 =                        1, /* 32-bit                  */
        ELF_BITNESS_64 =                        2  /* 64-bit                  */
};

enum elf_endianness{
        ELF_ENDIANNESS_LITTLE =                 1, /* little-endian           */
        ELF_ENDIANNESS_BIG =                    2  /* big-endian              */
};

enum elf_osabi{
        ELF_OSABI_SYSV =                        0,  /* System V ABI           */
        ELF_OSABI_HPUX =                        1,  /* HP-UX Operating System */
        ELF_OSABI_STANDALONE =                  255 /* Standalone/Embedded    */
};

/*
 * - magic[4]      - ELF_MAGIC
 * - bitness       - 0 = Invalid, 1 = 32-bit, 2 = 64-bit
 * - endianness    - 1 = little-endian, 2 = big-endian
 * - file_version  - "...which is defined with the value 1." (Cary Coutant)
 * - os_abi        - 0 = System V ABI, 1 = HP-UX, 255 = Standalone
 * - abi_version   - Usually 0.
 */

struct __attribute((packed)) elf64_identity{
        uint8_t                                 magic[4];
        uint8_t                                 bitness;
        uint8_t                                 endianness;
        uint8_t                                 file_version;
        uint8_t                                 osabi;
        uint8_t                                 abi_version;
        uint8_t                                 padding__[6];
        uint8_t                                 identity_size;
};

enum elf_type{
        ELF_TYPE_NONE =                         0, /* No file type            */
        ELF_TYPE_RELOCATABLE =                  1, /* Relocatable object file */
        ELF_TYPE_EXECUTABLE =                   2, /* Executable file         */
        ELF_TYPE_DYNAMIC =                      3, /* Shared object file      */
        ELF_TYPE_CORE =                         4  /* Core file               */
};

/*
 * - type           - Object's file type.
 * - machine        - Target architecture.
 * - version        - Format's version, "...defined with [...] 1" (Cary Coutant)
 * - entry_offset   - Virtual address of program's entry point, 0 if no entry.
 * - prg_hdr_offset - Bytes file offset of the program header table.
 * - sct_hdr_offset - Bytes file offset of the section header table.
 * - flags          - Processor-specific flags.
 * - eh_size        - Elf header's size.
 * - prg_entry_size - Byte size of a program header table entry.
 * - prg_entry_n    - Number of entries in the program header table.
 * - sct_entry_size - Byte size of a section header table entry.
 * - sct_entry_n    - Number of entries in the section header table.
 * - sct_str_index  - Index of the section with the section name string table.
 */

struct __attribute((packed)) elf64_header{
        struct elf64_identity                   identity;
        uint16_t                                type;
        uint16_t                                machine;
        uint32_t                                version;
        uint64_t                                entry_offset;
        uint64_t                                prg_hdr_offset;
        uint64_t                                sct_hdr_offset;
        uint32_t                                flags;
        uint16_t                                eh_size;
        uint16_t                                prg_entry_size;
        uint16_t                                prg_entry_n;
        uint16_t                                sct_entry_size;
        uint16_t                                sct_entry_n;
        uint16_t                                sct_str_index;
};

struct __attribute((packed)) elf64_program_header{
        uint32_t                                seg_type;
        uint32_t                                flags;
        uint64_t                                data_offset;
        uint64_t                                vaddr;
        uint64_t                                paddr;
        uint64_t                                seg_filesize;
        uint64_t                                seg_memsize;
        uint64_t                                alignment;
};

enum elf_section_type{
        ELF_SECTION_NULL =                      0,  /* Unused section         */
        ELF_SECTION_PROGBITS =                  1,  /* Defined by program     */
        ELF_SECTION_SYMTAB =                    2,  /* Linker symbol table    */
        ELF_SECTION_STRTAB =                    3,  /* String table           */
        ELF_SECTION_RELA =                      4,  /* "Rela" type relocation */
        ELF_SECTION_HASH =                      5,  /* Symbol hash table      */
        ELF_SECTION_DYNAMIC =                   6,  /* Dynamic linking tables */
        ELF_SECTION_NOTE =                      7,  /* Note information       */
        ELF_SECTION_NOBITS =                    8,  /* Doesn't occupy space   */
        ELF_SECTION_REL =                       9,  /* "Rel" type relocation  */
        ELF_SECTION_SHLIB =                     10, /* Reserved               */
        ELF_SECTION_DYNSYM =                    11  /* Dynamic loader symtab  */
};

enum elf_section_flag{
        ELF_SECTION_WRITABLE =                  0x1, /* Has writable data     */
        ELF_SECTION_ALLOCATED =                 0x2, /* Allocated in memory   */
        ELF_SECTION_EXECUTABLE =                0x4  /* Contains instructions */
};

/*
 * Use of elf_section_header.link:
 * - ELF_SECTION_DYNAMIC - String table used by entries in this section.
 * - ELF_SECTION_HASH    - Symbol table to which the hash table applies.
 * - ELF_SECTION_REL     - Symbol table referenced by relocations.
 * - ELF_SECTION_RELA    ^
 * - ELF_SECTION_SYMTAB  - String table used by entries in this section.
 * - ELF_SECTION_DYNSYM  ^
 */

/*
 * Use of elf_section_header.misc_info:
 * - ELF_SECTION_REL    - Section index of section to which the relocations
 * - ELF_SECTION_RELA   ^ apply.
 * - ELF_SECTION_SYMTAB - Index of first non-local symbol (i.e., number of
 * - ELF_SECTION_DYNSYM ^ local symbols)
 * - [Others]           - 0
 */

/*
 * - name_offset - Bytes offset to the section name, relative to the start of
 *                 the section name string table.
 * - type        - Section type.
 * - flags       - Attributes of the section.
 * - vaddr       - Virtual address of the beginning of the section in memory.
 *                 0 if the section is not allocated to the memory image of the
 *                 program.
 * - file_offset - Bytes offset of the beginning of the section contents in the
 *                 file.
 * - size        - Byte size of the section (except for SHT_NOBITS sections),
 *                 this is the amount of space occupied in the file.
 * - link        - Section index of an associated section, use varies on type.
 * - misc_info   - Extra info.
 * - addralign   - Required alignment of the section.
 * - entsize     - Byte size of each entry for sections that contains fixed-size
 *                 entries, else contains 0.
 */

struct __attribute((packed)) elf64_section_header{
        uint32_t                                name_offset;
        uint32_t                                type;
        uint64_t                                flags;
        uint64_t                                vaddr;
        uint64_t                                file_offset;
        uint64_t                                size;
        uint32_t                                link;
        uint32_t                                misc_info;
        uint64_t                                addralign;
        uint64_t                                entsize;
};

#endif /* ELF_H */
