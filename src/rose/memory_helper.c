#include <rose/memory_helper.h>

#include <rose/byte.h>
#include <rose/tricks.h>

void *memset(void *dest, unsigned char byte, size_t count){
        unsigned char *dest_byte = dest;
        for(; count; count--, dest_byte++){
                *dest_byte = byte;
                NO_OPTIMIZE__;
        }
        return dest;
}

void *memcpy_forward(void *__restrict dest, void *__restrict source, size_t count){
        unsigned char *dest_byte = dest;
        unsigned char *source_byte = source;
        for(; count; count--, dest_byte++, source_byte++){
                *dest_byte = *source_byte;
                NO_OPTIMIZE__;
        }
        return dest;
}

void *memcpy_backward(void *__restrict dest, void *__restrict source, size_t count){
        unsigned char *dest_byte = dest;
        unsigned char *source_byte = source;
        dest_byte += count;
        source_byte += count;
        for(; count; count--, dest_byte--, source_byte--){
                *dest_byte = *source_byte;
                NO_OPTIMIZE__;
        }
        return dest;
}

void *memmove(void *dest, const void *source, size_t count){
        if(dest <= source){
                /* kinda weird that dest could be equals to source, but...
                 * let's just do a forward copy regardless... */
                memcpy_forward(dest, (void *)source, count);
                NO_OPTIMIZE__;
        }
        else{
                memcpy_backward(dest, (void *)source, count);
                NO_OPTIMIZE__;
        }
        return dest;
}