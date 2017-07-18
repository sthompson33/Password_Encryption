/*


*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
using namespace std;

class LoginInformation {
private:
	Encrypt code;
	string website;
	string username;
	string password;
public:
	LoginInformation(string);
	bool findWebsite(string, string);
	void newLogin(string);
	void retrieveLogin(string);
	void updateLogin(string);
	void deleteLogin(string);
}; 

//constructor -- creates a file for each account created to hold login information for websites
LoginInformation::LoginInformation(string name) {
	
	ofstream outFile;
	outFile.open(name + ".txt", ios::app);
	outFile.close();
}

/*
	findWebsite(string, string) -- used to see if website exist on file.  
	If matching website found on file, true returned. If no website found, false returned. 

	Parameter(s) -- name is the username of current user, used to specify which file to read/write.
				 -- site is website to search for on file.
*/

bool LoginInformation::findWebsite(string name, string site) {

	ifstream inFile(name + ".txt");
	if (inFile.is_open()) {

		while (getline(inFile, website, '~'), getline(inFile, username, '~'), getline(inFile, password)) {

			code.findKey(name);
			if (site == code.decrypt(website)) 
				return true;
		}
		inFile.close();
		return false;
	}
	else
		cout << "\n*** FILE COULD NOT BE OPENED ***\n";
}

/*
	newLogin(string) -- asks user for login information for a new website to store on file. Parameter 
	Uses findWebsite() to avoid writing duplicates. If website does not already exist,
	user will be asked for username and password for new website.
	Uses encrypt() to store information in encrypted format.

	Parameter(s) -- name is the username of current user, used to specify which file to read/write.
*/

void LoginInformation::newLogin(string name) {
	
	ofstream outFile;
	outFile.open(name + ".txt", ios::app);
	
	if (outFile.is_open()) {
		
		string site;
		cout << "\nNew Website: ";
		getline(cin, site);

		while (site.empty()) {
			cout << "\n*** WEBSITE CANNOT BE BLANK ***\n";
			cout << "\nNew Website: ";
			getline(cin, site);
		}

		if (!findWebsite(name, site)) {
			
			website = site;
			cout << "Username: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;

			code.findKey(name);
			outFile << code.encrypt(website) << "~" << code.encrypt(username) << "~" << code.encrypt(password) << endl;
		}
		else 
			cout << "\n*** LOGIN INFORMATION FOR " << site << " ALREADY ON FILE ***\n";
		
		outFile.close();
	}
	else
		cout << "\n*** FILE COULD NOT BE OPENED ***\n";
}

/*
	retrieveLogin()	-- return username and password for a website the user wants to see.
	Finds coressponding record on file with matching website, uses decrypt() and displays username and password.
	If website not found, message will display no information found.

	Parameter(s) -- name is the username of current user, used to specify which file to read/write.
*/

void LoginInformation::retrieveLogin(string name) {
	
	bool found = false;
	string site;
	ifstream inFile(name + ".txt");
	if (inFile.is_open()) {
		
		cout << "\nWebsite to Retrieve: ";
		cin >> site;
		cin.ignore();

		while (getline(inFile, website, '~'), getline(inFile, username, '~'), getline(inFile, password)) {

			code.findKey(name);
			if (site == code.decrypt(website)) {
				cout << "Username: " << code.decrypt(username) << endl;
				cout << "Password: " << code.decrypt(password) << endl;
				found = true;
				break;
			}
		}
		
		if (!found) 
			cout << "\n*** NO LOGIN INFORMATION FOR " << site << " FOUND ***" << endl;
			
		inFile.close();
	}
	else
		cout << "\n*** FILE COULD NOT BE OPENED ***\n";
}

/*
	updateLogin() -- allow user to change username or password for a website. 
	Uses findwebsite() to verify website exist on file. If website is found, user will be asked 
	if they wish to update username or password. Temporary file created to store new information and renamed 
	to previous file name. Old file with outdated information deleted.

	Parameter(s) -- name is the username of current user, used to specify which file to read/write.
*/

void LoginInformation::updateLogin(string name) {

	int choice;
	string fileName = name + ".txt";
	string site, newInput;
	ofstream tempFile;
	tempFile.open("temp.txt", ios::app);
	ifstream inFile(name + ".txt");

	if (inFile.is_open()) {

		cout << "\nWebsite to Update: ";
		cin >> site;
		
		if (findWebsite(name, site)) {
			
			do {
				cout << "\nWhich to update\n1. Username\n2. Password\n>> ";
				cin >> choice;
			} while (choice < 1 || choice > 2);

			if (choice == 1) {
				cout << "\nNew Username: ";
				cin >> newInput;
			}
			else{
				cout << "\nNew Password: ";
				cin >> newInput;
			}
			cin.ignore();

			while (getline(inFile, website, '~'), getline(inFile, username, '~'), getline(inFile, password)) {

				code.findKey(name);
				if (site == code.decrypt(website)) {
					(choice == 1) ? username = code.encrypt(newInput) : password = code.encrypt(newInput);
					tempFile << website << "~" << username << "~" << password << endl;
				}
				else
					tempFile << website << "~" << username << "~" << password << endl;
			}

			inFile.close();
			tempFile.close();

			const char * c = fileName.c_str();
			remove(c);
			rename("temp.txt", c);

			cout << "\nWebsite Login Information Successfully Updated\n";
		}
		else
			cout << "\n*** NO LOGIN INFORMATION FOR " << site << " FOUND ***" << endl;
	}
	else
		cout << "\n*** FILE COULD NOT BE OPENED ***\n";
}

/*
	deleteLogin() -- user can delete a record of login information from file when no longer needed.
	Uses findWebsite() to verify website exist on file. If website found, user will be asked for which website info
	they wish to delete. Temporary file created to write website info that does not match user input and renamed to previous
	file name. Old file with unwanted website information deleted.

	Parameter(s) -- name is the username of current user, used to specify which file to read/write.
*/

void LoginInformation::deleteLogin(string name) {
	
	string fileName = name + ".txt";
	string site;
	ofstream tempFile;
	tempFile.open("temp.txt", ios::app);
	ifstream inFile(name + ".txt");
	
	if (inFile.is_open()) {

		cout << "\nWebsite to Delete: ";
		cin >> site;
		cin.ignore();

		if (findWebsite(name, site)) {
			
			while (getline(inFile, website, '~'), getline(inFile, username, '~'), getline(inFile, password)) {

				code.findKey(name);
				if (site != code.decrypt(website))
					tempFile << website << "~" << username << "~" << password << endl;
			}

			inFile.close();
			tempFile.close();

			const char * c = fileName.c_str();
			remove(c);
			rename("temp.txt", c);
			
			cout << "\nWebsite Login Information Successfully Deleted\n";
		}
		else
			cout << "\n*** NO LOGIN INFORMATION FOR " << site << " FOUND ***" << endl;
	}
	else
		cout << "\n*** FILE COULD NOT BE OPENED ***\n";
}

