/*
	Password_Encryption project -- store all username and passwords for online accounts in one place. 
	Information stored encrypted to file to protect privacy.

	Created by Stephen Thompson *** STILL A WORK IN PROGRESS *** 
	
	Features needed for main().
	- option for retrying password x number of times before ending program.

	********* NEW DELIMITER CHAR NEEDED/ POSSIBLE FOR MORE THAN ONE?/ EX: -- *********
*/
#include <iostream>
#include <string>
#include <fstream>
#include "Account.h"
#include "LoginInformation.h"
using namespace std;

//function prototypes
int menu();

int main() {

	int option1;//used for first choice
	int	option2;//used for choice from menu()
	
	do {
		cout << "1. Create New Account" << endl;
		cout << "2. Sign In" << endl;
		cout << ">> ";
		cin >> option1;
		cin.ignore();
	} while (option1 > 2 || option1 == 0);

	//create Account object using default constructor
	//constructor will ask for username and password
	Account user;
	string username = user.getUsername();
	string password = user.getPassword();

	if (option1 == 1) {

		if (user.lookForFile()) {

			if (user.validateAccount(username, password)) {
				cout << "\n*** ACCOUNT ALREADY EXISTS ***\n" << endl;
				return 0;
			}
			else {
				user.newAccount();
				option2 = menu();
			}
		
		}
		else {
			user.newAccount();
			option2 = menu();
		}
	
	}
	else { //option1 == 2
	
		if (user.validateAccount(username, password))
			option2 = menu();
		else { 
			//needs option to retry password x number of times before ending program
			cout << "\n*** USERNAME OR PASSWORD INCORRECT ***\n" << endl;
			return 0;
		}
	}

	//create LoginInformation object
	//username sent to constructor to create user file to hold login information
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
			login.changeLogin(username);
			break;
		case 4:
			login.deleteLogin(username);
			break;
		default:
			return 0;
		}
		option2 = menu();
	} while (option2 != 5);

	return 0; 
}//end of main

int menu() {
	int choice;
	do {
		cout << "\nLogin Information Menu" << endl;
		cout << "\n1. Add New\n2. Retrieve \n3. Change \n4. Delete \n5. Exit" << endl;
		cout << ">> ";
		cin >> choice;
		cin.ignore();
	} while (choice <= 0 || choice > 5);
	return choice;
}
