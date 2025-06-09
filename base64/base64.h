#pragma once

#include <string>

class base64 {
public:
	class encoder {
	public:
		virtual ~encoder() = default;

		virtual std::string encode(const std::string &src) = 0;
	};

	class decoder {
	public:
		virtual ~decoder() = default;

		virtual std::string decode(const std::string &src) = 0;
	};

private:
	class standard_encoder : public encoder {
	public:
		std::string encode(const std::string &src) override;
	};

	class standard_decoder : public decoder {
	public:
		std::string decode(const std::string &src) override;
	};

	class url_safe_encoder : public standard_encoder {
	public:
		std::string encode(const std::string &src) override;
	};

	class url_safe_decoder : public standard_decoder {
	public:
		std::string decode(const std::string &src) override;
	};

public:
	static encoder &get_encoder();

	static encoder &get_url_encoder();

	static decoder &get_decoder();

	static decoder &get_url_decoder();
};
