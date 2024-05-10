/*
** EPITECH PROJECT, 2023
** array
** File description:
** array
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basics.h"

void *smalloc(size_t size)
{
    void *ptr = malloc(size);

    if (!ptr)
        my_fputstr("Malloc Failed\n", 2);
    return ptr;
}

void *my_memcpy(void *dest, const void *source, size_t n)
{
    char *dest_ptr = (char *)dest;
    const char *source_ptr = (const char *)source;

    if (dest_ptr <= source_ptr || dest_ptr >= source_ptr + n) {
        for (size_t i = 0; i < n; i++)
            dest_ptr[i] = source_ptr[i];
    } else {
        for (size_t i = n; i > 0; i--)
            dest_ptr[i - 1] = source_ptr[i - 1];
    }
    return dest;
}

void *my_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *newptr = malloc(new_size);

    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    if (ptr != NULL) {
        my_memcpy(newptr, ptr, old_size);
        free(ptr);
    }
    return newptr;
}
