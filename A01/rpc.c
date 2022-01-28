/*
 * Author: Paige Schaefer 
 * Purpose: Play rock, paper scisscors with AI 
 * Language:  C
 * Created: January 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void game(int rounds){
    int AIScore = 0;
    int playerScore = 0;
    for(int i = 0; i < rounds; i++){                /* iterate for each round */
    
        printf("Which do you choose? rock, paper, or scissors? ");
        char input[50];                                 /* user input */
        scanf("%s",input);
        printf("\n");

        int inputSum = 0;                               /* recongnize bad input*/
        for (int j = 0; input[j] != '\0'; j++){
            inputSum += input[j];
        }

        int randomNum;                                  /* random number generator*/
        srand(time(0));
        randomNum = (rand() % (3-0+1))+0;
 
        int gamePlay;       

        while(randomNum < 4){                               /* edit generator*/
            if(randomNum == 0 || randomNum == 2 || randomNum == 3){
                break;
            }
            else{
                srand(time(0));
                randomNum = (rand() % (3-0+1))+0; 
            }
        }

        if(randomNum == 0){                             /* AI input*/
            char AI[50] = "rock";
            printf("AI chose %s\n", AI);
            gamePlay = strcmp(AI,input);
        }
        else if(randomNum == 2){
            char AI[50] = "paper";
            printf("AI chose %s\n", AI);
            gamePlay = strcmp(AI,input);
        }
        else if (randomNum == 3){
            char AI[50] = "scissors";
            printf("AI chose %s\n", AI);
            gamePlay = strcmp(AI,input);
        }
      
        if(inputSum == 431 || inputSum == 536 || inputSum == 889){      /* regonize bad input*/
           if(gamePlay == -1 || gamePlay == 3 || gamePlay == -2){       /* determine score of round */
                AIScore = AIScore + 1;
            }
            else if(gamePlay == -3 || gamePlay == 2 || gamePlay == 1){
                playerScore = playerScore + 1;
             }
        }
        else{
           printf("You entered an invalid choice: %s\n", input); 
        }
        
        
        printf("AI Score: %d , Player Score: %d\n",AIScore, playerScore);
    }
    if(AIScore > playerScore){                                  /* overall score*/
        printf("AI wins!\n");
    }
    else if(AIScore < playerScore){
        printf("Player wins!\n");
    }
    else{
        printf("It's a tie!\n");
    }

}
int main() {
    printf("Welcome to Rock, Paper, Scissors!\n");
    printf("How many rounds do you want play? ");

    int rounds;
    scanf("%d",&rounds);

    game(rounds);

    return 0;
}

 

