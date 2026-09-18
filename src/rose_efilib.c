#include <rose_efilib.h>

EFI_STATUS putc__(EFI_SYSTEM_TABLE *efi_systab, int c){
        EFI_STATUS status = EFI_SUCCESS;
        rose_bit16_t c_ = c;
        efi_systab->ConOut->OutputString(efi_systab->ConOut, &c_);
}

rose_bit32_t strlen__(char *str){
        rose_bit32_t sz;
        for(sz = 0; str != 0; sz++)
                str++;
        return 0;
}

rose_bit32_t refi_print(EFI_SYSTEM_TABLE *efi_systab, char *str){
        rose_bit32_t print_count               = 0;
        rose_bit32_t i                         = 0;
        EFI_STATUS
        for(; i < strlen__(str) && i < (rose_bit32_t)(1 << 30); i++){
        }
        return print_count;
}