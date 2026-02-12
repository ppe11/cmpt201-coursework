#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next,
                      int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *current = free_list_ptr;

  while (current != NULL) {
    if (current->size >= size) {
      return current->id;
    }
    current = current->next;
  }

  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *current = free_list_ptr;
  uint64_t smallest_size = UINT64_MAX;
  int best_fit_id = -1;

  while (current != NULL) {
    if (current->size >= size && current->size < smallest_size) {
      smallest_size = current->size;
      best_fit_id = current->id;
    }
    current = current->next;
  }

  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *current = free_list_ptr;
  uint64_t largest_size = 0;
  int worst_fit_id = -1;

  while (current != NULL) {
    if (current->size >= size && current->size > largest_size) {
      largest_size = current->size;
      worst_fit_id = current->id;
    }
    current = current->next;
  }

  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);

  free(free_block1);
  free(free_block2);
  free(free_block3);
  free(free_block4);
  free(free_block5);

  return 0;
}
/*
============================================================
Part 2: Coalescing Contiguous Free Blocks
============================================================

Assumptions:
- The free list is already coalesced.
- A single newly freed block "new_block" is given.
- The free list is sorted by memory address.

Algorithm:

1. Traverse the free list to find the correct position
   where new_block should be inserted (keep list sorted by address).

2. Insert new_block into the linked list.

3. Check if the block BEFORE new_block is contiguous:
      if (address_of_previous_block + previous_block->size
          == address_of_new_block)
      then:
          previous_block->size += new_block->size
          previous_block->next = new_block->next
          new_block = previous_block

4. Check if the block AFTER new_block is contiguous:
      if (address_of_new_block + new_block->size
          == address_of_next_block)
      then:
          new_block->size += next_block->size
          new_block->next = next_block->next

5. Done.
*/
