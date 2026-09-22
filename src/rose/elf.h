#ifndef ELF_H

/*
 * ELF parser for ROSE :<
 */
#define ELF_H

#include <stdint.h>

/* 0x7f, 0x45, 0x4c, 0x46 */
#define ELF_MAGIC                               4

/*
 * - magic                                      (0x7f454c46)
 * - archbit                                    (2 for 64-bit)
 * - endianness                                 (1 for little endian)
 * - osabi                                      (0 for system v)
 * - type:
 *   - 1 = relocatable
 *   - 2 = executable
 *   - 3 = shared
 *   - 4 = core
 * - instrset                                   (0x3e for Intel)
 * - elf_version                                ("currently 1" - osdev.org)
 * - flags                                      (0 on x64_64/Intel, hooray! :D)
 * - size                                       (apparently varied)
 */

struct __attribute((packed)) elf64_header{
        uint8_t                                 magic[ELF_MAGIC];
        uint8_t                                 archbit;
        uint8_t                                 endianness;
        uint8_t                                 version;
        uint8_t                                 osabi;
        uint8_t                                 padding__[8];
        uint16_t                                type;
        uint16_t                                instrset;
        uint32_t                                elf_version;
        uint64_t                                prg_entry_off;
        uint64_t                                prg_hdrtable_off;
        uint64_t                                sct_hdrtable_off;
        uint32_t                                flags;
        uint16_t                                size;
        uint16_t                                prg_entry_size;
        uint16_t                                prg_entry_n;
        uint16_t                                sct_entry_size;
        uint16_t                                sct_entry_n;
        uint16_t                                sct_strtable_index;
};

/*
 * - seg_type:
 *   - 0 = ignore
 *   - 1 = clear `seg_memsize` bytes at `vaddr` to 0
 *   - 2 = dynamic linking
 *   - 3 = has interpreter
 *   - 4 = note section
 * - flags:
 *   - 1 = executable
 *   - 2 = writable
 *   - 4 = readable
 */

struct __attribute((packed)) elf64_program_header{
        uint32_t                                seg_type;
        uint32_t                                flags;
        uint64_t                                data_off;
        uint64_t                                vaddr;
        uint64_t                                paddr;
        uint64_t                                seg_filesize;
        uint64_t                                seg_memsize;
        uint64_t                                alignment;
};

/* TODO: Section Types: https://uclibc.org/docs/elf-64-gen.pdf */

struct __attribute((packed)) elf64_section_header{
        uint32_t                                name_off;
        uint32_t                                type;
        uint64_t                                flags;
        uint64_t                                vaddr;
        uint64_t                                file_off;
        uint64_t                                size;
        uint32_t                                link;
        uint32_t                                misc_info;
        uint64_t                                addralign;
        uint64_t                                entsize;
};

#endif /* ELF_H */