#ifndef BITFIELD_H
#define BITFIELD_H

#include "../core/core.h"
#include "../type/Str.h"

typedef struct BitField BitField;

struct BitField
{
    U8 *    bytes;
    I64     n_bytes;
};

static inline BitField BitField_new(I64 n_bits)
{
    I64 n_bytes;

    n_bytes = n_bits % BPB == 0 ? n_bits / BPB : n_bits / BPB + 1;

    return (BitField) {(U8 *)mem_zero(n_bytes), n_bytes};
}

static inline I64 BitField_n_bytes(const BitField * field)
{
    return field->n_bytes;
}

static inline void BitField_set(BitField * field, I64 bit)
{
    field->bytes[bit / BPB] |= (1 << (bit % BPB));
}

static inline bool Bitfield_bit(const BitField * field, I64 bit)
{
    return field->bytes[bit / BPB] & (1 << (bit % BPB));
}

static inline void BitField_destroy(BitField * field)
{
    mem_destroy(field->bytes);
}

Str BitField_to_Str(const BitField * field);

#endif