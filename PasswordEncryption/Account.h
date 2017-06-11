/*
	Known BUGS 
	- methods from Encrypt.h do not work well with any account created with a username 
	that starts with a lowercase EXAMPLE: stephen instead of Stephen. Check findKey() from Encrypt.h and ASCII setup.
		*** toupper() used in findKey(). Ok for now. 6/7/17 *** 

	Features needed
	-include exception handling for empty input when creating an account.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Encrypt.h"
using namespace std;

class Account {
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

//constructor
Account::Account() {
	//need to check for empty input
	cout << "\nUsername: ";
	getline(cin, username);
	cout << "Password: ";
	getline(cin, password);
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

	bool flag = false;
	ifstream inFile("account.txt");
	if (inFile)
		flag = true;
	inFile.close();
	return flag;
}

/*
	If the user selects to create a new account after entering username and password from constructor,
	newAccount() will be called to write the data in encrypted format to file.
*/

void Account::newAccount() {

	ofstream outFile;
	outFile.open("account.txt", ios::app);
	if (outFile.is_open()) {
		code.findKey(username);
		outFile << username << "	" << code.encrypt(password) << endl;
		outFile.close();
	}
	else
		cout << "\n*** FILE COULD NOT BE OPENED ***\n";
}

/*
	validateAccount() -- has two uses from main()
	1. check to see if account already exists when user selects to make a new account
	2. check to see if account exist when user selects to sign in
*/
bool Account::validateAccount(string u, string p) {

	string user, pass;
	bool flag = false;
	ifstream inFile("account.txt");
	if (inFile.is_open()) {
		
		while (getline(inFile, user, '	'), getline(inFile, pass)) {

			code.findKey(user);
			if (u == user && p == code.decrypt(pass)) {
				flag = true;
				break;
			}
		}
		inFile.close();
	}
	else {
		cout << "\n*** NO ACCOUNTS ON RECORD. PLEASE CREATE NEW ACCOUNT ***\n" << endl;
		exit(1);
	}
	return flag;
}


