#include <rose/string.h>

uint64_t strlen(const char *str){
        uint64_t len;
        for(len = 0; str[len]; len++);
        return len;
}