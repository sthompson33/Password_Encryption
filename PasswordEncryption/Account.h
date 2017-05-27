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
	Check to see if file is open, if not display that it doesnt exist. 
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
	If the user selects to create a new account, after entering username and password from constructor,
	newAccount() will be called to write the data in encrypted format to file.
*/

void Account::newAccount() {

		ofstream outFile;
		outFile.open("account.txt", ios::app);
		if (outFile.is_open()) {
			code.findKey(username);
			outFile << username << "-" << code.encrypt(password) << endl;
		}
		else
			cout << "\n*** FILE COULD NOT BE OPENED ***\n";
		outFile.close();
}

/*
	
*/
bool Account::validateAccount(string u, string p) {

	string user, pass;
	bool flag = false;
	ifstream inFile("account.txt");
	if (inFile.is_open()) {
		
		while (!inFile.eof()) {

			getline(inFile, user, '-');
			getline(inFile, pass);
			
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


