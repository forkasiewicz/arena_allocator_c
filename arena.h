#include "utils.h"

#define KiB(n) ((u64)(n) << 10)
#define MiB(n) ((u64)(n) << 20)
#define GiB(n) ((u64)(n) << 30)

#define MEM_ALIGN(s, p) (((s) + (p) - 1) & ~((p) - 1))
#define ARENA_ALIGNMENT (sizeof(void *))

typedef struct {
  u8 *memory;
  u64 size;
  u64 offset;
} mem_arena;

extern mem_arena *arena_create(u64 size);
extern void arena_destroy(mem_arena *arena);
extern void *arena_alloc(mem_arena *arena, u64 size);
extern void arena_free(mem_arena *arena, u64 size);
