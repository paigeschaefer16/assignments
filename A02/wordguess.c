#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *remove_white_spaces(char *str){
	int i = 0, j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
          str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return str;
}

int main() {
  FILE *infile = NULL; 
  infile = fopen("words.txt", "r");

  char numStr[64];
  fgets(numStr,64,infile);
  int num = atoi(numStr);

  int upper = num + 1;
  int lower = 2; 
  int count = 0;

  srand((time(0)));
  int randomNum = rand() % 14;

  char line[32];
  
  while (fgets(numStr, sizeof numStr, infile) != NULL){
    if(randomNum == count){
      strcpy(line,numStr);
      break;
    }
    else{
      count = count + 1; 
    }
  }
  

  printf("Welcome to Word Guess!\n");
  int turn = 0;
  char game[32];
  strcpy(game,line);
  
  
  printf("Turn: %d\n",turn);

  for(int i = 0; i < (strlen(game) - 1); i++){
    game[i] = '_';
  }
  

  while(strcmp(line,game) != 0){
    for(int i = 0; i < (strlen(game) - 1); i++){
      printf("%c ",game[i]);
    }
    printf("\n");

    printf("Guess a character: ");
    char guess; 
    scanf(" %c", &guess);
    
    turn = turn + 1; 
    printf("Turn: %d\n",turn);

    for(int i = 0; i < (strlen(game)-1); i++){
      
      if(line[i] == guess){
        game[i] = guess; 
      }
    }
  }
  for(int i = 0; i < (strlen(game) - 1); i++){
      printf("%c ",game[i]);
    }
    printf("\nYou won in %d turns!\n", turn);
  fclose(infile);
  return 0;
}
