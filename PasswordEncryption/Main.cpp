/*
	Password_Encryption project -- store all username and passwords for online accounts in one place. 
	Information stored encrypted to file to protect privacy.

	Created by Stephen Thompson *** STILL A WORK IN PROGRESS *** 
	
	Features needed for main().
	- option for retrying password x number of times before ending program.

	
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

string getUsername() {
	string input;
	cout << "\nUsername: ";
	getline(cin, input);

	if (input.empty()) {
		runtime_error error("\n*** USERNAME LEFT BLANK ***\n");
		throw(error);
	}
	
	if (!isalpha(input[0])) {
		runtime_error error("\n*** USERNAME MUST BEGIN WITH AN ALPHABET CHARACTER ***\n");
		throw(error);
	}
	return input;
}

string getPassword() {
	string input;
	cout << "Password: ";
	getline(cin, input);

	if (input.empty()) {
		runtime_error error("\n*** PASSWORD LEFT BLANK ***\n");
		throw(error);
	}

	if (input.length() < 5) {
		runtime_error error("\n*** PASSWORD MUST BE LONGER THAN 5 CHARACTERS ***\n");
		throw(error);
	}
	return input;
}

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


int main() {

	int option1;//used for first choice
	int	option2;//used for choice from menu()
	string username, password;
	bool flag;
	
	option1 = openingMenu();
	
	do {
		flag = false;
		try {
			username = getUsername();
			password = getPassword();
		}
		catch (runtime_error e) {
			cout << e.what();
			flag = true;
		}
	} while(flag);

	Account userAccount(username, password);
	
	if (option1 == 1) {

		if (userAccount.lookForFile()) {

			if (userAccount.validateAccount(username, password)) {
				cout << "\n*** ACCOUNT ALREADY EXISTS ***\n" << endl;
				system("pause");
				return 0;
			}
			else {
				userAccount.newAccount();
				option2 = menu();
			}
		
		}
		else {
			userAccount.newAccount();
			option2 = menu();
		}
	
	}
	else { //option1 == 2
	
		if (userAccount.validateAccount(username, password))
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
			login.updateLogin(username);
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
}




