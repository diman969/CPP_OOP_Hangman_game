#pragma once
#include <iostream>
#include "Encripter.h"
#include "DataBase.h"
#include "FileHandler.h"
#include "IWindowDecorator.h"
#include "JsonSerializer.h"
#include "WordCluePair.h"


#define CHAR_TO_SIZE_T(input) static_cast<size_t>((input) - '0')
#define MAX_LIVES 7

class Hangman
{
public:
	Hangman() :
		_curPlayer{	Player::getInstance()},
		_data{},
		_encripter{ Encripter::get() },
		_fileStream{FileHandler::get() },
		_mainMenuWindow{ new MenuDecorator{new TitleDecorator{new BorderDecorator(new Window())}} },
		_instructionsWindow{ new InstructionsDecorator{new BorderDecorator(new Window())} },
		_nameChangeWindow{ new NameChangeDecorator{new TitleDecorator{new BorderDecorator(new Window())}} },
		_gameWindow{ dynamic_cast<GameWindowDecorator*>(new GameWindowDecorator{new BorderDecorator{new Window()}}) },
		_statisticsWindow{ dynamic_cast<StatisticsDecorator*>(new StatisticsDecorator{new BorderDecorator{new Window()} }) }
	{
		_encripter.setKey("password");
		_fileStream.setFilePath("Data\\data.bin");
		loadData();
		srand(time(nullptr));
	};

	void hangmanGame();

	~Hangman() {
		delete _mainMenuWindow;
		delete _instructionsWindow;
		delete _nameChangeWindow;
		delete _gameWindow;
		delete _statisticsWindow;
	};

private:
	enum eMenuOptions{eStartGame = 1, eChangeName, eInstructions, eExit};

	Player& _curPlayer;
	DataBase<WordCluePair> _data;
	Encripter& _encripter;
	FileHandler& _fileStream;
	IWindow* _mainMenuWindow;
	IWindow* _instructionsWindow;
	IWindow* _nameChangeWindow;
	GameWindowDecorator* _gameWindow;
	StatisticsDecorator* _statisticsWindow;

	void startGame();
	void changePlayerName();
	void showInstructions() const;
	
	bool checkIfPlayerNameEntered() const;
	WordCluePair getRandomQuestion();
	std::string hideGuessWord(const std::string& word) const;
	
	char promptUserForGuessInput() const;
	bool validatePlayerInput(const std::string& enteredLetters, const char playerGuessLetter);
	bool checkIfLetterInTheWord(const std::string& guessWord, const char playerGuessLetter) const;
	void openLetterInHiddenWord(const std::string& guessWord, std::string& hiddenWord, const char playerGuessLetter);
	bool isWordGuessedCorrectly(const std::string& guessWord, const std::string& hiddenWord) const;
	
	std::string stringToUpperCase(const std::string& originalString) const;
	size_t generateRandomNumber(const size_t maxValue) const;
	void createBackup();
	void loadData();
};

