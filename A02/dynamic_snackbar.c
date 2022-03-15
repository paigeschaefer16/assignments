#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  float cost;
  int quantity;
};

int main() {
  int numSnacks; 
  printf("Enter a number of snacks: ");
  scanf("%d", &numSnacks);

  struct snack *snackArray = malloc(sizeof *snackArray * numSnacks);
  
  for(int i = 0; i < numSnacks; i++){
    printf("Enter a name: ");
    scanf("%s",snackArray[i].name);
    
    printf("Enter a cost: ");
    scanf("%f",&snackArray[i].cost);

    printf("Enter a quantity: ");
    scanf("%d", &snackArray[i].quantity);
  }

  for(int i = 0; i < numSnacks; i++){
    printf("%d) %s \t\t cost: $%.2f \t quantity: %d \n",i,snackArray[i].name,
      snackArray[i].cost,snackArray[i].quantity);

  }

  free(snackArray);

  return 0;
}

