/*
	
*/
#include<iostream>
#include<string>
#include<fstream>
#include"Account.h"
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
	
	if (choice == 1)
		user.newAccount();
	else 
		if (user.validateAccount(user.getUsername(), user.getPassword()))
			menu();
		else
			cout << "Username or Password incorrect." << endl;
	
	
	
	return 0;
}

void menu() {
	cout << "\n1.\n2.\n3.\n4.\n5." << endl;
}