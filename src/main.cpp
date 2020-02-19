#include <iostream>
#include "Ciphers.h"

using namespace std;
using namespace Cipher;

#define TEST(a, b, name) cout << name << (a == b ? " Ok" : " failed") << endl;

void test_ceasar()
{
	std::string text = "ABCDEFXYZ";
	unsigned int key = 3;
	auto encoded = Ceasar::encode(key, text);
	auto decoded = Ceasar::decode(key, encoded);
	TEST(decoded, text, "Ceasar");
}

void test_vigenere()
{
	std::string key = "LEMON";
	std::string text = "ATTACKATDAWNXYZ";
	auto encoded = Vigenere::encode(key, text);
	auto decoded = Vigenere::decode(key, encoded);
	TEST(decoded, text, "Viginere");
}


void test_playfair()
{
	string key = "PLAYFAIR";
	string text = "JKLJSRIOJG";
	auto encoded = Playfair::encode(key, text);
	auto decoded = Playfair::decode(key, encoded);
	TEST(decoded, text, "Playfair");
}

int main()
{
	test_ceasar();
	test_vigenere();
	test_playfair();
	return 0;
}