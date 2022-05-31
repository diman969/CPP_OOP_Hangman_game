#pragma once
#include <string>

class Encripter
{
public:
	static Encripter& get() {
		static Encripter instance{};
		return instance;
	}
	
	void setKey(const std::string& newKey) {
		_key = newKey;
	}
	std::string key() {
		return _key;
	}
	
	std::string encript(const std::string& text) {
		std::string encriptedText{ text };

		size_t keyLength{ _key.length() };

		if (keyLength) {
			auto keyIterator{ _key.cbegin() };

			for (auto& symbol : encriptedText) {
				symbol = symbol ^ (*keyIterator);
				keyIterator++;
				if (keyIterator == _key.end()) {
					keyIterator = _key.cbegin();
				}
			}
		}
		return encriptedText;
	}

	Encripter(const Encripter& other) = delete;
	Encripter(Encripter&& other) = delete;
	Encripter& operator=(const Encripter& other) = delete;
private:
	Encripter() :
		_key{}
	{};
	std::string _key;
};
