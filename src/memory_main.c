/* Stadium Zero resident code. */
/* C ported from the Stadium 1 decomp: src/memory_main.c. */

#include "global.h"
#include "macros.h"
#include "memory.h"
extern struct MainPool sMemPool;

#include "m2c_macros.h"

void main_pool_init(void* start, void* end);
void* main_pool_alloc_from_pool(u32 size, u32 side);
u32 main_pool_free(void* addr, u32 runBlockFunc);
void* main_pool_alloc_with_func(u32 size, s32 side, s32 arg, AllocateFunc func);
void* main_pool_alloc(u32 size, s32 side);
void* main_pool_realloc(void* addr, size_t size);
u32 main_pool_push_state(u32 arg);
void* main_pool_search(uintptr_t addr, s32* argPtr);
void main_pool_set_func(void* block, s32 arg, AllocateFunc func);
size_t main_pool_get_block_dist(MainPoolBlock* block);
MainPool* main_pool_get_pool(void);

u32 main_pool_get_available(void);

/**
 * Initialize the main memory pool. This pool is conceptually a pair of stacks
 * that grow inward from the left and right. It therefore only supports
 * freeing the object that was most recently allocated from a side.
 */
void main_pool_init(void* start, void* end) {
    sMemPool.start = (void*)(ALIGN16((uintptr_t)start) + 16);
    sMemPool.end = (void*)(ALIGN16((uintptr_t)end - 15) - 16);
    sMemPool.available = (uintptr_t)sMemPool.end - (uintptr_t)sMemPool.start;
    sMemPool.mainState = NULL;

    sMemPool.listHeadL = ((u8*)sMemPool.start - sizeof(MainPoolBlock));
    sMemPool.listHeadL->prev = NULL;
    sMemPool.listHeadL->next = NULL;
    sMemPool.listHeadL->func = NULL;
    sMemPool.listHeadL->arg = '\0';

    sMemPool.listHeadR = sMemPool.end;
    sMemPool.listHeadR->prev = NULL;
    sMemPool.listHeadR->next = NULL;
    sMemPool.listHeadL->func = NULL;
    sMemPool.listHeadL->arg = '\0';

    osCreateMesgQueue(&sMemPool.queue, sMemPool.msgs, ARRAY_COUNT(sMemPool.msgs));
    osSendMesg(&sMemPool.queue, NULL, OS_MESG_NOBLOCK);
}

/**
 * Allocate a block of memory from the pool of given size, and from the
 * specified side of the pool (MEMORY_POOL_LEFT or MEMORY_POOL_RIGHT).
 * If there is not enough space, return NULL.
 */
void* main_pool_alloc_from_pool(u32 size, u32 side) {
    MainPoolBlock* new_list_head;
    void* addr = NULL;

    size = ALIGN16(size) + sizeof(MainPoolBlock);

    // do we have enough space?
    if (size > 0 && size <= sMemPool.available) {
        if (side == MEMORY_POOL_LEFT) {
            // reduce available size.
            sMemPool.available -= size;
            new_list_head = (void*)((uintptr_t)sMemPool.listHeadL + size);
            sMemPool.listHeadL->next = new_list_head;
            new_list_head->prev = sMemPool.listHeadL;
            new_list_head->next = NULL;
            new_list_head->func = NULL;
            new_list_head->arg = '\0';
            addr = ((u8*)sMemPool.listHeadL + sizeof(MainPoolBlock));
            sMemPool.listHeadL = new_list_head;
        } else if (side == MEMORY_POOL_RIGHT) {
            // reduce available size.
            sMemPool.available -= size;
            new_list_head = (void*)((uintptr_t)sMemPool.listHeadR - size);
            sMemPool.listHeadR->prev = new_list_head;
            new_list_head->next = sMemPool.listHeadR;
            new_list_head->prev = NULL;
            new_list_head->func = NULL;
            new_list_head->arg = '\0';
            sMemPool.listHeadR = new_list_head;
            addr = ((u8*)new_list_head + sizeof(MainPoolBlock));
        }
    }
    return addr;
}

/**
 * Free a block of memory that was allocated from the pool. The block must be
 * the most recently allocated block from its end of the pool, otherwise all
 * newer blocks are freed as well.
 * Return the amount of free space left in the pool.
 */
u32 main_pool_free(void* addr, u32 run_block_func) {
    MainPoolBlock* block = (MainPoolBlock*)((u8*)addr - sizeof(MainPoolBlock));
    MainPoolBlock* old_list_head = (MainPoolBlock*)((u8*)addr - sizeof(MainPoolBlock));

    if (old_list_head < sMemPool.listHeadL) {
        do {
            block = (sMemPool.listHeadL = sMemPool.listHeadL->prev);
            if (run_block_func) {
                // TODO: Fakematch
                AllocateFunc func = block->func;
                if (func != 0) {
                    block->func((u8*)block + sizeof(MainPoolBlock), block->arg);
                    // TODO: fake here too
                    if ((!(&sMemPool)) && (!(&sMemPool))) {}  // FAKE
                }
            }
            sMemPool.available += ((uintptr_t)sMemPool.listHeadL->next - (uintptr_t)sMemPool.listHeadL);
            sMemPool.listHeadL->next = NULL;
        } while (old_list_head != sMemPool.listHeadL);
    } else {
        block = sMemPool.listHeadR;
        if (old_list_head >= block && old_list_head >= block) {
            do {
                if (run_block_func) {
                    AllocateFunc func = block->func;
                    if (func != NULL) {
                        func((u8*)block + sizeof(MainPoolBlock), block->arg);
                        block = sMemPool.listHeadR;
                    }
                }
                block = (sMemPool.listHeadR = block->next);
                sMemPool.available += ((uintptr_t)block - (uintptr_t)block->prev);
                block->prev = NULL;
                block = sMemPool.listHeadR;
            } while (old_list_head >= sMemPool.listHeadR);
        }
    }

    return main_pool_get_available();
}

/**
 * Manually allocate and initialize a block given a size and side and its
 * function+arguments.
 */
void* main_pool_alloc_with_func(u32 size, s32 side, s32 arg, AllocateFunc func) {
    MainPoolBlock* addr;

    osRecvMesg(&sMemPool.queue, NULL, OS_MESG_BLOCK);
    addr = main_pool_alloc_from_pool(size, side);
    if (addr != NULL) {
        main_pool_set_func(addr, arg, func);
    }
    osSendMesg(&sMemPool.queue, NULL, OS_MESG_NOBLOCK);

    return addr;
}

/**
 * Same as above but no function/argument is set.
 */
void* main_pool_alloc(u32 size, s32 side) {
    MainPoolBlock* node;

    osRecvMesg(&sMemPool.queue, NULL, OS_MESG_BLOCK);
    node = main_pool_alloc_from_pool(size, side);
    osSendMesg(&sMemPool.queue, NULL, OS_MESG_NOBLOCK);

    return node;
}

M2C_UNK func_80002230(s32, M2C_UNK);                /* extern */
s32 func_8000255C(void);
M2C_UNK func_8004CFB0(M2C_UNK *, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8004D1C0(M2C_UNK *, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_800A94A4;

void func_80002420(s32 arg0) {
    func_8004D1C0(&D_800A94A4, 0, 1);
    func_80002230(arg0, 1);
    func_8004CFB0(&D_800A94A4, 0, 0);
    func_8000255C();
}

/**
 * Resize a block of memory that was allocated from the left side of the pool.
 * If the block is increasing in size, it must be the most recently allocated
 * block from the left side.
 * The block does not move.
 */
void* main_pool_realloc(void* addr, size_t size) {
    MainPoolBlock* prior = (MainPoolBlock*)((u8*)addr - sizeof(MainPoolBlock));
    void* newaddr = NULL;

    osRecvMesg(&sMemPool.queue, NULL, OS_MESG_BLOCK);

    // most recently allocated block?
    if (prior->next == sMemPool.listHeadL) {
        size_t diff = ((uintptr_t)prior->next - (uintptr_t)addr);
        size = ALIGN16(size);

        // is there enough room to expand/realloc the area?
        if (diff >= size || sMemPool.available >= (size - diff)) {
            s32 arg = prior->arg;
            AllocateFunc func = prior->func;
            main_pool_free(addr, FALSE); // do not run the func as we are merely reallocating it.
            newaddr = main_pool_alloc_from_pool(size, MEMORY_POOL_LEFT);
            main_pool_set_func(newaddr, arg, func);
        }
    }
    osSendMesg(&sMemPool.queue, NULL, OS_MESG_NOBLOCK);
    return newaddr;
}

extern s32 D_800A94BC;

s32 func_8000255C(void) {
    return D_800A94BC - 0x10;
}

/**
 * Push pool state, to be restored later. Return the amount of free space left
 * in the pool.
 */
u32 main_pool_push_state(u32 arg) {
    MainPoolState* state;
    MainPoolBlock* listHeadL;
    MainPoolBlock* listHeadR;
    uintptr_t available;

    osRecvMesg(&sMemPool.queue, NULL, OS_MESG_BLOCK);

    // retrieve the space and head pointers.
    available = sMemPool.available;
    listHeadL = sMemPool.listHeadL;
    listHeadR = sMemPool.listHeadR;

    /**
     * We are essentially allocating a block that looks like this:
     *
     * struct AllocatedBlock {
     *     MainPoolBlock block;
     *     struct MainPoolState state; <---- the pointer is pointing here.
     * };
     */
    state = main_pool_alloc_from_pool(sizeof(struct MainPoolState), MEMORY_POOL_LEFT);
    if (state != NULL) {
        /**
         * Why is this line here? What this line is doing is backing the pointer up to the
         * previous block before the state. In the block alloc function, addr is determined
         * by the head plus the size of the block struct, meaning it is returning the
         * pointer to the head.
         */
        ((MainPoolBlock*)((u8*)state - sizeof(MainPoolBlock)))->arg = arg;

        // now that the previous block's argument is set, set the newly allocated state's
        // fields.
        state->prev = sMemPool.mainState;
        state->freeSpace = available;
        state->listHeadL = listHeadL;
        state->listHeadR = listHeadR;

        // add the newly allocated state.
        sMemPool.mainState = state;
    }
    osSendMesg(&sMemPool.queue, NULL, OS_MESG_NOBLOCK);
    return main_pool_get_available();
}

/**
 * Restore pool state from a previous call to main_pool_push_state. Return the
 * amount of free space left in the pool.
 * @unverified Name matches Stadium 1. Comment from Stadium 1.
 */
u32 main_pool_pop_state(u32 arg) {
    MainPoolBlock* argptr;
    MainPoolBlock* block;

    osRecvMesg(&sMemPool.queue, NULL, OS_MESG_BLOCK);

    do {
        block = (MainPoolBlock*)((u8*)sMemPool.mainState - sizeof(struct MainPoolState));

        argptr = sMemPool.listHeadR;
        while ((uintptr_t)argptr < (uintptr_t)sMemPool.mainState->listHeadR) {
            if (argptr->func != NULL) {
                argptr->func((u8*)argptr + sizeof(MainPoolBlock), argptr->arg);
            }
            argptr = argptr->next;
        }

        argptr = sMemPool.listHeadL->prev;
        while ((uintptr_t)argptr >= (uintptr_t)sMemPool.mainState->listHeadL) {
            if (argptr->func != NULL) {
                argptr->func((u8*)argptr + sizeof(MainPoolBlock), argptr->arg);
            }
            argptr = argptr->prev;
        }

        sMemPool.available = sMemPool.mainState->freeSpace;
        sMemPool.listHeadL = sMemPool.mainState->listHeadL;
        sMemPool.listHeadR = sMemPool.mainState->listHeadR;
        sMemPool.mainState = sMemPool.mainState->prev;

        if (arg == '\0') {
            break;
        }
        if (arg == (uintptr_t)block->arg) {
            break;
        }
    } while (sMemPool.mainState != NULL);

    osSendMesg(&sMemPool.queue, NULL, OS_MESG_NOBLOCK);
    return func_8000255C();
}

/*
 * Unused function. Seems at first glance to check for an address within some
 * range, and then return the pointer to its data after the block. Perhaps?
 * Without this being called, its hard to tell the correct context of this
 * function.
 */
void* main_pool_search(uintptr_t addr, s32* arg_ptr) {
    MainPoolBlock* node;
    MainPoolBlock* other_node;

    node = sMemPool.listHeadL->prev;
    while (node != NULL) {
        int isAddrLater = (addr >= ((uintptr_t)((u8*)node + sizeof(MainPoolBlock))));
        other_node = node->next;
        // seems to be checking for an addr within a block region? Since this function
        // is unused, we wont be able to check for the intended context of what could
        // call this function.
        if (isAddrLater && addr < ((uintptr_t)other_node & 0xFFFFFFFF)) {
            if (arg_ptr != NULL) {
                *arg_ptr = node->arg;
            }
            // return the pointer to its block contents.
            return (void*)((u8*)(node) + sizeof(MainPoolBlock));
        }
        node = node->prev;
    }

    // we've searched thr prev linked list. Now lets go through the next linked list.
    node = sMemPool.listHeadR;
    other_node = node->next;
    while (other_node != NULL) {
        int isAddrLater = (addr >= ((uintptr_t)((u8*)node + sizeof(MainPoolBlock))));
        MainPoolBlock* new_var = other_node; // bit of a fakematch to force the move reload.
        // same as above.
        if (isAddrLater && (addr < ((uintptr_t)new_var & 0xFFFFFFFF))) {
            if (arg_ptr != NULL) {
                *arg_ptr = node->arg;
            }
            // return the pointer to its block contents.
            return (void*)((u8*)(node) + sizeof(MainPoolBlock));
        }
        other_node = (node = other_node)->next;
    }

    return NULL;
}

/**
 * Set the block function and its argument(s) for a given block.
 */
void main_pool_set_func(void* block, s32 arg, AllocateFunc func) {
    MainPoolBlock* node = (void*)((uintptr_t)block - sizeof(MainPoolBlock));
    node->func = func;
    node->arg = arg;
}

/**
 * Get the distance offset from the block's state listHeadL pointer to the current block.
 */
size_t main_pool_get_block_dist(MainPoolBlock* block) {
    MainPoolState* state = ((u8*)block - sizeof(MainPoolBlock));

    return (size_t)((uintptr_t)state->listHeadL - (uintptr_t)block);
}

/**
 * Return the pointer to the static memory pool area.
 */
MainPool* main_pool_get_pool(void) {
    return &sMemPool;
}
