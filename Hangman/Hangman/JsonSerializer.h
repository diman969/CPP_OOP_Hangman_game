#pragma once
#include <string>
#include "JSonConvertible.h"

class JsonSerializer {
public:

	static std::string serialize(const DynamicJsonDocument& jsonDoc) {
		std::string jsonStr{};

		serializeJson(jsonDoc, jsonStr);

		return jsonStr;
	}
	static DynamicJsonDocument deserialize(const std::string& jsonStr) {
		size_t noElemsInJSonStr{ calcsNoElemsInJSonStr(jsonStr) };
		size_t JSonDataSize{ noElemsInJSonStr * ONE_KILOBYTE };

		DynamicJsonDocument jsonDoc(JSonDataSize);

		deserializeJson(jsonDoc, jsonStr);
		return jsonDoc;
	}

private:
	static size_t calcsNoElemsInJSonStr(const std::string& data) {
		size_t count{};
		size_t curPos{ data.find('{') };

		while (curPos != std::string::npos) {
			count++;
			curPos = data.find('{', curPos + 1);
		}
		return count;
	};
};