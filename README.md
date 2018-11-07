# Bank-Management

This is a simple bank management project made with C. Made like real life banking system with admins and customers.


Project still in progress

Future Plan(s):
  - Create a single file for each user
  - Better UI
  
- Currently splitting up the code

### Functions
  ##### account/AccManager.h
  - ```int int authenticate(int userType, int accNum, int password)```
  
    Used to authenticate users using their account number
            and password.
  - ```void createAccount(int userType)```
  
      This function is used to create new accounts for admins 
  and customers.
    
  
  

### Deployment

* Clone this repo
* cd into the repo
* `gcc -Wall -std=gnu99 -g -o bank BankManagement.c`
* `./bank`

