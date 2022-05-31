#pragma once
#include <vector>
#include <initializer_list>
#include "JSonConvertible.h"

template<typename T, typename T1 = void>
class DataBase
{
public:
	DataBase() : _data{} {};
	DataBase(const std::initializer_list<T> list) : _data{} {
		for (auto elem : list) {
			_data.push_back(elem);
		}
	}
	std::vector<T> data() const {
		return _data;
	}
	std::vector<T>& data() {
		return _data;
	}

	void push_back(const T& obj) {
		_data.push_back(obj);
	}

	T& operator[](const size_t& i) {
		return _data[i];
	}
	size_t size() const {
		return _data.size();
	}

	auto begin() {
		return _data.begin();
	}
	auto end() {
		return _data.end();
	}
	auto at(const size_t value) {
		return _data.at(value);
	}
	auto clear() {
		_data.clear();
	}

	~DataBase() = default;
private:
	std::vector<T> _data;
};

template<typename T>
class DataBase<T, onlyIfJsonConvertible<T>> : public JsonConvertible
{
public:
	DataBase() : _data{} {};
	explicit DataBase(const std::initializer_list<T>& list) : _data{}
	{
		for (auto& elem : list) {
			_data.push_back(elem);
		}
	}
	std::vector<T> data() const {
		return _data;
	}
	std::vector<T>& data() {
		return _data;
	}
	void push_back(const T& obj) {
		_data.push_back(obj);
	}

	T& operator[](const size_t& i) {
		return _data[i];
	}
	size_t size() const {
		return _data.size();
	}

	auto begin() {
		return _data.begin();
	}
	auto end() {
		return _data.end();
	}
	auto at(const size_t value) {
		return _data.at(value);
	}
	auto clear() {
		_data.clear();
	}
	~DataBase() = default;
	DynamicJsonDocument toJson() const override {
		size_t noOfItems{ _data.size() };

		DynamicJsonDocument jsonDoc(noOfItems * ONE_KILOBYTE);

		jsonDoc["No of items: "] = noOfItems;

		JsonArray itemsArr = jsonDoc.createNestedArray("Items: ");

		DynamicJsonDocument item(ONE_KILOBYTE);
		for (auto item : _data) {
			itemsArr.add(item.toJson());
		}
		return jsonDoc;
	}
	void fromJson(const DynamicJsonDocument& jsonDoc) override {
		if (jsonDoc.containsKey("No of items: ") && jsonDoc.containsKey("Items: ")) {

			size_t noElems{ jsonDoc["No of items: "] };
			T newItem{};

			DynamicJsonDocument tempJsonDoc(ONE_KILOBYTE);

			for (size_t i{}; i < noElems; i++) {
				tempJsonDoc = jsonDoc["Items: "][i];
				newItem.fromJson(tempJsonDoc);
				_data.push_back(newItem);
			};
		}
		else {
			throw std::exception("Corrupt itemsArr!");
		}
	}
private:
	std::vector<T> _data;
};

