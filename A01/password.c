/*
 * Author: Paige Schaefer 
 * Purpose: To create a bad password 
 * Language:  C
 * Created: January 2022
 */

#include <stdio.h>
#include <string.h>

int main() {
	char password[50];
	printf("Enter a word: ");
	
	scanf("%s",password);			/* reading password */


	for (int i = 0; i < strlen(password);i++){		/* making bad password */
		if(password[i] == 'e'){
			password[i] = '3';
		}
		if(password[i] == 'l'){
			 password[i] = '1';
                }
		if(password[i] == 'a'){
                        password[i] = '@';
                }

	}

	printf("Your bad password is %s\n",password);	/* printing bad password */
  	return 0;
}
