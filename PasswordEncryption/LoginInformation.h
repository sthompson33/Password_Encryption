/*
	
	Known BUGS 
	- deleteLogin() only deletes website from file and not username and password like intended.
		*** recently fixed, more testing needed  6/6/17 ***
	-
*/
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
//#include "Encrypt.h" <-----why getting redundant error for this? / how Encrypt.h already included?
using namespace std;

class LoginInformation {
private:
	Encrypt code;
	string website;
	string username;
	string password;
public:
	LoginInformation(string);
	void newLogin(string);
	void retrieveLogin(string);
	void updateLogin(string);
	void deleteLogin(string);
}; 

//constructor -- creates a file for each account created to hold login information for websites
LoginInformation::LoginInformation(string str) {
	ofstream outFile;
	outFile.open(str + ".txt", ios::app);
	outFile.close();
}

/*
	newLogin() -- asks user for login information for a website.
	Uses encrypt() to store information in encrypted format on file.
*/

void LoginInformation::newLogin(string str) {
	
	ofstream outFile;
	outFile.open(str + ".txt", ios::app);
	
	if (outFile.is_open()) {

		cout << "\nWebsite: ";
		cin >> website;
		cout << "Username: ";
		cin >> username;
		cout << "Password: ";
		cin >> password;

		code.findKey(str);
		outFile << code.encrypt(website) << "	" << code.encrypt(username) << "	" << code.encrypt(password) << endl;
	
		outFile.close();
	}
	else
		cout << "\n*** FILE COULD NOT BE OPENED ***\n";
	
}

/*
	retrieveLogin()	-- return username and password for a website the user wants to see.
	Finds coressponding record on file with matching website, uses decrypt() and displays username and password
*/

void LoginInformation::retrieveLogin(string str) {
	
	bool flag = false;
	string site;
	ifstream inFile(str + ".txt");
	if (inFile.is_open()) {
		
		cout << "\nWebsite: ";
		cin >> site;

		while (getline(inFile, website, '	'), getline(inFile, username, '	'), getline(inFile, password)) {

			code.findKey(str);
			if (site == code.decrypt(website)) {
				cout << "Username: " << code.decrypt(username) << endl;
				cout << "Password: " << code.decrypt(password) << endl;
				flag = true;
				break;
			}
		}
		
		if (!flag) {
			cout << "\n*** NO LOGIN INFORMATION FOR " << site << " FOUND ***" << endl;
			exit(1);
		}
		inFile.close();
	}
	else
		cout << "\n*** FILE COULD NOT BE OPENED ***\n";
}

/*
	changeLogin() -- *** Testing Needed ***
	Allow user to change username or password for a website. 
*/

void LoginInformation::updateLogin(string str) {

	bool flag = false;
	int choice;
	string fileName = str + ".txt";
	string site, newInput;
	ofstream tempFile;
	tempFile.open("temp.txt", ios::app);
	ifstream inFile(str + ".txt");

	if (inFile.is_open()) {

		cout << "\nWebsite to Update: ";
		cin >> site;
		
		do {
			cout << "\nWhich to update\n1. Username\n2. Password\n>> ";
			cin >> choice;
		} while (choice < 1 || choice > 2);
		

		if (choice == 1) {
			cout << "\nNew Username\n>> ";
			cin >> newInput;
		}
		else
		{
			cout << "\nNew Password\n>> ";
			cin >> newInput;
		}

		cin.ignore();
		while (getline(inFile, website, '	'), getline(inFile, username, '	'), getline(inFile, password)) {

			code.findKey(str);
			if (site == code.decrypt(website)) {
				(choice == 1)  ? username = code.encrypt(newInput) : password = code.encrypt(newInput);
				tempFile << website << "	" << username << "	" << password << endl;
			}
			else
				tempFile << website << "	" << username << "	" << password << endl;
		}

		inFile.close();
		tempFile.close();

		const char * c = fileName.c_str();
		remove(c);
		rename("temp.txt", c);

		if (!flag) {
			cout << "\n*** NO LOGIN INFORMATION FOR " << site << " FOUND ***" << endl;
			exit(1);
		}
	}
	else
		cout << "\n*** FILE COULD NOT BE OPENED ***\n";
}

/*
	deleteLogin() -- user can delete a record of login information from file when no longer needed.
	Input website to delete. Creates a temporary file to write records that do not match website entered by user.
	Temporary file then renamed to current user file. Old user file removed.
*/

void LoginInformation::deleteLogin(string str) {
	
	string fileName = str + ".txt";
	string site;
	ofstream tempFile;
	tempFile.open("temp.txt", ios::app);
	ifstream inFile(str + ".txt");
	
	if (inFile.is_open()) {

		cout << "\nWebsite to Delete: ";
		cin >> site;
		cin.ignore();

		while (getline(inFile, website, '	'), getline(inFile, username, '	'), getline(inFile, password)) {

			code.findKey(str);
			if (site != code.decrypt(website))
				tempFile << website << "	" << username << "	" << password << endl;
		}
	
		inFile.close();
		tempFile.close();
		
		const char * c = fileName.c_str();
		remove(c);
		rename("temp.txt", c);
	}
	else
		cout << "\n*** FILE COULD NOT BE OPENED ***\n";
}