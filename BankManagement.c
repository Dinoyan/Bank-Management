#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

struct Customer {
	char firstName[64];
	char lastName[64];
	int uniqueCustomerId;
	int password;
}

struct Admin {
	char firstName[64];
	char lastName[64];
	int uniqueAdminId;
	int password;
}

void admin(){
	printf("%s\n", );

}

void customer(){

}

void createAccount(int userType){
	char firstName[64];
	char lastName[64];
	int password;
	printf("Enter your first name: ");
	scanf("%s", firstName);
	printf("Enter your last name: ");
	scanf("%s", lastName);
	printf("Enter your new password\n");
	scanf("%d", password);

	if (userType = 2){
		FILE *customerfile; 
      
    	// open file for writing 
    	customerfile = fopen ("customer.dat", "w"); 
    	if (customerfile == NULL) { 
        	fprintf(stderr, "\nError opend file\n"); 
        	exit (1); 
    	} 
  
   	 	struct Customer customer = {firstName, lastName, password}; 
      
    	// write struct to file 
    	fwrite (&customer, sizeof(struct Customer), 1, customerfile); 
      
    	if(fwrite != 0) {
        	printf("contents to file written successfully !\n"); 
    	}
    	else {
        	printf("error writing file !\n"); 
    	}
  
    	// close file 
    	fclose (customerfile); 
	} else {

	}
	

}

int authenticate(int userType, int accNum, int password){
	int authenticated = 0;

	return authenticated;
}

int main(){
	int userType, accNum, password;
	int selected = 0;

	printf("Welcome to Dinoyan's Bank\n");
	printf("Select your account type\n");
	printf("1: Admin \n 2: Customer");
	scanf("%d", userType);

	while (selected = 0) {
		if(userType == 1){
			selected = 1;
			system("CLS");
			admin();
		} else if (userType == 2){
			selected = 1;
			system("CLS");
			customer();
		} else {
			system("CLS");
			printf("Please enter the correct type\n");
			printf("1: Admin \n 2: Customer \n 3: New Customer");
			scanf("%d", userType);
		}
	}
	


	scanf()
}