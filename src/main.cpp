#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "Ciphers.h"

using namespace std;
using namespace Cipher;

#define ASSERT_EQUAL(a, b, name) cout << name << (a == b ? " Ok" : " failed") << endl;

#define TEST(key, text, cipher) \
{ \
	auto encoded = cipher::encode(key, text); \
	auto decoded = cipher::decode(key, encoded); \
	ASSERT_EQUAL(decoded, text, #cipher); \
} \


void generate_text(unsigned int size, ostream& out)
{
	srand(time(NULL));
	string text(size, ' ');
	for (int i = 0; i < size; i++)
		text[i] = (rand() % 26) + 'a';
	out << text;
}

void test(unsigned int size = 1'000'000)
{
	string key = "playfair";
	ostringstream out;
	generate_text(size, out);

	TEST(3, out.str(), Ceasar);
	TEST(key, out.str(), Vigenere);
	TEST(key, out.str(), Playfair);
}

void usage()
{
	cout << "Usage: \n";
	cout << "-c\tCeasar\n";
	cout << "-p\tPlayfair\n";
	cout << "-v\tVigenere\n";
	cout << "-e\tencode\n";
	cout << "-d\tdecode\n";
}

int main(int argc, char* argv[])
{
	if (argc != 2 && argc != 3)
	{
		usage();
		return 0;
	}

	bool encode = true;
	enum { CEASAR, VIGENERE, PLAYFAIR } cipher_type = CEASAR;
	for (size_t i = 1; i < argc && argv[i][0] == '-'; i++)
	{
		switch (argv[i][1])
		{
		case 'e': encode = true; break;
		case 'd': encode = false; break;
		case 'c': cipher_type = CEASAR; break;
		case 'p': cipher_type = PLAYFAIR; break;
		case 'v': cipher_type = VIGENERE; break;
		case 't': test(); return 0;
		default:
			usage();
			exit(EXIT_FAILURE);
		}
	}

	system(" ");
	string key, text;
	cout << "Enter key: ";
	cin >> key;
	cout << "\u001B[A" << "Enter key: " << key << endl;
	cout << "Enter text: ";
	cin >> text;
	cout << "\u001B[A" << "Enter text: " << text << endl << "(d)encrypted text: ";
	switch (cipher_type)
	{
	case CEASAR:
	{
		stringstream s(key);
		int int_key;
		s >> int_key;
		cout << (encode ? Ceasar::encode(int_key, text) : Ceasar::decode(int_key, text));
		break;
	}
	case VIGENERE:
		cout << (encode ? Vigenere::encode(key, text) : Vigenere::decode(key, text));
		break;
	case PLAYFAIR:
		cout << (encode ? Playfair::encode(key, text) : Playfair::decode(key, text));
		break;
	}

	return 0;
}