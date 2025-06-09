#pragma once
#include <string>

class url_codec {
public:
	static std::string encode(const std::string &src);

	static std::string decode(const std::string &src);

private:
	static const char HEX_CHARS[];
	static const std::array<bool, 256> unreserved_char_map;

	static char char2hex(unsigned char ch);

	static char hex2char(char hex);
};