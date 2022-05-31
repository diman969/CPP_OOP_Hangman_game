#pragma once
#include <string>
#include <time.h>

class Statistics {
public:
	Statistics() = default;

	std::string guessWord() const {
		return _guessWord;
	}

	std::string clue() const {
		return _clue;
	}

	std::string wrongLetters() const {
		return _wrongLetters;
	}

	void addWrongLetter(const char letter) {
		_wrongLetters.push_back(letter);
		_wrongLetters.push_back(' ');
	}

	std::string timeElapsed() const {
		return _timeElapsed;
	}

	size_t noOfTries() const {
		return _noOfTries;
	}

	size_t score() const {
		return _score;
	}

	size_t noOfWins() const {
		return _noOfWins;
	}

	size_t noOfLosses() const {
		return _noOfLosses;
	}

	bool isWon() const {
		return _gameResult;
	}

	bool isLetterRepeating(const char userLetter) const {
		return _wrongLetters.find_first_of(userLetter) != std::string::npos;
	}

	void setBegingParams(const std::string& guessWord, const std::string clue) {
		_wrongLetters.erase();
		_guessWord = guessWord;
		_clue = clue;
		time(&_startTime);
	}

	void setEndingParams(bool isWon, size_t noOfTries) {
		time(&_endTime);
		time_t timeElapsed{ _endTime - _startTime };
		_timeElapsed = convertsTimeStempToString(timeElapsed);

		_gameResult = isWon;
		_noOfTries = noOfTries;
		if (isWon) {
			_noOfWins++;
			_score += 100;
		}
		else {
			_noOfLosses++;
		}
	}
	~Statistics() = default;
private:
	std::string _guessWord;
	std::string _clue;
	std::string _wrongLetters;
	std::string _timeElapsed;
	time_t _startTime;
	time_t _endTime;
	size_t _noOfTries;
	size_t _score;
	size_t _noOfWins;
	size_t _noOfLosses;
	bool _gameResult;

	std::string convertsTimeStempToString(const time_t timeStemp) const {
		time_t temp{ timeStemp };

		size_t secsInMin{ 60 };
		size_t secs{ temp % secsInMin };
		temp /= secsInMin;
		size_t minsInHour{ 60 };
		size_t mins{ temp % minsInHour };
		size_t hours{ temp / minsInHour };

		std::string res{};
		if (hours) {
			res = std::to_string(hours) + " hours ";
		}
		if (mins) {
			res += std::to_string(mins) + " minutes ";
		}
		if (secs) {
			res += std::to_string(secs) + " seconds";
		}
		return res;
	}
};