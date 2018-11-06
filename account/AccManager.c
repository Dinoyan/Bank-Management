#include "AccManager.h"

/*
* Used to authenticate users using their account number
* and password.
*/
int authenticate(int userType, int accNum, int password) {
	int authenticated = 0;

	if (userType == 1) {
		FILE *adminfile;
		struct Admin admin;

		adminfile = fopen("admin.dat", "r");
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

		customerfile = fopen("customer.dat", "r");
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
		customerfile = fopen ("customer.dat", "w");
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
