#pragma once
#include <fstream>
#include <string>

template<typename T>
using onlyIfString =
std::enable_if_t<std::is_same_v<T, std::string>>;

template<typename T>
using onlyIfValueType =
std::enable_if_t<std::is_arithmetic_v<T> == true>;


template<typename T, typename U = void>
class FileStreamHandler
{
public:
	bool writeToFile(std::fstream& destination, const T& dataIntoFile) {

		auto originalPosInFile{ destination.tellp() };
		uint32_t dataSizeInBytes{ sizeof(dataIntoFile) };

		destination.write(reinterpret_cast<const char*>(&dataIntoFile), dataSizeInBytes);

		uint32_t bytesWritten{ static_cast<uint32_t>(destination.tellp() - originalPosInFile) };

		return bytesWritten == dataSizeInBytes;
	}
	bool readFromFile(std::fstream& source, T& dataOutOfFile) {
		auto originalPosInFile{ source.tellg() };
		uint32_t dataSizeInBytes{ sizeof(dataOutOfFile) };
		source.read(reinterpret_cast<char*>(&dataOutOfFile), dataSizeInBytes);
		uint32_t bytesRead{ reinterpret_cast<uint32_t>(source.tellg() - originalPosInFile) };

		return bytesRead == dataSizeInBytes;
	}
};

template<typename T>
class FileStreamHandler<T, onlyIfValueType<T>>
{
public:
	static bool writeToFile(std::fstream& destination, const T& dataIntoFile) {
		const uint32_t valueSizeInBytes{ sizeof(dataIntoFile) };
		auto originalPosInFile = destination.tellp();

		destination.write(reinterpret_cast<const char*>(&dataIntoFile), valueSizeInBytes);

		uint32_t bytesWritten{ static_cast<uint32_t>(destination.tellp() - originalPosInFile) };
		return bytesWritten == valueSizeInBytes;
	}

	static bool readFromFile(std::fstream& source, T& dataOutOfFile) {

		const uint32_t valueSizeInBytes{ sizeof(dataOutOfFile) };
		auto curPosInFile = source.tellg();

		source.read(reinterpret_cast<char*>(&dataOutOfFile), valueSizeInBytes);

		uint32_t bytesRead{ static_cast<uint32_t>(source.tellg() - curPosInFile) };
		return bytesRead == valueSizeInBytes;
	}
};

template<typename T>
class FileStreamHandler<T, onlyIfString<T>>
{
public:
	static bool writeToFile(std::fstream& destination, const T& dataIntoFile) {
		const uint32_t textLength{ (uint32_t)dataIntoFile.size() };
		std::streampos originalPosInFile{};
		uint32_t bytesWritten{};
		if (textLength) {
			if (FileStreamHandler<uint32_t>::writeToFile(destination, textLength)) {
				originalPosInFile = destination.tellp();

				destination.write(reinterpret_cast<const char*>(dataIntoFile.data()), textLength);

				bytesWritten  = static_cast<uint32_t>(destination.tellp() - originalPosInFile);
			}
		}
		return bytesWritten == textLength;
	}
	static bool readFromFile(std::fstream& source, T& dataOutOfFile) {
		uint32_t textLength{};
		std::streampos originalPosInFile{};
		uint32_t bytesRead{};
		if (FileStreamHandler<uint32_t>::readFromFile(source, textLength))
		{
			if (textLength) {
				char* readData = new char[textLength + 1]{};
				originalPosInFile = source.tellg();
				source.read(reinterpret_cast<char*>(readData), textLength);
				bytesRead = static_cast<uint32_t>(source.tellg() - originalPosInFile);
				readData[textLength] = '\0';
				std::string temp(&readData[0], &readData[0] + textLength);
				delete[] readData;
				dataOutOfFile = temp;
			}
		}

		return bytesRead == textLength;

	}
};

