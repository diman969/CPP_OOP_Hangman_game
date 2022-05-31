#pragma once
#include "FileIOStreamHandler.h"

namespace MyFunctions {
	template<typename T>
	bool writeToFile(std::fstream& _file, const T& value) {
		return FileStreamHandler<T>::writeToFile(_file, value);
	}

	template<typename T>
	bool readFromFile(std::fstream& _file, T& value) {
		return FileStreamHandler<T>::readFromFile(_file, value);
	}
}