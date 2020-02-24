#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>
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


string generate_text(unsigned int size)
{
	srand(time(NULL));
	string text(size, ' ');
	for (int i = 0; i < size; i++)
		text[i] = (rand() % 26) + 'a';
	return text;
}

void test(unsigned int size = 10'000'000)
{
#ifdef _DEBUG
	size = 10;
#endif // _DEBUG

	string key = "playfair";
	string text = generate_text(size);

	TEST(27, text, Ceasar);
	TEST(key, text, Vigenere);
	TEST(key, text, Playfair);
}

vector<double> calc_probabilities(const string& text)
{
	vector<double> probabilities(128);
	for (char ch : text)
		probabilities[ch]++;
	for (double& p : probabilities)
		p /= text.size();
	return probabilities;
}

double calc_entropy(const string& text)
{
	vector<double> probabilities = calc_probabilities(text);
	double H = 0;
	for (double p : probabilities)
	{
		if (p != 0)
		{
			H += p * log2(p);
		}
	}
	return -H;
}

void print_entropy()
{
	int size;
	cout << "Enter text size: ";
	cin >> size;

	string text = generate_text(size);
	string key = "playfair";

	cout << "Plain text\t" << calc_entropy(text) << endl;
	cout << "Ceasar text\t" << calc_entropy(Ceasar::encode(3, text)) << endl;
	cout << "Vigenere text\t" << calc_entropy(Vigenere::encode(key, text)) << endl;
	cout << "Playfair text\t" << calc_entropy(Playfair::encode(key, text)) << endl;
}

void usage()
{
	cout << "Usage: \n";
	cout << "-e\tprint entropy\n";
	cout << "-c\tCeasar [default]\n";
	cout << "-p\tPlayfair\n";
	cout << "-v\tVigenere\n";
	cout << "-d\tdecode [optional]\n";
	cout << "-k\tprint key [optional]\n";
}

int main(int argc, char* argv[])
{
	if (argc != 2 && argc != 3)
	{
		usage();
		return 0;
	}

	bool encode = true;
	bool print_key = false;
	enum { CEASAR, VIGENERE, PLAYFAIR } cipher_type = CEASAR;
	for (size_t i = 1; i < argc && argv[i][0] == '-'; i++)
	{
		switch (argv[i][1])
		{
		case 'e': print_entropy(); return 0;
		case 'd': encode = false; break;
		case 'c': cipher_type = CEASAR; break;
		case 'p': cipher_type = PLAYFAIR; break;
		case 'v': cipher_type = VIGENERE; break;
		case 'k': print_key = true; break;
		case 't': test(); return 0;
		default:
			usage();
			exit(EXIT_FAILURE);
		}
	}

	string key, text;
	cin >> key;
	cin >> text;
	if (print_key)
		cout << key << endl;
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