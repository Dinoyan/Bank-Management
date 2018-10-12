#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define SPECIAL_KEY 1998
#define ADMIN_TYPE 1
#define CUSTOMER_TYPE 2

struct Customer {
	int accType;
	char firstName[64];
	char lastName[64];
	int accNum;
	int password;
	float balance;
};

struct Admin {
	int accType;
	char firstName[64];
	char lastName[64];
	int accNum;
	int password;
};

float deposit(float amount, struct Customer customer){
	float newBalance;
	
	return newBalance;
}

float withdraw(float amount, struct Customer customer){
	float newBalance;

	return newBalance;
}


int authenticate(int userType, int accNum, int password){
	int authenticated = 0;

	if (userType == 1){
		FILE *adminfile;
		struct Admin admin;

		adminfile = fopen("admin.dat", "r");
		if(adminfile == NULL) {
			fprintf(stderr, "\nError opening file\n");
			exit(1);
		}
		while(fread(&admin, sizeof(struct Admin), 1, adminfile)){
			if ((admin.accNum == accNum) && (admin.password == password)){
				authenticated = 1;
			} 
		}

	} else {
		FILE *customerfile;
		struct Customer customer;

		customerfile = fopen("customer.dat", "r");
		if(customerfile == NULL) {
			fprintf(stderr, "\nError opening file\n");
			exit(1);
		}
		while(fread(&customer, sizeof(struct Customer), 1, customerfile)){
			if ((customer.accNum == accNum) && (customer.password == password)){
				authenticated = 1;
				printf("success\n");
			} else {
				authenticated = 0;
			}
		}

	}

	return authenticated;
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
	printf("Enter your new account number: ");
	scanf("%d", &accNum);
	printf("Enter your new password: ");
	scanf("%d", &password);

	if (userType == 2){
		FILE *customerfile; 
      
    	// open file for writing 
    	customerfile = fopen ("customer.dat", "w"); 
    	if (customerfile == NULL) { 
        	fprintf(stderr, "\nError opend file\n"); 
        	exit (1); 
    	} 

    	struct Customer customer;

    	strcpy(customer.firstName, firstName);
    	strcpy(customer.lastName, lastName);
    	customer.accType = CUSTOMER_TYPE;
    	customer.accNum = accNum;
    	customer.password = password;
      	
    	// write struct to file 
    	fwrite (&customer, sizeof(struct Customer), 1, customerfile); 
      
    
    	// close file 
    	authenticate(2, accNum, password);
	} else if(userType == SPECIAL_KEY) {
		FILE *adminfile; 
      
    	// open file for writing 
    	adminfile = fopen ("admin.dat", "w"); 
    	if (adminfile == NULL) { 
        	fprintf(stderr, "\nError opend file\n"); 
        	exit (1); 
    	} 

    	struct Admin admin;
  
   	 	strcpy(admin.firstName, firstName);
    	strcpy(admin.lastName, lastName);
    	admin.accType = ADMIN_TYPE;
    	admin.accNum = accNum;
    	admin.password = password;
      
    	// write struct to file 
    	fwrite (&admin, sizeof(struct Admin), 1, adminfile); 
     
    	// close file 
    	fclose (adminfile); 
	}
}



void admin(){
	int logout = 0;
	int authenticated, accNum, password, choice;
	printf("account number: ");
	scanf("%d", &accNum);
	printf("Enter password: ");
	scanf("%d", &password);
	authenticated = authenticate(ADMIN_TYPE, accNum, password);
	if (authenticated == 1) {
		while (logout == 0){
			// admin menu.
		}
	} else {
		printf("Login failed");
		admin();
	}
}


void customer(){
	int logout = 0;
	int authenticated, accNum, password;
	printf("Account number: ");
	scanf("%d", &accNum);
	printf("Enter password: ");
	scanf("%d", &password);
	authenticated = authenticate(CUSTOMER_TYPE, accNum, password);
	if (authenticated == 1) {
		while (logout == 0){
			// customer menu.
		}
	} else {
		printf("Login failed");
		customer();
	}
}


int main(){
	int userType;
	int selected = 0;

	printf("Welcome to Dinoyan's Bank\n");
	printf("Select your account type\n");
	printf("1: Admin 2: Customer: ");
	scanf("%d", &userType);

	while (selected == 0) {
		if(userType == 1){
			selected = 1;
			system("cls");
			admin();
		} else if (userType == 2){
			selected = 1;
			system("cls");
			customer();
		} else if(userType == SPECIAL_KEY) {
			system("cls");
			selected = 1;
			createAccount(SPECIAL_KEY);
		} else {
			system("cls");
			printf("Please enter the correct type\n");
			printf("1: Admin \n2: Customer: ");
			scanf("%d", &userType);
		}
	}
}