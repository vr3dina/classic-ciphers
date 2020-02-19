#include "Ciphers.h"


std::string Cipher::Vigenere::encode(const std::string& key, const std::string& text)
{
	auto ans = text;
	for (size_t i = 0; i < ans.size(); i++)
	{
		ans[i] = alphabet[(index(text[i]) + index(key[i % key.size()])) % alphabet.size()];
	}
	return ans;
}

std::string Cipher::Vigenere::decode(const std::string& key, const std::string& text)
{
	size_t n = alphabet.size();
	auto ans = text;
	for (size_t i = 0; i < ans.size(); i++)
	{
		ans[i] = alphabet[(n + index(text[i]) - index(key[i % key.size()])) % n];
	}
	return ans;
}