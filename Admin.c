#include "Admin.h"

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