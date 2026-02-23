#include "arena.h"
#include "utils.h"
#include <stdlib.h>
#include <time.h>

typedef struct __attribute__((__packed__)) {
  u32 cols, rows;
  f32 *data;
} mat;

static mat *mat_create(mem_arena *restrict arena, u32 cols, u32 rows);
static inline mat *mat_mul(mem_arena *arena, mat *restrict mat_a,
                           mat *restrict mat_b);
static inline f32 mat_sum(mat *restrict matrix);

i32 main(void) {
  srand(time(NULL));

  mem_arena *arena = arena_create(MiB(1));

  mat *a = mat_create(arena, 10, 10);
  mat *b = mat_create(arena, 10, 10);
  for (u32 i = 0; i < a->cols * a->rows; i++) {
    a->data[i] = (f32)rand() / (f32)RAND_MAX;
    b->data[i] = (f32)rand() / (f32)RAND_MAX;
  }

  mat *c = mat_mul(arena, a, b);

  f32 sum = mat_sum(c);

  printf("%f\n", sum);

  arena_destroy(arena);
  return EXIT_SUCCESS;
}

static mat *mat_create(mem_arena *restrict arena, u32 cols, u32 rows) {
  mat *matrix = arena_alloc(arena, sizeof(mat) + sizeof(f32) * rows * cols);
  matrix->cols = cols;
  matrix->rows = rows;
  matrix->data = (f32 *)(matrix + 1);

  for (u32 i = 0; i < cols * rows; i++) {
    matrix->data[i] = 0.0f;
  }

  return matrix;
}

static inline f32 mat_sum(mat *restrict matrix) {
  f32 sum = 0.0f;

  for (u32 i = 0; i < matrix->cols * matrix->rows; i++) {
    sum += matrix->data[i];
  }

  return sum;
}

static inline mat *mat_mul(mem_arena *arena, mat *restrict mat_a,
                           mat *restrict mat_b) {
  mat *mat_c = mat_create(arena, mat_b->cols, mat_a->rows);

  for (u32 i = 0; i < mat_c->rows * mat_c->cols; i++) {
    mat_c->data[i] = 0.0f;
  }

  for (u32 i = 0; i < mat_a->rows; i++) {
    for (u32 j = 0; j < mat_b->cols; j++) {
      for (u32 k = 0; k < mat_a->cols; k++) {
        mat_c->data[i * mat_c->cols + j] +=
            mat_a->data[i * mat_a->cols + k] * mat_b->data[k * mat_b->cols + j];
      }
    }
  }

  return mat_c;
}
