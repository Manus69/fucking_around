#ifndef DEF_H
#define DEF_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define OK              (1337)
#define NOT_OK          (-1)
#define INDEX_FW        (32)

typedef uint_fast64_t   U64;
typedef uint_fast32_t   U32;
typedef int_fast64_t    I64;
typedef int_fast32_t    I32;
typedef void *          Ptr;
typedef void (* Swap)   (void *, void *);
typedef void (* Set)    (void *, const void *);
typedef I64  (* Cmp)    (const void *, const void *);
typedef I64  (* Hash)   (const void *);



#endif