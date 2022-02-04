#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 


int main() {
  printf("Enter a word: "); 
  char input[32];
  scanf("%s",input);
  printf("Enter a count: "); 
  int count; 
  scanf("%d", &count);

  char *ret = malloc (strlen (input) * count + count);

  strcpy (ret, input);
  while (--count > 0){
    strcat (ret, input);
  }
  if(ret != NULL){
    printf("Your word is %s\n",ret);
  }
  else{
    printf("Cannot allocate new string. Exiting...");
    exit(-1);
  }
  free(ret);
  return 0;
}
