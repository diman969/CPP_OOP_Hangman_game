#pragma once
#include "JSonConvertible.h"

class WordCluePair : public JsonConvertible
{
public:
	explicit WordCluePair(const std::string& word, const std::string& clue) :
		_word{word},
		_clue{clue}
	{};
	WordCluePair() = default;

	void setWord(const std::string& word) {
		_word = word;
	}
	void setsClue(const std::string& clue) {
		_clue = clue;
	}

	std::string word() const {
		return _word;
	}
	std::string clue() const {
		return _clue;
	}
	
	DynamicJsonDocument toJson() const override {
		DynamicJsonDocument doc(ONE_KILOBYTE);
		doc["word: "] = _word;
		doc["clue: "] = _clue;
		return doc;
	}

	void fromJson(const DynamicJsonDocument& data) override {

		if (data.containsKey("word: ") && data.containsKey("clue: ")) {
			setWord(data["word: "]);
			setsClue(data["clue: "]);
		}
		else {
			throw std::exception("Corrupt data!");
		}
	}
	~WordCluePair() = default;
private:
	std::string _word;
	std::string _clue;
};


