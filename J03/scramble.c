#include <stdio.h>

int main() {
  char input[1000];

  printf("Please enter a phrase: ");
  scanf("%s",input);

  unsigned int lbit;
  unsigned int rbit; 

  for(int i = 0; i < 1000; i++){
    lbit = input[i] & 1 << 2;
    rbit = input[i] & 1 << 1;

    if((lbit  >> 1) == rbit){
      lbit = lbit >> 1;
      rbit = rbit << 1;
      input[i] = input[i] | lbit;
      input[i] = input[i] | rbit;
    }
    else{
      input[i] = input[i] | (lbit ^ (1 << 2));
      input[i] = input[i] | (rbit ^ (1 << 1));
    }
  }
 
  printf("%s\n",input);

  return 0;
}
