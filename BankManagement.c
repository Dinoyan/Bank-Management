#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define SPECIALKEY 1998

struct Customer {
	int accType;
	char firstName[64];
	char lastName[64];
	int accNum;
	int password;
}

struct Admin {
	int accType;
	char firstName[64];
	char lastName[64];
	int accNum;
	int password;
}

void admin(){
	int logout = 0;


}

void customer(){
	int logout = 0;

}

void createAccount(int userType){
	char firstName[64];
	char lastName[64];
	int password;
	int accNum;
	printf("Enter your first name: ");
	scanf("%s", firstName);
	printf("Enter your last name: ");
	scanf("%s", lastName);
	printf("Enter a new account number: \n");

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
  
   	 	struct Customer customer = {2, firstName, lastName, password}; 
      
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
	} else if(userType = SPECIALKEY) {
		FILE *adminfile; 
      
    	// open file for writing 
    	adminfile = fopen ("admin.dat", "w"); 
    	if (adminfile == NULL) { 
        	fprintf(stderr, "\nError opend file\n"); 
        	exit (1); 
    	} 
  
   	 	struct Admin admin = {1, firstName, lastName, password}; 
      
    	// write struct to file 
    	fwrite (&admin, sizeof(struct Admin), 1, adminfile); 
      
    	if(fwrite != 0) {
        	printf("contents to file written successfully !\n"); 
    	}
    	else {
        	printf("error writing file !\n"); 
    	}
  
    	// close file 
    	fclose (adminfile); 
	}
	

}

int authenticate(int userType, int accNum, int password){
	int authenticated = 0;
	int accNum;
	int password;

	if (userType == 1){
		FILE *adminfile
		struct Admin admin;

		adminfile = fopen("admin.dat", 'r');
		if(adminfile == NULL) {
			fprintf(stderr, "\nError opening file\n",);
			exit(1);
		}
		while(fread(&admin, sizeof(struct Admin), 1, adminfile)){
			if (admin.accNum == accNum && admi.password = password){
				authenticated = 1;
			} else {
				authenticated = 0;
			}
		}
	} else {
		FILE *customerfile
		struct Customer customer;

		customerfile = fopen("customer.dat", 'r');
		if(customerfile == NULL) {
			fprintf(stderr, "\nError opening file\n",);
			exit(1);
		}
		while(fread(&customer, sizeof(struct Customer), 1, customerfile)){
			if (customer.accNum == accNum && customer.password = password){
				authenticated = 1;
			} else {
				authenticated = 0;
			}
		}

	}

	return authenticated;
}

int main(){
	int userType;
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
		} else if(selected = SPECIALKEY) {
			system("CLS");
			createAccount(SPECIALKEY);

		{ else {
			system("CLS");
			printf("Please enter the correct type\n");
			printf("1: Admin \n 2: Customer \n 3: New Customer");
			scanf("%d", userType);
		}
	}
	
}