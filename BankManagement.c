/*
@author Dinoyan 

Inspired by: 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Customer.h"
#include "Admin.h"
#include "AccManager.h"

// defined constants
#define SPECIAL_KEY 1998
#define ADMIN_TYPE 1
#define CUSTOMER_TYPE 2

// global variables to see if the user's session is active or not
int activeCustomerSession = 0;
int activeAdminSession = 0;

void adminMainInterface(void);
void adminCustomerInterface(void);
void customerInterface(int);

// Struct to store the customers attributes
struct Customer {
	int accType;
	char firstName[64];
	char lastName[64];
	int accNum;
	int password;
	float balance;
};

// Struct to store the admins attributes
struct Admin {
	int accType;
	char firstName[64];
	char lastName[64];
	int accNum;
	int password;
};

/*
* Returns the customer's balace given their account number.
* Future plan: record each transaction.
*/
void getStatement(int accNum) {
	FILE *customerfile;
	struct Customer customer;

	customerfile = fopen("db/customer.dat", "r");
	if(customerfile == NULL){
		fprintf(stderr, "error opening file");
		exit(1);
	}

	while(fread(&customer, sizeof(struct Customer), 1, customerfile)) {
		if (customer.accNum == accNum){
			printf("|Statement|\n");
			printf("%s %s\n", customer.firstName, customer.lastName);
			printf("Balance: %f\n",customer.balance);
		}
	}
	fclose(customerfile);

	customerInterface(accNum);
}

/*
* deposit to customer account given amount and update the
* current balance.
*/
void deposit(float amount) {
	float newBalance = 0.0;
}


/*
* withdraw amoount from the customer and update the 
* current balance.
*/
float withdraw(float amount) {
	float newBalance = 0.0;

	return newBalance;
}

/*
* Used to authenticate users using their account number
* and password.
*/
int authenticate(int userType, int accNum, int password) {
	int authenticated = 0;

	if (userType == 1) {
		FILE *adminfile;
		struct Admin admin;

		adminfile = fopen("db/admin.dat", "r");
		if (adminfile == NULL) {
			fprintf(stderr, "\nError opening file\n");
			exit(1);
		}
		while (fread(&admin, sizeof(struct Admin), 1, adminfile)) {
			if ((admin.accNum == accNum) && (admin.password == password)) {
				authenticated = 1;
			}
		}

	} else {
		FILE *customerfile;
		struct Customer customer;

		customerfile = fopen("db/customer.dat", "r");
		if (customerfile == NULL) {
			fprintf(stderr, "\nError opening file\n");
			exit(1);
		}
		while (fread(&customer, sizeof(struct Customer), 1, customerfile)) {
			if ((customer.accNum == accNum) && (customer.password == password)) {
				authenticated = 1;
			} else {
				authenticated = 0;
			}
		}
	}
	return authenticated;
}

/*
* This function is used to create new accounts for admins 
* and customers.
*/
void createAccount(int userType) {
	char firstName[64];
	char lastName[64];
	char accountType;
	int password;
	int accNum;

	if (userType == SPECIAL_KEY) {
		printf("Customer Account [y/n]: ");
		while ((getchar()) != '\n');
		scanf("%c", &accountType);
		if (accountType == 'y') {
			userType = 2;
		} else {
			userType = SPECIAL_KEY;
		}
	}

	printf("Enter your first name: ");
	scanf("%s", firstName);
	printf("Enter your last name: ");
	scanf("%s", lastName);
	printf("Enter your new account number: ");
	scanf("%d", &accNum);
	printf("Enter your new password: ");
	scanf("%d", &password);


	
	if (userType == 2) {
		FILE *customerfile;

		// open file for writing
		customerfile = fopen ("db/customer.dat", "w");
		if (customerfile == NULL) {
			fprintf(stderr, "\nError opend file\n");
			exit (1);
		} 
		struct Customer customer;

		while (fread(&customer, sizeof(struct Customer), 1, customerfile)) {
			if (customer.accNum == accNum) {
				// Account number used.
			} else {
				strcpy(customer.firstName, firstName);
				strcpy(customer.lastName, lastName);
				customer.accType = CUSTOMER_TYPE;
				customer.accNum = accNum;
				customer.password = password;

				// write struct to file
				fwrite (&customer, sizeof(struct Customer), 1, customerfile);

			}
		}
		// close file
		fclose(customerfile);
		// authenticate(2, accNum, password);

	} else if (userType == SPECIAL_KEY) {
		FILE *adminfile;

		// open file for writing
		adminfile = fopen ("db/admin.dat", "w");
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


/*
BREAK INTO 2 INTERFACES:
	1. Menu for admin
		- What to do? Help with customer or logout
	2. Menu when helping customer.
*/

/*
* Displays the admin's menu UI
*/
void adminMainInterface() {
	int adminChoice;
	printf("|Admin Interface|\n");
	printf("1: Help a customer 2: logout\n");

	while ((getchar()) != '\n');
	scanf("%d", &adminChoice);

	if(adminChoice == 1) {
		adminCustomerInterface();
	} else if (adminChoice == 2) {
		activeAdminSession = 0;
		system("clear");
	} else {
		adminMainInterface();
	}
}

/*
* Displays the UI when an admin helps a customer
*/
void adminCustomerInterface() {
	int logout = 0;
	int choice, accNum, password, authenticated;
	float amount = 0.0;
	printf("|Customer help interface|\n");
	printf("Hello, please login!\n");

	if (activeCustomerSession != 1) {
		printf("Account number: ");
		while ((getchar()) != '\n');
		scanf("%d", &accNum);
		printf("Enter password: ");
		while ((getchar()) != '\n');
		scanf("%d", &password);
	}
	
	authenticated = authenticate(CUSTOMER_TYPE, accNum, password);
	if (authenticated == 1) {
		activeCustomerSession = 1;
		printf("How can i help you today?\n");
		printf("----menu---- \n");
		printf("1: Deposit \n2: Withdraw \n3: logout \n");
		while ((getchar()) != '\n');
		scanf("%d", &choice);
		if (choice == 1) {
			printf("Enter the amount to deposit: ");
			scanf("%f", &amount);
			withdraw(amount);
			deposit(amount);
		} else if (choice == 2) {
			printf("Enter the amount to withdraw: ");
			scanf("%f", &amount);
			withdraw(amount);
		} else if (choice == 3) {
			activeCustomerSession = 0;
			system("clear");
			printf("logged out successfully\n");
			printf("--------------------------\n");
			adminMainInterface();
		} else {
			adminCustomerInterface();
			printf("please select the correct opotion");
			system("clear");
		}
	}
}


void admin() {
	int authenticated, accNum, password, choice;
	printf("Account number: ");
	while ((getchar()) != '\n');
	scanf("%d", &accNum);
	printf("Enter password: ");
	while ((getchar()) != '\n');
	scanf("%d", &password);
	authenticated = authenticate(ADMIN_TYPE, accNum, password);
	if (authenticated == 1) {
		activeAdminSession = 1;
		system("clear");
		adminMainInterface();
	} else {
		system("clear");
		printf("Login failed\n");
		printf("--------------------------\n");
		admin();
	}
}

/*
* Displays the customer's UI
*/
void customerInterface(int accNum) {
	int tempAccNum = accNum;
	int logout = 0;
	int choice;
	printf("Customer Interface: ");
	printf("----menu---- \n");
	printf("|1: Balance| \n|2: Statement| \n|3: logout| \n");
	while ((getchar()) != '\n');
	scanf("%d", &choice);
	if (choice == 1) {

	} else if (choice == 2) {
		getStatement(accNum);
	} else if (choice == 3) {
		activeCustomerSession = 0;
		system("clear");
		printf("logged out successfully\n");
		printf("--------------------------\n");
	} else {
		system("clear");
		customerInterface(tempAccNum);
	}
}


void customer() {
	int logout = 0;
	int authenticated, accNum, password, choice;
	printf("Account number: ");
	scanf("%d", &accNum);
	printf("Enter password: ");
	scanf("%d", &password);
	authenticated = authenticate(CUSTOMER_TYPE, accNum, password);
	if (authenticated == 1) {
		activeCustomerSession = 1;
		system("clear");
		customerInterface(accNum);
	} else {
		system("clear");
		printf("Login failed");
		printf("--------------------------\n");
		customer();
	}
}

/*
* Main menu, where admin and customer picks who they are
*/

void menu(){
	int userType;
	int selected = 0;

	printf("---- Welcome to Dinoyan's Bank ----\n");
	printf("|Select your account type|\n");
	printf("|1: Admin| |2: Customer| ");
	scanf("%d", &userType);

	while (selected == 0) {
		// based on the selected option, call the correct function
		switch(userType){
			case 1:
				selected = 1;
				system("clear");
				admin();
			case 2:
				selected = 2;
				system("clear");
				customer();
			case SPECIAL_KEY:
				system("clear");
				selected = 1;
				createAccount(SPECIAL_KEY);
			default :
				printf("Please enter the correct type\n");
				menu();
		}
	}

}

int main() {
	// call menu function to display the menu
	menu();

	return 0;
}
