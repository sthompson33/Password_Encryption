//find key
//encrypt
//decrypt
#include <iostream>
using namespace std;

class Encrypt {
private:
	char key;
public:
	char findKey(string);
	string encrypt(string);
	string decrypt(string);
};

char Encrypt::findKey(string p) {

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