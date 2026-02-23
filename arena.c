#include "arena.h"
#include "utils.h"
#include <stdlib.h>

mem_arena *arena_create(u64 size) {
  mem_arena *arena = (mem_arena *)malloc(sizeof(mem_arena));
  ASSERT(arena, "failed to initialize arena\n");

  arena->memory = (u8 *)malloc(size);
  ASSERT(arena->memory, "failed to allocate arena memory\n");

  arena->size = size;
  arena->offset = 0;

  return arena;
}

void arena_destroy(mem_arena *restrict arena) {
  free(arena->memory);
  free(arena);
}

void *arena_alloc(mem_arena *restrict arena, u64 size) {
  u64 aligned = MEM_ALIGN(size, ARENA_ALIGNMENT);
  ASSERT(arena->offset + aligned <= arena->size, "arena ran out of memory\n");
  void *mem_ptr = arena->memory + arena->offset;
  arena->offset += aligned;

  return mem_ptr;
}

void arena_free(mem_arena *restrict arena, u64 size) {
  u64 aligned = MEM_ALIGN(size, ARENA_ALIGNMENT);
  ASSERT(arena->offset >= aligned, "arena pop out of bounds\n");
  arena->offset -= aligned;
}
