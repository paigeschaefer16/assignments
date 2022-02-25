#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char input[4];
  printf("Enter 4 characters: ");
  scanf(" %s",input);

  unsigned int output[4];
  unsigned int total = 0; 
  

  for(int i = 3; i >= 0;i--){
    output[i] = (int)input[i];
    if(i == 2){
      output[i] = output[i] << 8;
    }
    if(i == 1){
      output[i] = output[i] << 16;
    }
    if(i == 0){
      output[i] = output[i] << 24;
    }
  
    printf("Debug: %c = 0x%08X\n",input[i],output[i]);
    total = total + output[i];
  }

  printf("Your number is: %u (0x%08x)\n",total,total);
  return 0;
}
