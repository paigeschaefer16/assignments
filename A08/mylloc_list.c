#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
  int currentlyUsed; 
  struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc (size_t size) {
  if (size == 0){
    return NULL;
  }

  struct chunk *next = flist; 
  struct chunk *prev = NULL; 

  while(next != NULL){
    if (next->size >= size) {
			if(prev != NULL) {
				prev->next = next->next;
			} 
      else {
				flist = next->next;
			}
			next->currentlyUsed += size;
			return (void*)(next + 1); 
		} 
    else {
			prev = next;
			next = next->next; 
		}

  }

  void *memory = sbrk(size + sizeof(struct chunk));
  if (memory == (void *) -1) {
    return NULL;
  } 
  else {
    struct chunk* cnk = (struct chunk*) memory;
    cnk -> size = size;
    cnk -> currentlyUsed = size; 
    return (void*) (cnk + 1);
  }
}

void free(void *memory) {
  if(memory != NULL){
    struct chunk *cnk = (struct chunk*)((struct chunk*)memory -1);
    cnk -> next = flist;
    cnk -> currentlyUsed = 0;
    flist = cnk; 
  }
  return;
}

void fragstats(void* buffers[], int len) {
  int numUsed = 0;
  int numFragmented = 0; 
  int smallestFrag = - 1; 
  int largestFrag = 0; 

  for(int i = 0; i < len; i++){
    if(buffers[i] != NULL){
      numUsed++;
      struct chunk *cnk = (struct chunk*) ((struct chunk*) buffers[i] -1);
      int unUsed = cnk-> size - cnk->currentlyUsed;
      numFragmented += unUsed; 
      if(smallestFrag < 0 || unUsed < smallestFrag){
        smallestFrag = unUsed; 
      }
      if(unUsed > largestFrag){
        largestFrag = unUsed; 
      }
    }
  }

  float averageFrag = numUsed > 0? numFragmented/numUsed : 0;
  int numFree = 0;
  int smallest = -1;
  int largest = 0; 
  int total = 0;

  struct chunk* current = flist;
  while(current != NULL){
    numFree++; 
    if(smallest < 0 || current ->size < smallest){
      smallest = current -> size; 
    }
    if(current -> size > largest){
      largest = current -> size; 
    }
    total += current -> size; 
    current = current -> next; 
  }
  float average = numFree > 0? total/numFree : 0; 
  printf("Total Blocks: %d Free: %d Used: %d\n",numUsed+numFree,numFree,numUsed);
  printf("Internal unused: total: %d average: %0.1f smallest: %d largest: %d\n",
              numFragmented,averageFrag,smallestFrag,largestFrag);
  printf("External unused: total: %d average: %0.1f smallest: %d largest: %d\n",
              total,average,smallest,largest);
}

