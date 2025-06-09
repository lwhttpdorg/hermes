# Hermes

## What is Hermes?

Hermes is a C++ library for Base64 encoding/decoding and URL encoding/decoding (percent-encoding).

## How to use?

### Base64 Encoding and Decoding

Standard Base64 Encoding:

```c++
std::string text = "The quick brown fox jumps over the lazy dog敏捷的棕色狐狸跨过懒狗";

base64::encoder &encoder = base64::get_encoder();
std::string encoded = encoder.encode(text);
std::cout << encoded << std::endl;
// Alternatively:
std::string encoded = base64::get_encoder().encode(text);
```

Standard Base64 Decoding:

```c++
base64::decoder &decoder = base64::get_decoder();
std::string decoded = decoder.decode(encoded);
std::cout << decoded << std::endl;
// Alternatively:
std::string decoded = dbase64::get_decoder().decode(encoded);
```

URL-safe Base64 Encoding:

```c++
base64::encoder &encoder = base64::get_url_encoder();
std::string url_encoded = encoder.encode(text);
std::cout << url_encoded << std::endl;
// Alternatively:
std::string url_encoded = base64::get_url_encoder().encode(text);
```

URL-safe Base64 Decoding:

```c++
base64::decoder &decoder = base64::get_url_decoder();
std::string decoded = decoder.decode(encoded);
std::cout << decoded << std::endl;
// Alternatively:
std::string decoded = base64::get_url_decoder().decode(encoded);
```

### URL Encoding and Decoding

```c++
std::string text = "The quick brown fox jumps over the lazy dog敏捷的棕色狐狸跨过懒狗";

std::string encoded = url_codec::encode(text);
std::cout << encoded << std::endl;
std::string decoded = url_codec::decode(encoded);
std::cout << decoded << std::endl;
```

### CMake

```cmake
cmake_minimum_required(VERSION 3.10)
project(demo LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
		hermes
		GIT_REPOSITORY https://github.com/lwhttpdorg/hermes.git
		GIT_TAG main
)
FetchContent_MakeAvailable(hermes)

add_executable(demo main.cpp)
target_link_libraries(demo hermes)
```

```c++
#include <iostream>
#include <ostream>

#include <base64.h>
#include <url_codec.h>

int main() {
	std::string text = "The quick brown fox jumps over the lazy dog敏捷的棕色狐狸跨过懒狗";
	std::string encoded = base64::get_encoder().encode(text);
	std::cout << encoded << std::endl;
	std::string decoded = base64::get_decoder().decode(encoded);
	std::cout << decoded << std::endl;
	
	std::string url_encoded = base64::get_url_encoder().encode(text);
	std::cout << url_encoded << std::endl;
	decoded = base64::get_url_decoder().decode(encoded);
	std::cout << decoded << std::endl;

	encoded = url_codec::encode(text);
	std::cout << encoded << std::endl;
	decoded = url_codec::decode(encoded);
	std::cout << decoded << std::endl;

	return 0;
}
```
