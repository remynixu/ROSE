#include <efi/efi.h>
#include <efi/efi_utils.h>

EFI_STATUS EFI_API efi_bootloader(
        EFI_HANDLE ImageHandle,
        EFI_SYSTEM_TABLE *SystemTable
){
        efi_output(SystemTable, SystemTable->FirmwareVendor);
        while(1)
                __asm__ __volatile__("hlt");
        return EFI_SUCCESS;
}