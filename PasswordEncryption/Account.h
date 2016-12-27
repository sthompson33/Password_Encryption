#include<iostream>
#include<string>
using namespace std;

class Account {
private:
	string username;
	string password;
public:
	void setUsername(string);
	void setPassword(string);
	string getUsername();
	string getPassword();
};

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