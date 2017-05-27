/*
	
*/
#include <iostream>
#include <string>
#include <fstream>
#include "Account.h"
#include "AccountInformation.h"
using namespace std;

//function prototypes
void menu();

int main() {

	int choice;
	do {
		cout << "1. Create New Account" << endl;
		cout << "2. Sign In" << endl;
		cout << ">> ";
		cin >> choice;
		cin.ignore();
	} while (choice > 2 || choice == 0);

	//create Account object using default constructor
	//constructor will ask for username and password
	Account user;

	if (choice == 1) {

		if (user.lookForFile()) {

			if (user.validateAccount(user.getUsername(), user.getPassword())) {
				cout << "\n*** ACCOUNT ALREADY EXISTS ***\n" << endl;
				return 0;
			}
			else
				user.newAccount();
		}
		else
			user.newAccount();
	}
	else { //choice == 2
		if (user.validateAccount(user.getUsername(), user.getPassword()))
			menu();
		else
			cout << "\n*** USERNAME OR PASSWORD INCORRECT ***\n" << endl;
	}

	return 0;
}

void menu() {
	cout << "\n1.\n2.\n3.\n4.\n5." << endl;
}
