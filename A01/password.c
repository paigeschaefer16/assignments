#include <stdio.h>
#include <string.h>

int main() {
	char password[50];
	printf("Enter a word: ");
	
	scanf("%s",password);


	for (int i = 0; i < strlen(password);i++){
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

	printf("Your bad password is %s\n",password);
  	return 0;
}
