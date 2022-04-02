#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
  struct chunk *next;
};
struct chunk *flist = NULL;
int freeChunk = 0;
int mallocChunk = 0;
int totalSize = 0;

void *malloc (size_t size) {
  if (size == 0){
    return NULL;
  }

  void *memory = sbrk(size + sizeof(struct chunk));
  if (memory == (void *) -1) {
    return NULL;
  } else {
    struct chunk* cnk = (struct chunk*) memory;
    cnk -> size = size;
    mallocChunk = cnk ->size;
    return (void*) (cnk + 1);
  }
}

void free(void *memory) {
  if(memory != NULL){
    struct chunk *cnk = (struct chunk*)((struct chunk*)memory -1);
    cnk -> next = flist;
    flist = cnk;
    freeChunk = cnk->size;
  }
  return;
}

void fragstats(void* buffers[], int len) {
  totalSize = freeChunk + mallocChunk;
  
  printf("Total blocks: %d Free: %d Used: %d\n",totalSize,freeChunk,mallocChunk);

  printf("Internal used: total: average: smallest:  largest: \n");
  printf("Extrnal used: total: average: smallest:  largest:  \n");
}

