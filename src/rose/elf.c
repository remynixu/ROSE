#include <rose/elf.h>

#include <stddef.h>

/* 0x7f, 0x45, 0x4c, 0x46 */

bool elf_check(void *buf){
        struct elf64_identity *identity = buf;
        const char magic[ELF_MAGIC_COUNT] = {0x7f, 0x45, 0x4c, 0x46};
        int i;
        for(i = 0; i < ELF_MAGIC_COUNT; i++){
                if(identity->magic[i] != magic[i])
                        return 0;
        }
        return 1;
}