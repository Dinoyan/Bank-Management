#include "Customer.h"


/*
* Returns the customer's balace given their account number.
* Future plan: record each transaction.
*/
void getStatement(int accNum) {
	FILE *customerfile;
	struct Customer customer;

	customerfile = fopen("customer.dat", "r");
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