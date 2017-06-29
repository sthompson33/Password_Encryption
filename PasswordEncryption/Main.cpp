/*
	Password_Encryption project -- store all username and passwords for online accounts in one place. 
	Information stored encrypted to file to protect privacy.

	Created by Stephen Thompson
*/

#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include "Account.h"
#include "LoginInformation.h"
using namespace std;

int openingMenu() {
	int choice;
	do {
		cout << "\n1. Create New Account" << endl;
		cout << "2. Sign In" << endl;
		cout << ">> ";
		cin >> choice;
		cin.ignore();
	} while (choice > 2 || choice <= 0);
	return choice;
}

int loginMenu() {
	int choice;
	do {
		cout << "\nLogin Information Menu" << endl;
		cout << "\n1. Add New\n2. Retrieve \n3. Update \n4. Delete \n5. Exit" << endl;
		cout << ">> ";
		cin >> choice;
		cin.ignore();
	} while (choice <= 0 || choice > 5);
	return choice;
}

int main() {
	
	int option1;//used for openingMenu()
	int	option2;//used for loginMenu()
	string username, password;
	
	cout << "\n\t\t\t*** PASSWORD ENCRYPTION ***" << endl;
	option1 = openingMenu();
	Account userAccount;
	username = userAccount.getUsername();
	password = userAccount.getPassword();

	if (option1 == 1) {

		if (userAccount.lookForFile()) {

			if (userAccount.validateAccount(username, password)) {
				cout << "\n*** ACCOUNT ALREADY EXISTS ***\n" << endl;
				system("pause");
				return 0;
			}
			else {
				userAccount.newAccount();
				option2 = loginMenu();
			}
		
		}
		else {
			userAccount.newAccount();
			option2 = loginMenu();
		}
	
	}
	else { //option1 == 2
	
		if (userAccount.validateAccount(username, password))
			option2 = loginMenu();
		else { 
			//needs option to retry password x number of times before ending program
			cout << "\n*** USERNAME OR PASSWORD INCORRECT ***\n" << endl;
			return 0;
		}
	}

	

	//create LoginInformation object
	//username sent to constructor to create user file to hold website login information
	LoginInformation login(username);
	do {
		switch (option2) {
		case 1:
			login.newLogin(username);
			break;
		case 2:
			login.retrieveLogin(username);
			break;
		case 3:
			login.updateLogin(username);
			break;
		case 4:
			login.deleteLogin(username);
			break;
		default:
			return 0;
		}
		option2 = loginMenu();
	} while (option2 != 5);
	
	
	return 0; 
}




