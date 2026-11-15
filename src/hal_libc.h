/* Declarations for src/hal_libc.c. */
#ifndef HAL_LIBC_H
#define HAL_LIBC_H

#include "global.h"

// hal_libc.c
char* HAL_Strcpy(char* dest, char* src);
char* HAL_Strcpy2(char *dest, char* src);
size_t HAL_Strcmp(char* dest, char* src);
char* HAL_Memset(char* dest, s32 c, u32 nsize);

#endif // HAL_LIBC_H
