#include "Hangman.h"

void Hangman::hangmanGame()
{
	char playerInput{};
	size_t playerMenuChoice{};

	while (playerMenuChoice != eExit)
	{
		_mainMenuWindow->draw();

		playerInput = _getch();
		
		playerMenuChoice = CHAR_TO_SIZE_T(playerInput);

		switch (playerMenuChoice) {
		case eStartGame:
			startGame();
			break;
		case eChangeName:
			changePlayerName();
			break;
		case eInstructions:
			showInstructions();
			break;
		default:
			break;
		}
		system("cls");
	}
	
	system("cls");
	std::cout << "Good Bye!\n";
}

void Hangman::startGame()
{
	if (checkIfPlayerNameEntered() == false) {
		changePlayerName();
	}

	WordCluePair curQuestion{ getRandomQuestion() };

	_curPlayer.statistics().setBegingParams(curQuestion.word(), curQuestion.clue());
	
	std::string guessWord{ stringToUpperCase(curQuestion.word()) };

	std::string hiddenGuessWord{ hideGuessWord(guessWord) };
	std::string wordClue{ curQuestion.clue() };

	char playerGuessInput{};

	size_t noOfLivesLeft{ MAX_LIVES };

	_gameWindow->draw(hiddenGuessWord, wordClue, MAX_LIVES);

	std::string playersGuessLetters{};
	bool isWon{};

	while (!isWon && noOfLivesLeft)
	{
		_gameWindow->drawUserGuessInputField();

		playerGuessInput = promptUserForGuessInput();

		if (validatePlayerInput(playersGuessLetters, playerGuessInput)) {
			
			playersGuessLetters.push_back(playerGuessInput);

			bool isGoodGuess = checkIfLetterInTheWord(guessWord, playerGuessInput);

			if (isGoodGuess) {
				openLetterInHiddenWord(guessWord, hiddenGuessWord, playerGuessInput);

				_gameWindow->drawHiddenWordField(hiddenGuessWord);

				if (isWordGuessedCorrectly(guessWord, hiddenGuessWord)) {
					isWon = 1;
				}
			}
			else {
				noOfLivesLeft--;
				_curPlayer.statistics().addWrongLetter(playerGuessInput);
				_gameWindow->drawHangerField(noOfLivesLeft);
			}

			_gameWindow->drawGuessResult(isGoodGuess);
			_gameWindow->drawLivesLeftField(noOfLivesLeft);
		}
		else {
			_gameWindow->drawInvalidInput();
		}
	}
	_curPlayer.statistics().setEndingParams(isWon, MAX_LIVES - noOfLivesLeft);
	
	_gameWindow->drawGameResultField(isWon);
	
	_getch();

	_statisticsWindow->draw();

	_getch();
}
void Hangman::changePlayerName() {
	bool isValid{};
	std::string newName{};
	while (!isValid) {
		_nameChangeWindow->draw();
	
		std::getline(std::cin, newName);
		for (auto letter : newName) {
			if (isalpha(letter)) {
				isValid = true;
				break;
			}
		}
	}
	_curPlayer.setsName(newName);
}
void Hangman::showInstructions() const {
	_instructionsWindow->draw();
}

bool Hangman::checkIfPlayerNameEntered() const {
	return _curPlayer.name().length();
}
WordCluePair Hangman::getRandomQuestion() {
	size_t questionNo{ generateRandomNumber(_data.size()) };
	return _data.at(questionNo);
}
std::string Hangman::hideGuessWord(const std::string& word) const {
	std::string result(word.length(), '*');
	return result;
}

char Hangman::promptUserForGuessInput() const {
	char userInput{};
	std::cout << "Enter your letter : ";
	userInput = _getche();
	return toupper(userInput);
}
bool Hangman::validatePlayerInput(const std::string& allPlayersGuessLetters, const char playerGuessLetter) {
	bool isLetter = isalpha(playerGuessLetter);
	bool isUniqueLetter{ allPlayersGuessLetters.find_first_of(playerGuessLetter) == std::string::npos };
	return  isUniqueLetter && isLetter;
}
bool Hangman::checkIfLetterInTheWord(const std::string& guessWord, const char playerGuessLetter) const {
	return (guessWord.find(playerGuessLetter) != std::string::npos);
}
void Hangman::openLetterInHiddenWord(const std::string& guessWord, std::string& hiddenWord, const char playerGuessLetter)
{
	size_t foundAt{ guessWord.find(playerGuessLetter) };

	while (foundAt != std::string::npos) {
		hiddenWord.at(foundAt) = playerGuessLetter;
		foundAt = guessWord.find(playerGuessLetter, ++foundAt);
	}
}
bool Hangman::isWordGuessedCorrectly(const std::string& guessWord, const std::string& hiddenWord) const
{
	bool areTheSame{1};
	for (size_t i{}; i < guessWord.length(); i++) {
		if (tolower(guessWord[i]) != tolower(hiddenWord[i])) {
			areTheSame = false;
			break;
		}
	}
	return areTheSame;
}

std::string Hangman::stringToUpperCase(const std::string& stringToConvert) const {
	std::string result{ stringToConvert };
	size_t resultLength{ result.length() };
	for (size_t i{}; i < resultLength; i++) {
		result.at(i) = toupper(result.at(i));
	}
	return result;
}
size_t Hangman::generateRandomNumber(const size_t maxValue) const {
	return rand() % maxValue;
}

void Hangman::createBackup() {
	
	DataBase<WordCluePair> backUp{
		WordCluePair{"Inheritance", "C++ OPP concept"},
		WordCluePair{"Polymorphism", "C++ OOP concept"},
		WordCluePair{"Encapsulation", "C++ OOP concept"},
		WordCluePair{"Constructor", "Method that builds object of a class/struct"},
		WordCluePair{"Destructor", "Method that destroyes object of a class/struct"},
		WordCluePair{"Arguments", "Parameters of the function"},
		WordCluePair{"Pointer", "Stores address of the variable/function"},
		WordCluePair{"Concatenate", "Glue strings together"},
		WordCluePair{"Variable", "Stores data in memory"},
		WordCluePair{"Method", "Function of a class in C++"},
		WordCluePair{"Class", "Blueprint to an object"},
		WordCluePair{"Bitwise", "Operations performed on a data on bit level"},
		WordCluePair{"Double", "Holds float point value in memory"},
		WordCluePair{"Recursive", "Function that calls it self"},
		WordCluePair{"Constant", "Data that can not be changed throught program"},
		WordCluePair{"Enumerator", "Syntactic sugar"},
		WordCluePair{"Macro", "Defines are..."},
		WordCluePair{"Lambda", "Anonymous function called after greek letter"}
	};
	DynamicJsonDocument jsonDoc(backUp.toJson());

	std::string jsonStr(JsonSerializer::serialize(jsonDoc));

	_fileStream.eraseFile();
	jsonStr = _encripter.encript(jsonStr);
	_fileStream.writeToFile(jsonStr);
}
void Hangman::loadData() {
	
	std::string jsonStr{};
	_fileStream.openFile();
	try {
		_fileStream.readFromFile(jsonStr);
		jsonStr = _encripter.encript(jsonStr);
		DynamicJsonDocument jsonDoc{ JsonSerializer::deserialize(jsonStr) };
		_data.fromJson(jsonDoc);
	}
	catch (...) {
		createBackup();
		loadData();
	}
	_fileStream.closeFile();
}
