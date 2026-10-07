#include <rose/string_helper.h>

size_t strlen(char *str){
        size_t len;
        for(len = 0; str[len]; len++);
        return len;
}