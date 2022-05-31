#pragma once
#include "FileIOStreamHandler.h"

class FileHandler {
public:
	static FileHandler& get() {
		static FileHandler instance{};
		return instance;
	}
	
	void setFilePath(const std::string& filename) {
		_fileName = filename;
	}
	std::string filePath() {
		return _fileName;
	}
	
	bool openFile() {
		if (!_file.is_open()) {
			_file.exceptions(std::fstream::badbit | std::fstream::failbit);
			_file.open(_fileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
		}
		return _file.is_open();
	}
	bool closeFile() {
		if (_file.is_open()) {
			_file.close();
		}
		return _file.is_open();
	}
	bool eraseFile() {
		bool isErased{};
		if (_file.is_open()) {
			_file.close();
			_file.open(_fileName, std::ios::out | std::ios::trunc);
			_file.close();
			openFile();
			isErased = true;
		}
		return isErased;
	}

	template<typename T>
	bool writeToFile(const T& dataToWrite) {
		bool isWritten{};
		if (_file.is_open()) {
			isWritten = FileStreamHandler<T>::writeToFile(_file, dataToWrite);
		}
		return isWritten;
	}

	template<typename T>
	void readFromFile(T& dataToRead) {
		if (_file.is_open()) {
			_file.seekg(std::ios::beg);
			FileStreamHandler<T>::readFromFile(_file, dataToRead);
		}
	}

	FileHandler(const FileHandler& other) = delete;
	FileHandler(FileHandler&& other) = delete;
	FileHandler& operator=(const FileHandler& other) = delete;
private:
	FileHandler() :
		_file{},
		_fileName{}
	{};

	std::fstream _file;
	std::string _fileName;
};
