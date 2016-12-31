#include<iostream>
#include<string>
using namespace std;

class Account {
private:
	string username;
	string password;
public:
	Account();
	Account(string, string);
	void setUsername(string);
	void setPassword(string);
	string getUsername();
	string getPassword();
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