/*
	
*/
#include<iostream>
#include<string>
#include<fstream>
#include"Account.h"
using namespace std;

int main() {

	char choice;
	cout << "1. Create New Account" << endl;
	cout << "2. Sign In" << endl;
	cout << ">> ";
	cin >> choice;
	cin.ignore();
	//create an Account object using default constructor
	Account user;
	
	return 0;
}
