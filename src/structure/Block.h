#ifndef BLOCK_H
#define BLOCK_H

#include "../core/mem.h"
#include <string.h>

typedef struct Block Block;

struct Block
{
    void *  data;
    I64     size;
};

static inline I64 Block_size(const Block * block)
{
    return block->size;
}

static inline void * Block_data(const Block * block)
{
    return block->data;
}

static inline Block Block_new(I64 size)
{
    return (Block) {mem_allocate(size), size};
}

static inline Block Block_zero(I64 size)
{
    return (Block) {mem_zero(size), size};
}

static inline Block Block_from_ptr(const void * ptr, I64 size)
{
    Block block;

    block = Block_new(size);
    memcpy(block.data, ptr, size);

    return block;
}

static inline void Block_destroy(Block * block)
{
    mem_destroy(block->data);
}

static inline void * Block_get(const Block * block, I64 offset)
{
    return block->data + offset;
}

static inline void Block_set_ptr(Block * block, I64 offset, const void * ptr, Put put)
{
    put(Block_get(block, offset), ptr);
}

#define Block_set(block_ptr, offset, value) (* (typeof(value) *)Block_get((block_ptr), (offset)) = value)

static inline void Block_swap(Block * block, I64 lhs, I64 rhs, Swap swap)
{
    swap(Block_get(block, lhs), Block_get(block, rhs));
}

static inline void Block_extend(Block * block, I64 extra_size)
{
    block->data = mem_extend(block->data, block->size, extra_size);
    block->size += extra_size;
}

#endif