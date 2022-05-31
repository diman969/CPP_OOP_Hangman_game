#pragma once
#include "ArduinoJson-v6.19.4.h"

#define ONE_KILOBYTE 1024
#define JSON_OBJECT_OPEN_BRACKET '{'

class JsonConvertible {
public:
	virtual DynamicJsonDocument toJson() const = 0;
	virtual void fromJson(const DynamicJsonDocument& data) = 0;
};

template<typename T>
using onlyIfJsonConvertible =
	std::enable_if_t<std::is_base_of_v<JsonConvertible, T>>;

