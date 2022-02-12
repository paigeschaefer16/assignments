//---------------------------------------------------------------------
// sorted_snackbar.c 
// CS223 - Spring 2022
// Ask the user for a list of snacks and store them in alphabetical order
// Name: Paige Schaefer
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  int quantity;
  float cost;
  struct snack* next;
};

// Insert a new node to a list (implemented as a linked list). 
// The new node should store the given properties
// Param snacks: the first item in the list (NULL if empty)
// Param name: the snack name (max length is 32 characters)
// Param quantity: the snack quantity
// Param cost: the snack cost
// Returns the first item in the list
struct snack* insert_sorted(struct snack* snacks, 
  const char* name, int quantity, float cost) {

  struct snack * new_snack = NULL;

  new_snack = (struct snack *)malloc(sizeof(struct snack));

  if(new_snack == NULL){
    printf("Failed to insert element. Out of memory");
  }
  
  strcpy(new_snack -> name,name);
  new_snack -> cost = cost; 
  new_snack -> quantity = quantity; 

  new_snack -> next = snacks;
  
  return snacks;
}

// Delete (e.g. free) all nodes in the given list of snacks
// Param snacks: the first node in the list (NULL if empty)
void clear(struct snack* snacks) {
  struct snack* temp;

  while (snacks != NULL){
    temp = snacks;
    snacks = snacks -> next;
    free(temp);
  }
}

void print(struct snack* snacks){
  for(struct snack * new_snack = snacks; new_snack != NULL; new_snack->next){
      printf("%s cost: %0.2f quantity: %d \n",snacks->name,snacks->cost,snacks->quantity);
  }
}

int main() {
  int numSnacks;
  printf("Enter a number of snacks: ");
  scanf(" %d",&numSnacks);

  struct snack snackArray[numSnacks];

  for(int i = 0; i < numSnacks; i++){
    printf("Enter a name: ");
    scanf("%s",snackArray[i].name);

    printf("Enter a cost: ");
    scanf("%f",&snackArray[i].cost);

    printf("Enter a quantity: ");
    scanf("%d", &snackArray[i].quantity);
  }
  char *sortedName[numSnacks * 3]; 
  for(int i = 0; i < numSnacks;i++){
    sortedName[i] = snackArray[i].name;
  }
  char temp[numSnacks * 3];

  for(int i=0; i<numSnacks; i++){
    for(int j=0; j<numSnacks-1-i; j++){
      if(strcmp(snackArray[j].name, snackArray[j+1].name) > 0){
        strcpy(temp, snackArray[j].name);
        strcpy(snackArray[j].name, snackArray[j+1].name);
        strcpy(snackArray[j+1].name, temp);
      }
    }
  }
  struct snack* snack[numSnacks];
  for(int i = 0; i < numSnacks;i++){
    snack[i] = insert_sorted(snack[i],snackArray[i].name
                              ,snackArray[i].cost,snackArray[i].quantity);
    print(snack[i]);
    clear(snack[i]);
    
  }
  return 0;
}

