#include <efi/efi_utils.h>
#include <rose/basic_memory.h>

extern EFI_STATUS global_efi_status;

bool efi_output(
        EFI_SYSTEM_TABLE                       *ctx,
        const uint16_t                         *utf16
){
        global_efi_status = ctx->ConOut->OutputString(ctx->ConOut, utf16);
        return EFI_ISSUCCESS(global_efi_status);
}

bool efi_printc(
        EFI_SYSTEM_TABLE                       *ctx,
        const uint16_t                          c
){
        uint16_t utf16[2];
        utf16[0] = c;
        utf16[1] = 0;
        return efi_output(ctx, utf16);
}

bool efi_prints(
        EFI_SYSTEM_TABLE                       *ctx,
        const char                             *str
){
        uint64_t i;
        for(i = 0; i < strlen(str); i++){
                if(efi_printc(ctx, str[i]))
                        continue;
                if(EFI_ISERROR(global_efi_status))
                        break;
        }
        return EFI_ISSUCCESS(global_efi_status);
}

bool efi_input(
        EFI_SYSTEM_TABLE                       *ctx,
        EFI_INPUT_KEY                           key             [static 1]
){
        global_efi_status = ctx->ConIn->ReadKeyStroke(ctx->ConIn, key);
        return EFI_ISSUCCESS(global_efi_status);
}

bool efi_keystroke(
        EFI_SYSTEM_TABLE                       *ctx,
        uint16_t                                scancode        [static 1],
        uint16_t                                unicode         [static 1]
){
        EFI_INPUT_KEY key;
        if(!efi_input(ctx, &key)){
                if(!EFI_ISSUCCESS(global_efi_status))
                        goto exit;
        }
        *scancode = key.ScanCode;
        *unicode = key.UnicodeChar;
exit:
        return EFI_ISSUCCESS(global_efi_status);
}