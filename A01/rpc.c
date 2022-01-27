#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void game(int rounds){
    int AIScore = 0;
    int playerScore = 0;
    for(int i = 0; i < rounds; i++){
    
        printf("Which do you choose? rock, paper, or scissors? ");
        char input[50];
        scanf("%s",input);
        printf("\n");

        int inputSum = 0;
        for (int j = 0; input[j] != '\0'; j++){
            inputSum += input[j];
        }

        int randomNum;
        srand(time(0));
        randomNum = (rand() % (3-0+1))+0;
 
        int gamePlay; 
        while(randomNum < 4){
            if(randomNum == 0 || randomNum == 2 || randomNum == 3){
                break;
            }
            else{
                srand(time(0));
                randomNum = (rand() % (3-0+1))+0; 
            }
        }

        if(randomNum == 0){
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
      
        if(inputSum == 431 || inputSum == 536 || inputSum == 889){
           if(gamePlay == -1 || gamePlay == 3 || gamePlay == -2){
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
    if(AIScore > playerScore){
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

 

