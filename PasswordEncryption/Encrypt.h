/*
	
*/
#include <iostream>
using namespace std;

class Encrypt {
private:
	char key;
public:
	void findKey(string);
	string encrypt(string);
	string decrypt(string);
};

void Encrypt::findKey(string str) {
	key = str[0];
}

string Encrypt::encrypt(string str) {
	
	for (int i = 0; i < str.size(); i++)
		str[i] ^= (int(key) + i);
	return str;
}

string Encrypt::decrypt(string str) {

	for (int i = 0; i < str.size(); i++)
		str[i] ^= (int(key) + i);
	return str;
}