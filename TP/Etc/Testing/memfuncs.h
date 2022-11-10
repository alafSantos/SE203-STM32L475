#ifndef MEMFUNCS_H
#define MEMFUNCS_H

    #include <stdlib.h>
    #include <stdint.h>
    #include <stddef.h>
    #include <string.h>

    /* 
        The memcpy() function copies n bytes from memory area src to memory area dest.
        The memory areas must not overlap.  Use memmove(3) if the memory areas do overlap. 
    */
    void *memcpy(void *dest, const void *src, size_t n);

    /* 
        The  memmove() function copies n bytes from memory area src to memory area dest.
        The memory areas may overlap: copying takes place as though the bytes in src are first copied 
        into a temporary array that does not overlap src or dest, and the bytes are then copied from the temporary array to dest.
    */
    void *memmove(void *dest, const void *src, size_t n);

    /* The memset() function fills the first n bytes of the memory area pointed to by s with the constant byte c. */
    void *memset(void *s, int c, size_t n);

    /* The memcmp() function compares the first n bytes (each interpreted as unsigned char) of the memory areas s1 and s2. */
    int memcmp(const void *s1, const void *s2, size_t n);

#endif