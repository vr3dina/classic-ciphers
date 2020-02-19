#include "Ciphers.h"


std::string Cipher::Ceasar::encode(unsigned int shift, const std::string& text)
{
	std::string ans = text;
	for (size_t i = 0; i < ans.size(); i++)
	{
		ans[i] = alphabet[(index(text[i]) + shift) % alphabet.size()];
	}
	return ans;
}

std::string Cipher::Ceasar::decode(unsigned int shift, const std::string& text)
{
	size_t n = alphabet.size();
	std::string ans = text;
	for (size_t i = 0; i < ans.size(); i++)
	{
		ans[i] = alphabet[(index(text[i]) + n - shift) % n];
	}
	return ans;
}