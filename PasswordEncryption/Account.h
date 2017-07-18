/*
	

*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <exception>
#include "Encrypt.h"
using namespace std;

class Account {
	friend istream& operator >> (istream&, Account&) throw(runtime_error);
private:
	Encrypt code;
	string username;
	string password;
public:
	Account();
	Account(string, string);
	bool lookForFile();
	void newAccount();
	bool validateAccount(string, string);
	void setUsername(string);
	void setPassword(string);
	string getUsername();
	string getPassword();

};

/*
	overloaded operator >> for getting username and password input.  
	Exception handling included...
	Username must begin with an alphabet character.
	Password must be longer than 5 characters long
	Both cannot be NULL
*/
istream& operator >> (istream& in, Account& acct) throw(runtime_error) {
	
	cout << "\nUsername: ";
	getline(in, acct.username);

	if (acct.username.empty()) {
		runtime_error error("\n*** USERNAME CANNOT BE BLANK ***\n");
		throw(error);
	}
	else if (!isalpha(acct.username[0])) {
		runtime_error error("\n*** USERNAME MUST BEGIN WITH AN ALPHABET CHARACTER ***\n");
		throw(error);
	}

	cout << "Password: ";
	getline(in, acct.password);

	if (acct.password.empty()) {
		runtime_error error("\n*** PASSWORD CANNOT BE BLANK ***\n");
		throw(error);
	}
	else if (acct.password.length() < 6) {
		runtime_error error("\n*** PASSWORD MUST BE LONGER THAN 5 CHARACTERS ***\n");
		throw (error);
	}
}

//constructors
Account::Account() {

}

Account::Account(string u, string p) {
	username = u;
	password = p;
}

void Account::setUsername(string u) {
	username = u;
}

void Account::setPassword(string p) {
	password = p;
}

string Account::getUsername() {
	return username;
}

string Account::getPassword() {
	return password;
}

/*
	lookForFile() -- if file exists return true, if not return false. 

*/

bool Account::lookForFile() {

	bool found = false;
	ifstream inFile("account.txt");
	if (inFile)
		found = true;
	inFile.close();
	return found;
}

/*
	newAccount() -- write new account information to account.txt in encrypted format.
*/

void Account::newAccount() {

	ofstream outFile;
	outFile.open("account.txt", ios::app);
	if (outFile.is_open()) {
		code.findKey(username);
		outFile << username << "~" << code.encrypt(password) << endl;
		outFile.close();
	}
	else
		cout << "\n*** FILE COULD NOT BE OPENED ***\n";
}

/*
	validateAccount() -- has two uses from main()
	1. check to see if account already exists when user selects to make a new account
	2. check to see if account exist when user selects to sign in

	Parameter(s) -- u for username entered by user
		         -- p for password entered by user
*/
bool Account::validateAccount(string u, string p) {

	string user, pass;
	bool found = false;
	ifstream inFile("account.txt");
	if (inFile.is_open()) {
		
		while (getline(inFile, user, '~'), getline(inFile, pass)) {

			code.findKey(user);
			if (u == user && p == code.decrypt(pass)) {
				found = true;
				break;
			}
		}
		inFile.close();
	}
	else {
		cout << "\n*** NO ACCOUNTS ON RECORD. PLEASE CREATE NEW ACCOUNT ***\n" << endl;
		getchar();
		exit(EXIT_FAILURE);
	}
	return found;
}


