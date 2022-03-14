/*
 * Author: Paige Schaefer 
 * Purpose: To create a snack bar menu using structs 
 * Language:  C
 * Created: January 2022
 */

#include <stdio.h>
#include <string.h>

struct Snacks{				
	char snackType[50];
	float cost;
	int quantity; 
};

int main() {
	printf("Welcome to Steven Struct's Snack Bar.\n"); 
	printf("How much money do you have? ");
	
	float userMoney;						
	scanf("%f",&userMoney);
	printf("\n");
	
	struct Snacks snackArray[3];


	strcpy(snackArray[0].snackType, "Coco Puffs");
	snackArray[0].cost = 1.50;
	snackArray[0].quantity = 4;

	strcpy(snackArray[1].snackType, "Manchego cheese");
    snackArray[1].cost = 15.50;
    snackArray[1].quantity = 6;

	strcpy(snackArray[2].snackType, "Magic beans");
    snackArray[2].cost = 0.50;
    snackArray[2].quantity = 0;


	printf("0) %s \t\t cost: $%.2f \t quantity: %d \n",
				snackArray[0].snackType,snackArray[0].cost,snackArray[0].quantity);
	printf("1) %s \t cost: $%.2f \t quantity: %d \n",
				snackArray[1].snackType,snackArray[1].cost,snackArray[1].quantity);
	printf("2) %s \t\t cost: $%.2f \t quantity: %d \n",
				 snackArray[2].snackType, snackArray[2].cost, snackArray[2].quantity);
	
	printf("What snack would you like to buy? [0,1,2] ");
	
	int snackOption;				
	scanf("%d",&snackOption);
	printf("\n");
	
	if(snackOption == 0){						
		if( snackArray[0].cost > userMoney){
			printf("You can't afford it!\n");
		}
		else if( snackArray[0].quantity == 0){
			printf("Sorry, we are out of %s\n", snackArray[0].snackType);
		}
		else{
			printf("You bought %s\n", snackArray[0].snackType);
			userMoney = userMoney -  snackArray[0].cost;
			printf("You have $%0.2f left\n",userMoney);
		}
	}
	
	if(snackOption == 1){
		if(snackArray[1].cost > userMoney){
            printf("You can't afford it!\n");
        }
        else if(snackArray[1].quantity == 0){
            printf("Sorry, we are out of %s\n",snackArray[1].snackType);
        }
        else{
            printf("You bought %s\n",snackArray[1].snackType);
                userMoney = userMoney - snackArray[1].cost;
                printf("You have $%0.2f left\n",userMoney);
            }
    }
	if(snackOption == 2){
		if(snackArray[2].cost > userMoney){
            printf("You can't afford it!\n");
        }
        else if(snackArray[2].quantity == 0){
            printf("Sorry, we are out of %s\n",snackArray[2].snackType);
        }
        else{
            printf("You bought %s\n",snackArray[2].snackType);
            userMoney = userMoney - snackArray[2].cost;
        	printf("You have $%0.2f left\n",userMoney);
        }
    }
	return 0;
}
