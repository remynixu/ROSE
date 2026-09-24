#include <efi/efi_utils.h>
#include <rose/string.h>

EFI_STATUS efi_output(
        EFI_SYSTEM_TABLE                       *ctx,
        const uint16_t                         *utf16
){
        return ctx->ConOut->OutputString(ctx->ConOut, utf16);
}

EFI_STATUS efi_printc(
        EFI_SYSTEM_TABLE                       *ctx,
        const uint16_t                          c
){
        uint16_t utf16[2];
        utf16[0] = c;
        utf16[1] = 0;
        return efi_output(ctx, utf16);
}

EFI_STATUS efi_prints(
        EFI_SYSTEM_TABLE                       *ctx,
        const char                             *str
){
        EFI_STATUS status = EFI_SUCCESS;
        uint64_t i;
        for(i = 0; i < strlen(str); i++){
                status = efi_printc(ctx, str[i]);
                if(EFI_ISERROR(status))
                        break;
        }
        return status;
}