/*
	class Encrypt

	* Both encrypt() and decrypt() 
		-- include if statements to detect and change specific characters during ciphering that could disrupt data.
		
			OLD CHAR     DESCRIPTION												 NEW CHAR
			~            used as a delimiter when storing data to a file			 \u00C2   A
			\n           will cause data from same record to begin on a new line     \u00CA   E
			\u001A       unicode substitute character used to signal end of file     \u017D   Z

			encrypt() OLD CHAR --> NEW CHAR
			decrypt() NEW CHAR --> OLD CHAR

	** Only chars found at this time to cause disruptions. Will update if more found.
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

/*
	findKey(string) -- finds the first char of the username entered at account creation. 
	This char will be used as a key to create unique encryptions for each account.
*/

void Encrypt::findKey(string name) {
	key = name[0];
}

/*
	encrypt(string) -- encrypts each character of str using the XOR operation.
*/

string Encrypt::encrypt(string str) {
	
	for (int i = 0; i < str.size(); i++) {
		
		str[i] ^= (int(key) + i);

		if (str[i] == '~')
			str[i] = '\u00C2';
		
		if (str[i] == '\n')
			str[i] = '\u00CA';

		if (str[i] == '\u001A')
			str[i] = '\u017D'; 
	}
	return str;
}

/*
	decrypt(string) -- decrypts each encrypted str character using the XOR operation to restore it to original form.
*/

string Encrypt::decrypt(string str) {

	for (int i = 0; i < str.size(); i++) {

		if (str[i] == '\u00C2')
			str[i] = '~';
		
		if (str[i] == '\u00CA')
			str[i] = '\n';
		
		if (str[i] == '\u017D') 
			str[i] = '\u001A';

		str[i] ^= (int(key) + i);
	}
	return str;
}