#include <array>
#include <stdexcept>

#include "url_codec.h"

const char url_codec::HEX_CHARS[] = "0123456789ABCDEF";

const std::array<bool, 256> url_codec::unreserved_char_map = []()
{
	std::array<bool, 256> map{};
	for (int i = 'a'; i <= 'z'; ++i) map[i] = true;
	for (int i = 'A'; i <= 'Z'; ++i) map[i] = true;
	for (int i = '0'; i <= '9'; ++i) map[i] = true;
	map['.'] = true;
	map['-'] = true;
	map['*'] = true;
	map['_'] = true;
	map['!'] = true;
	map['~'] = true;
	return map;
}();

char url_codec::char2hex(unsigned char ch) {
	return HEX_CHARS[ch & 0x0F];
}

char url_codec::hex2char(char hex) {
	char ch = -1;
	if ((('A' <= hex) && (hex <= 'F')) || (('a' <= hex) && (hex <= 'f'))) {
		ch = static_cast<char>(hex - 'A' + 10);
	}
	else if (('0' <= hex) && (hex <= '9')) {
		ch = static_cast<char>(hex - '0');
	}
	return ch;
}

std::string url_codec::encode(const std::string &src) {
	size_t len = src.length();
	std::string encoded;
	encoded.reserve(len * 3);
	for (size_t i = 0; i < len; ++i) {
		if (unreserved_char_map[static_cast<unsigned char>(src[i])]) {
			encoded.push_back(src[i]);
		}
		else {
			encoded.push_back('%');
			encoded.push_back(char2hex(static_cast<unsigned char>(src[i]) >> 4));
			encoded.push_back(char2hex(static_cast<unsigned char>(src[i]) & 0x0F));
		}
	}

	return encoded;
}

std::string url_codec::decode(const std::string &src) {
	size_t len = src.length();
	std::string decoded;
	decoded.reserve(len);
	size_t i = 0;
	while (i < len) {
		if ('+' == src[i]) {
			decoded.push_back(' ');
			++i;
		}
		else if (('%' == src[i]) && (i + 2 < len)) {
			char high_nibble = hex2char(src[i + 1]);
			char low_nibble = hex2char(src[i + 2]);

			if (high_nibble == -1 || low_nibble == -1) {
				throw std::invalid_argument("URL decoding failed: Invalid percent-encoded sequence");
			}
			decoded.push_back(static_cast<char>((high_nibble << 4) | low_nibble));
			i += 3;
		}
		else {
			decoded.push_back(src[i]);
			++i;
		}
	}

	return decoded;
}
