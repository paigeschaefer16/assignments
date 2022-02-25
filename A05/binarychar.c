#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int input;
  printf("Enter 8 bits: ");
  scanf(" %d",&input);

  int decimal = 0;
  int i = 0;

  while(input != 0){
    int x = input % 10;
    decimal += x << i;
    input = input/10;
    i++;
  }
  char output = (char)decimal;
  printf("Your character is: %c\n",output);

  return 0;
}
