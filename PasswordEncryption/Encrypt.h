/*
	findKey(string) 
		-- finds the first char of the username entered at account creation. This char will be
		used to create unique encryptions for each account.

	encrypt(string)
	decrypt(string)
		-- use same instructions, included both for clarity when in use. 
		encrypt - used to show when regular text transformed into encrypted format.
		decrypt - used to show when encryptions transformed into regular text.
*/

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