# Hermes

## Hermes是什么?

Hermes是一个C++实现的base64编解码、URL编解码(百分号编码)库

## 如何使用?

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
