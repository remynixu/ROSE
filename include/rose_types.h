#ifndef ROSE_TYPES_H

/*
 * What about Clang's stdint library extensions? Well...
 * 
 * I'll ignore Clang's stdint.h and make my own regardless, mainly because I
 * want to be sure I get the sizes right.
 *
 * Also, this reduces dependence to the compiler.
 */
#define ROSE_TYPES_H

/*
 * A hack to check and make sure data types are sane :>
 *
 * Note: Strictly only called once, otherwise it's undefined behavior.
 */
#define ROSE_CHECK_DATASIZE(name, expected_bytesize)                          \
        typedef name rose_check_datasize_##name[                              \
                (sizeof(name) == expected_bytesize) ? 1 : -1                  \
        ]

typedef unsigned char                           rose_bit8_t;
typedef signed char                             rose_sbit8_t;

ROSE_CHECK_DATASIZE(rose_bit8_t, 1);
ROSE_CHECK_DATASIZE(rose_sbit8_t, 1);

typedef rose_bit8_t                             rose_bool;

typedef unsigned short                          rose_bit16_t;
typedef signed short                            rose_sbit16_t;

ROSE_CHECK_DATASIZE(rose_bit16_t, 2);
ROSE_CHECK_DATASIZE(rose_sbit16_t, 2);

typedef unsigned int                            rose_bit32_t;
typedef signed int                              rose_sbit32_t;

ROSE_CHECK_DATASIZE(rose_bit32_t, 4);
ROSE_CHECK_DATASIZE(rose_sbit32_t, 4);

#if defined(__has_extension)

__extension__ typedef unsigned long long        rose_bit64_t;
__extension__ typedef signed long long          rose_sbit64_t;

ROSE_CHECK_DATASIZE(rose_bit64_t, 8);
ROSE_CHECK_DATASIZE(rose_sbit64_t, 8);

__extension__ typedef rose_bit64_t              rose_native_t;
__extension__ typedef rose_sbit64_t             rose_snative_t;

#else

#error "This header uses extensions for 64-bit data type support in C89."

#endif /* 64-BIT EXTENSION */

#endif /* ROSE_TYPES_H */