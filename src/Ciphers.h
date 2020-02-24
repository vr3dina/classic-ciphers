#pragma once
#include <string>


namespace Cipher {
	static std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

	static inline size_t index(char ch)
	{
		return ch - 'a';
	}

	namespace Ceasar {
		std::string encode(unsigned int shift, const std::string& text);
		std::string decode(unsigned int shift, const std::string& text);
	}

	namespace Vigenere {
		std::string encode(const std::string& key, const std::string& text);
		std::string decode(const std::string& key, const std::string& text);
	}

	namespace Playfair {
		std::string encode(const std::string& key, const std::string& text);
		std::string decode(const std::string& key, const std::string& text);
	}
}
