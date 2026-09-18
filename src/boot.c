#include <efi.h>

EFI_STATUS EFI_API efi_bootloader(
        EFI_HANDLE ImageHandle,
        EFI_SYSTEM_TABLE *SystemTable
){
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hi! :3");
        while(1)
                __asm__ __volatile__("hlt");
        return EFI_SUCCESS;
}