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
		if (!cin) {
			//clear any input that does not match a valid choice including strings
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (choice < 1 || choice > 2);
	cin.ignore();
	return choice;
}

int loginMenu() {
	int choice;
	do {
		cout << "\nLogin Information Menu" << endl;
		cout << "\n1. Add New\n2. Retrieve \n3. Update \n4. Delete \n5. Exit" << endl;
		cout << ">> ";
		cin >> choice;
		if (!cin) {
			//clear any input that does not match a valid choice including strings
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (choice < 1 || choice > 5);
	cin.ignore();
	return choice;
}

int main() {
	
	int openingMenuChoice, loginMenuChoice;
	int failedTries = 0;
	string username, password;
	bool correctInput, validInput;

	cout << "\n\t\t\t*** PASSWORD ENCRYPTION ***" << endl;
	openingMenuChoice = openingMenu();
	Account userAccount;

	do {
		validInput = true;
		
		do {
			correctInput = true;
			try {
				//ask for username and password with overloaded >> operator
				cin >> userAccount;
			}
			catch (runtime_error e) {
				cout << e.what();
				correctInput = false;
			}
		} while (!correctInput);

		username = userAccount.getUsername();
		password = userAccount.getPassword();

		if (openingMenuChoice == 1) { //create a new account option

			if (userAccount.lookForFile()) {

				if (userAccount.validateAccount(username, password)) {
					cout << "\n*** ACCOUNT ALREADY EXISTS ***\n" << endl;
					validInput = false;
				}
			}

			if(validInput)
				userAccount.newAccount();
		}
		else { //sign in to existing account option

			if (!(userAccount.validateAccount(username, password))){
				cout << "\n*** USERNAME OR PASSWORD INCORRECT ***" << endl;
				failedTries++;
				validInput = false;

				if (failedTries > 2) {
					cout << "\n*** MAX NUMBER OF TRIES REACHED ***\n";
					getchar();
					return 0;
				}
			}
		}
	} while (!validInput);

	loginMenuChoice = loginMenu();

	//create LoginInformation object
	//username sent to constructor to create user file to hold website login information
	LoginInformation login(username);
	do {
		switch (loginMenuChoice) {
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
		loginMenuChoice = loginMenu();
	} while (loginMenuChoice != 5);

	return 0;
}




