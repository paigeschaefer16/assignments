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
    exit(1);
  }
  
  strcpy(new_snack -> name,name);
  new_snack -> cost = cost; 
  new_snack -> quantity = quantity; 

  new_snack -> next = NULL;
  if(snacks == NULL){
    snacks = new_snack;
  }
  else if(strcmp(new_snack->name,snacks->name) < 0){
    new_snack->next = snacks;
    snacks = new_snack;
  }
  else{
    struct snack * current = snacks;
    while(current->next != NULL){
      if(strcmp(current->next->name,new_snack->name)> 0){
        new_snack->next = current->next;
        current->next = new_snack;
        break;
      }  
      current = current->next;
    }
    if(strcmp(current->name,new_snack->name)< 0){
      current->next = new_snack;
    }
    
  }

  
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
  printf("\n");
  for(struct snack * new_snack = snacks; new_snack != NULL; new_snack = new_snack->next){
      printf("%s\t cost: $%0.2f \t quantity: %d \n",new_snack->name,new_snack->cost,new_snack->quantity);
  }
}

int main() {
  int numSnacks;
  printf("Enter a number of snacks: ");
  scanf(" %d",&numSnacks);

  struct snack *snackPointer = NULL;

  char tempName[32];
  int tempQuantity;
  float tempCost;

  for(int i = 0; i < numSnacks; i++){
    printf("Enter a name: ");
    scanf("%s",tempName);

    printf("Enter a cost: ");
    scanf("%f",&tempCost);

    printf("Enter a quantity: ");
    scanf("%d",&tempQuantity);
    snackPointer = insert_sorted(snackPointer,tempName,tempQuantity,tempCost);
  }
  printf("\n");
  printf("Welcome to Sorted Sally's Snack Bar.\n");
  print(snackPointer);
  

  
  return 0;
}

