#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "Ciphers.h"

using namespace std;
using namespace Cipher;

#define ASSERT_EQUAL(a, b, name) cout << name << (a == b ? " Ok" : " failed") << endl;

#define TEST(key, text, cipher)						\
{													\
	auto encoded = cipher::encode(key, text);		\
	auto decoded = cipher::decode(key, encoded);	\
	ASSERT_EQUAL(decoded, text, #cipher);			\
}													\


void generate_big_text_file(unsigned int size, ostream& out)
{
	srand(time(NULL));
	string text(size, ' ');
	for (int i = 0; i < size; i++)
		text[i] = (rand() % 26) + 'A';
	out << text;
}

void test()
{
	string key = "PLAYFAIR";
	ostringstream out;
	generate_big_text_file(10'000'000, out);

	TEST(3, out.str(), Ceasar);
	TEST(key, out.str(), Vigenere);
	TEST(key, out.str(), Playfair);
}

int main()
{
	test();
	return 0;
}