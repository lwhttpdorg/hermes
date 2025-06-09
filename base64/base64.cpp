#include <stdexcept>
#include "base64.h"

#include <algorithm>

namespace {
	/**
	 * This array is a lookup table that translates 6-bit positive integer
	 * index values into their "Base64 Alphabet" equivalents as specified
	 * in "Table 1: The Base64 Alphabet" of RFC 2045 (and RFC 4648).
	 */
	constexpr char BASE64_TBL[64] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', /* 00 - 07 */
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', /* 08 - 15 */
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', /* 16 - 23 */
		'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', /* 24 - 31 */
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', /* 32 - 39 */
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v', /* 40 - 47 */
		'w', 'x', 'y', 'z', '0', '1', '2', '3', /* 48 - 55 */
		'4', '5', '6', '7', '8', '9', '+', '/' /*  56 - 63 */
	};

	char b64_to_val(char b64) {
		char ch;
		if (b64 >= '0' && b64 <= '9') {
			ch = static_cast<char>(b64 + 4);
		}
		else if (b64 >= 'A' && b64 <= 'Z') {
			ch = static_cast<char>(b64 - 65);
		}
		else if (b64 >= 'a' && b64 <= 'z') {
			ch = static_cast<char>(b64 - 71);
		}
		else if (b64 == '+') {
			ch = 62;
		}
		else if (b64 == '/') {
			ch = 63;
		}
		else if (b64 == '=') {
			ch = 0;
		}
		else {
			throw std::invalid_argument("Invalid base64 character");
		}
		return ch;
	}
}

std::string base64::standard_encoder::encode(const std::string &src) {
	if (src.empty()) {
		throw std::invalid_argument("Input string cannot be empty");
	}
	std::string encoded;
	encoded.reserve(((src.size() + 2) / 3) * 4);

	const size_t len = src.size();
	size_t i = 0;
	while (i + 3 <= len) {
		unsigned char b1 = src[i];
		unsigned char b2 = src[i + 1];
		unsigned char b3 = src[i + 2];

		encoded.push_back(BASE64_TBL[b1 >> 2]);
		encoded.push_back(BASE64_TBL[(b1 & 0x03) << 4 | b2 >> 4]);
		encoded.push_back(BASE64_TBL[(b2 & 0x0F) << 2 | b3 >> 6]);
		encoded.push_back(BASE64_TBL[b3 & 0x3F]);
		i += 3;
	}
	size_t rem = len - i;
	if (rem > 0) {
		unsigned char b1 = src[i];
		encoded.push_back(BASE64_TBL[b1 >> 2]);
		if (rem == 1) {
			encoded.push_back(BASE64_TBL[(b1 & 0x03) << 4]);
			encoded.append("==");
		}
		else {
			// rem == 2
			unsigned char b2 = src[i + 1];
			encoded.push_back(BASE64_TBL[((b1 & 0x03) << 4) | (b2 >> 4)]);
			encoded.push_back(BASE64_TBL[(b2 & 0x0F) << 2]);
			encoded.push_back('=');
		}
	}
	return encoded;
}

std::string base64::standard_decoder::decode(const std::string &src) {
	if (src.empty()) {
		throw std::invalid_argument("Input string cannot be empty");
	}

	std::string decoded;
	decoded.reserve((src.size() / 4) * 3);

	for (size_t i = 0; i < src.size(); i += 4) {
		char c0 = b64_to_val(src[i]);
		char c1 = b64_to_val(src[i + 1]);
		char c2 = b64_to_val(src[i + 2]);
		char c3 = b64_to_val(src[i + 3]);

		decoded.push_back(static_cast<char>(c0 << 2 | ((0x30 & c1) >> 4)));
		if (src[i + 2] != '=') {
			decoded.push_back(static_cast<char>((0x0f & c1) << 4 | (0x3c & c2) >> 2));
		}
		if (src[i + 3] != '=') {
			decoded.push_back(static_cast<char>((0x03 & c2) << 6 | (0x3f & c3)));
		}
	}
	return decoded;
}

std::string base64::url_safe_encoder::encode(const std::string &src) {
	/* It's the lookup table for "URL and Filename safe Base64" as specified
	 * in Table 2 of the RFC 4648, with the '+' and '/' changed to '-' and '_'*/
	std::string encoded = standard_encoder::encode(src);
	std::replace(encoded.begin(), encoded.end(), '+', '-');
	std::replace(encoded.begin(), encoded.end(), '/', '_');
	return encoded;
}

std::string base64::url_safe_decoder::decode(const std::string &src) {
	std::string temp(src);
	std::replace(temp.begin(), temp.end(), '-', '+');
	std::replace(temp.begin(), temp.end(), '_', '/');
	return standard_decoder::decode(temp);
}

base64::encoder &base64::get_encoder() {
	static standard_encoder encoder;
	return encoder;
}

base64::encoder &base64::get_url_encoder() {
	static url_safe_encoder encoder;
	return encoder;
}

base64::decoder &base64::get_decoder() {
	static standard_decoder decoder;
	return decoder;
}

base64::decoder &base64::get_url_decoder() {
	static url_safe_decoder decoder;
	return decoder;
}
