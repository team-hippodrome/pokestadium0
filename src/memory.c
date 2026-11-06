/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/memory.c. */

#include "global.h"
#include "memory.h"

MemoryPool* mem_pool_try_init(u32 size, s32 side);
MainPool* mem_pool_init(MainPool* pool, s32 size);
void* mem_pool_alloc(MemoryPool* node, s32 size);

/**
 * Allocate a memory pool from the main pool. This pool supports arbitrary
 * order for allocation/freeing.
 * Return NULL if there is not enough space in the main pool.
 */
MemoryPool* mem_pool_try_init(u32 size, s32 side) {
    MainPoolBlock* block;
    MemoryPool* ret;

    size = ALIGN4(size);
    block = main_pool_alloc(size, side);
    if (block != NULL) {
        ret = mem_pool_init(block, size);
    }
    return ret; //! UB: Uninitialized return if the earlier call is not done.
}

/**
 * Perform the actual mem pool init. This is called by the earlier function.
 * In earlier EAD titles, this was part of mem_pool_try_init.
 */
// TODO: This function is strange, it cant be using MemoryPool, as it allocates
// more variables than the MemoryPool struct, and it doesnt line up. Whats going
// on with these structs?
MainPool* mem_pool_init(MainPool* pool, s32 size) {
    s32 aligned_size =
        ALIGN4(size - 3) - 0x28; // whats the deal with 0x28? this size doesnt match any known pool struct.
    void* listHeadL = &pool->listHeadL;

    pool->available = aligned_size;
    pool->start = listHeadL;
    pool->end = listHeadL;
    pool->listHeadL = NULL;
    pool->listHeadR = aligned_size;
    osCreateMesgQueue(&pool->queue, &pool->msgs[0], 1);
    osSendMesg(&pool->queue, NULL, 0);
    return pool;
}

/**
 * Allocate from a memory pool. Return NULL if there is not enough space.
 */
void* mem_pool_alloc(MemoryPool* node, s32 size) {
    struct MemoryBlock* freeBlock;
    void* addr;

    osRecvMesg(&node->queue, 0, 1);

    addr = NULL;
    size = ALIGN4(size) + sizeof(struct MemoryBlock);
    freeBlock = &node->freeList;

    while (freeBlock->next != NULL) {
        if (freeBlock->next->size >= size) {
            addr = (u8*)freeBlock->next + sizeof(struct MemoryBlock); // get data after header
            if (freeBlock->next->size - size <= sizeof(struct MemoryBlock)) {
                freeBlock->next = freeBlock->next->next;
            } else {
                struct MemoryBlock* newBlock = (struct MemoryBlock*)((u8*)freeBlock->next + size);
                newBlock->size = freeBlock->next->size - size; // set size
                newBlock->next = freeBlock->next->next;
                freeBlock->next->size = size; // set size
                freeBlock->next = newBlock;
            }
            break;
        }
        freeBlock = freeBlock->next;
    }
    osSendMesg(&node->queue, 0, 0);
    return addr;
}

void func_800029D0(MemoryPool* pool, void* addr) {
    struct MemoryBlock* block;
    struct MemoryBlock* freeList;

    osRecvMesg(&pool->queue, NULL, 1);
    block = (struct MemoryBlock*)((u8*)addr - sizeof(struct MemoryBlock));
    freeList = pool->freeList.next;
    if (pool->freeList.next == NULL) {
        pool->freeList.next = block;
        block->next = NULL;
    } else if (block < pool->freeList.next) {
        if ((u32)pool->freeList.next == ((u32)block + (u32)block->size)) {
            block->size += ((u32)freeList->size);
            block->next = freeList->next;
            pool->freeList.next = block;
        } else {
            block->next = pool->freeList.next;
            pool->freeList.next = block;
        }
    } else {
        while (freeList->next != NULL) {
            if (freeList < block && block < freeList->next) {
                break;
            }
            freeList = freeList->next;
        }
        if (((u32)freeList + (u32)freeList->size) == (u32)block) {
            freeList->size += block->size;
            block = freeList;
        } else {
            block->next = freeList->next;
            freeList->next = block;
        }
        if (block->next != NULL && (u32)block->next == ((u32)block + (u32)block->size)) {
            block->size = (u32)block->size + (u32)block->next->size;
            block->next = block->next->next;
        }
    }
    osSendMesg(&pool->queue, NULL, 0);
}
