/*
** EPITECH PROJECT, 2024
** RobotFactory
** File description:
** append
*/

#include "basics.h"

void **append_ptr(void ***ptr, void *entity, int *len)
{
    int len_ptr = my_arraylen(*ptr);

    if (*ptr == NULL) {
        *ptr = smalloc(sizeof(void *) * 2);
    } else {
        *ptr = my_realloc(*ptr, sizeof(void *) * (len_ptr + 1),
            sizeof(void *) * (len_ptr + 2));
    }
    if (*ptr == NULL)
        return NULL;
    (*ptr)[len_ptr] = entity;
        (*ptr)[len_ptr + 1] = NULL;
    if (len != NULL)
        *len = len_ptr + 1;
    return *ptr;
}

void **remove_ptr(void ***ptr, int index, int *len)
{
    int len_ptr = my_arraylen(*ptr);

    if (*ptr == NULL) {
        my_fputstr("Remove failed, Ptr is empty\n", 2);
        return *ptr;
    }
    if (index > len_ptr - 1) {
        my_fputstr("Wrong index risk of overflow\n", 2);
        return *ptr;
    }
    free((*ptr)[index]);
    for (int i = index; (*ptr)[i] != NULL; i++)
        (*ptr)[i] = (*ptr)[i + 1];
    *ptr = my_realloc(*ptr, sizeof(void *) * (len_ptr + 1),
        sizeof(void *) * (len_ptr));
    if (len != NULL)
        *len = len_ptr - 1;
    return *ptr;
}
