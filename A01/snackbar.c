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
	
	struct Snacks Snack0;
	struct Snacks Snack1;
	struct Snacks Snack2;

	strcpy(Snack0.snackType, "Coco Puffs");
	Snack0.cost = 1.50;
	Snack0.quantity = 4;

	strcpy(Snack1.snackType, "Manchego cheese");
        Snack1.cost = 15.50;
        Snack1.quantity = 6;

	strcpy(Snack2.snackType, "Magic beans");
        Snack2.cost = 0.50;
        Snack2.quantity = 0;

	printf("0) %s \t\t cost: $%.2f \t quantity: %d \n",Snack0.snackType,Snack0.cost,Snack0.quantity);
	printf("1) %s \t cost: $%.2f \t quantity: %d \n",Snack1.snackType,Snack1.cost,Snack1.quantity);
	printf("2) %s \t\t cost: $%.2f \t quantity: %d \n",Snack2.snackType,Snack2.cost,Snack2.quantity);
	
	printf("What snack would you like to buy? [0,1,2] ");
	
	int snackOption;
	scanf("%d",&snackOption);
	printf("\n");
	
	if(snackOption == 0){
		if(Snack0.cost > userMoney){
			printf("You can't afford it!\n");
		}
		else if(Snack0.quantity == 0){
			printf("Sorry, we are out of %s\n",Snack0.snackType);
		}
		else{
			printf("You bought %s\n",Snack0.snackType);
			userMoney = userMoney - Snack0.cost;
			printf("You have $%0.2f left\n",userMoney);
		}
	}
	
	 if(snackOption == 1){
		if(Snack1.cost > userMoney){
                        printf("You can't afford it!\n");
                }
                else if(Snack1.quantity == 0){
                        printf("Sorry, we are out of %s\n",Snack1.snackType);
                }
                else{
                        printf("You bought %s\n",Snack1.snackType);
                        userMoney = userMoney - Snack1.cost;
                        printf("You have $%0.2f left\n",userMoney);
                }
        }
	 if(snackOption == 2){
		if(Snack2.cost > userMoney){
                        printf("You can't afford it!\n");
                }
                else if(Snack2.quantity == 0){
                        printf("Sorry, we are out of %s\n",Snack2.snackType);
                }
                else{
                        printf("You bought %s\n",Snack2.snackType);
                        userMoney = userMoney - Snack2.cost;
                        printf("You have $%0.2f left\n",userMoney);
                }
        }
	return 0;
}
