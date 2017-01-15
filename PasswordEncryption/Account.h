#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

class Account {
private:
	string username;
	string password;
	char key = 'q';
public:
	Account();
	Account(string, string);
	void newAccount();
	bool validateAccount(string, string);
	void setUsername(string);
	void setPassword(string);
	string getUsername();
	string getPassword();
	string encrypt(string);
	string decrypt(string);
};

//constructor
Account::Account() {
	
	cout << "Username: ";
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

void Account::newAccount() {

	ofstream outFile;
	outFile.open("account.txt", ios::app);

	if (outFile.is_open())
		outFile << encrypt(username) << "#" << encrypt(password) << endl;
	else
		cout << "File could not be opened.";
	outFile.close();
}

bool Account::validateAccount(string u, string p) {

	ifstream inFile("account.txt");
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			
			getline(inFile, username, '#');
			getline(inFile, password);
			
			if (u == decrypt(username) && p == decrypt(password)) {
				return true;
				break;
			}
		}
		inFile.close();
		return false;
	}
	else {
		cout << "File could not be found." << endl;
		exit(EXIT_FAILURE);
	}
}

string Account::encrypt(string str) {

	for (int i = 0; i < str.size(); i++)
		str[i] ^= (int(key) + i);
	return str;
}

string Account::decrypt(string str) {

	for (int i = 0; i < str.size(); i++)
		str[i] ^= (int(key) + i);
	return str;
}