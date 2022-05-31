#include "IWindowDecorator.h"

void IWindowDecorator::drawBorders(const size_t borderPosX, const size_t borderPosY, const size_t width, const size_t height) const
{
	setCoursorToXY(borderPosX, borderPosY);
	std::cout << BORDER_TOP_LEFT_CORNER;

	for (size_t i{}; i < width - 1; i++) {
		std::cout << BORDER_HORIZONTAL;
	}

	std::cout << BORDER_TOP_RIGHT_CORNER;

	for (size_t i{1}; i < height; i++)
	{
		setCoursorToXY(borderPosX, borderPosY + i);
		std::cout << BORDER_VERTICAL;
		setCoursorToXY(borderPosX + width, borderPosY + i);
		std::cout << BORDER_VERTICAL;
	}

	setCoursorToXY(borderPosX, borderPosY + height);
	std::cout << BORDER_BOTTOM_LEFT_CORNER;

	for (size_t i{}; i < width - 1; i++) {
		std::cout << BORDER_HORIZONTAL;
	}

	std::cout << BORDER_BOTTOM_RIGHT_CORNER;
}

void BorderDecorator::drawMainBorder() const {
	SET_TEXT_BLUE();
	static size_t mainBoarderPosX{};
	static size_t mainBoarderPosY{};

	drawBorders(mainBoarderPosX, mainBoarderPosY, innerField.noOfCols, innerField.noOfRows);
}

void TitleDecorator::drawTitle() const {
	const size_t noOfLinesInTitle{ 7 };
	const char* title[noOfLinesInTitle]{
		"HH    HH     AA     NN    NN     GGG    MM          MM     AA     NN    NN",
		"HH    HH   AA  AA   NNN   NN   GG   GG  MMM        MMM   AA  AA   NNN   NN",
		"HH    HH  AA    AA  NNNN  NN  GG        MMMM      MMMM  AA    AA  NNNN  NN",
		"HHHHHHHH  AAAAAAAA  NN NN NN  GG        MM MM    MM MM  AAAAAAAA  NN NN NN",
		"HH    HH  AA    AA  NN  NNNN  GG   GGG  MM  MM  MM  MM  AA    AA  NN  NNNN",
		"HH    HH  AA    AA  NN   NNN   GG   GG  MM   MMMM   MM  AA    AA  NN   NNN",
		"HH    HH  AA    AA  NN    NN     GGG    MM    MM    MM  AA    AA  NN    NN"
	};
	const size_t titleWidth{ strlen(title[0]) };
	size_t titlePosX{ (innerField.noOfCols - titleWidth) / 2};
	for (size_t curLine{}; curLine < noOfLinesInTitle; curLine++)
	{
		SET_TEXT_RED();
		setCoursorToXY(titlePosX, 1 + curLine);
		std::cout << title[curLine];
	}
}

void MenuDecorator::drawMenu() const {
	SET_TEXT_BLUE();
	size_t menuLineAvgLen{ 20 };
	size_t noOfLinesInMenu{ 4 };
	size_t linePadding{ 2 };

	size_t menuBorderWidth{ menuLineAvgLen + BORDER_PADDING };
	size_t menuBorderHeight{ noOfLinesInMenu * linePadding + BORDER_PADDING };

	size_t menuBorderPosX{ (innerField.noOfCols - menuBorderWidth) / 2 };
	size_t menuBorderPosY{ TITLE_HEIGHT + (innerField.noOfRows - TITLE_HEIGHT - menuBorderHeight) / 2 };
	drawBorders(menuBorderPosX, menuBorderPosY, menuBorderWidth, menuBorderHeight);


	size_t horizontalOffset{ (menuBorderWidth - menuLineAvgLen) / 2 + BORDER_PADDING / 2};
	size_t verticalOffset{ (menuBorderHeight - (noOfLinesInMenu * linePadding)) / 2  + BORDER_PADDING / 2};

	size_t menuPosX{ menuBorderPosX + horizontalOffset };
	size_t playGamePosY{ menuBorderPosY + verticalOffset };

	setCoursorToXY(menuPosX, playGamePosY);
	std::cout << "(1)->  Play game ";

	size_t changeNamePosY{ playGamePosY + linePadding };
	setCoursorToXY(menuPosX, changeNamePosY);
	std::cout << "(2)->  Change Names ";

	size_t instructionsPosY{ changeNamePosY + linePadding };
	setCoursorToXY(menuPosX, instructionsPosY);
	std::cout << "(3)->  How to play";

	size_t wordPosY{ instructionsPosY + linePadding };
	setCoursorToXY(menuPosX, wordPosY);
	std::cout << "(4)->  Exit ";
}

void InstructionsDecorator::drawInstructions() const
{
	SET_TEXT_RED();

	const size_t noOfLiesInInstructions{ 11 };
	const char* _instructionsWindow[noOfLiesInInstructions]{
		":: HANGMAN ::",
		"",
		"In this game, you have to hiddenWord a word!",
		"",
		"You will have 7 tries to hiddenWord the word.",
		"If you guessed the word, you won the round!",
		"",
		"But if you were unable to hiddenWord the word and",
		"little guy was hanged, you loose the round!",
		"",
		"Enjoy!"
	};
	size_t instructionsPosY{ (innerField.noOfRows - noOfLiesInInstructions) / 2 };
	size_t instructionsPosX{};
	for (size_t curLine{}; curLine < noOfLiesInInstructions; curLine++) {
		size_t lineLength{ strlen(_instructionsWindow[curLine]) };
		if (lineLength) {
			instructionsPosX = (innerField.noOfCols - lineLength) / 2 + BORDER_PADDING * 2;
			setCoursorToXY(instructionsPosX, instructionsPosY + curLine);
			std::cout << _instructionsWindow[curLine];
		}
	}
	_getch();
}

void NameChangeDecorator::drawNameChangeWindow() const {
	SET_TEXT_RED();

	std::string fieldTitle{ "Enter Your Name : " };
	size_t fieldTitlePosX{ ((innerField.noOfCols - fieldTitle.length()) / 2) - AVERAGE_NAME_LENGTH + BORDER_PADDING * 2};
	size_t fieldTitlePosY{ ((innerField.noOfRows - TITLE_HEIGHT) / 2) + TITLE_HEIGHT };
	setCoursorToXY(fieldTitlePosX, fieldTitlePosY);
	SET_TEXT_BLUE();
	std::cout << fieldTitle;
}

void GameWindowDecorator::draw(const std::string& hiddenWord, const std::string& clue, const size_t noOfLivesLeft) const {
	system("cls");
	draw();
	drawHiddenWordField(hiddenWord);
	drawClueField(clue);
	drawLivesLeftField(noOfLivesLeft);
	drawHangerField(noOfLivesLeft);
}
void GameWindowDecorator::drawHiddenWordField(const std::string& hiddenWord) const {
	const char* fieldTitle{ "Word : " };

	size_t wordLength{ hiddenWord.length() };
	size_t fieldTitleLength{ strlen(fieldTitle) };

	size_t fieldBorderHeight{ 4 };
	size_t fieldBorderWidth{ wordLength + fieldTitleLength + BORDER_PADDING * 2 };

	size_t fieldBorderPosX{ 10 };
	size_t fieldBorderPosY{ 2 };

	drawBorders(fieldBorderPosX, fieldBorderPosY, fieldBorderWidth, fieldBorderHeight);

	size_t fieldTitlePosX{ fieldBorderPosX + BORDER_PADDING };
	size_t fieldTitlePosY{ fieldBorderPosY + BORDER_PADDING };

	setCoursorToXY(fieldTitlePosX, fieldTitlePosY);

	std::cout << fieldTitle << hiddenWord;
};
void GameWindowDecorator::drawClueField(const std::string& clue) const {
	size_t cluePosX{ 12 };
	size_t cluePosY{ 8 };
	setCoursorToXY(cluePosX, cluePosY);

	std::cout << "Clue : " << clue;
};
void GameWindowDecorator::drawLivesLeftField(const size_t noOfLIvesLeft) const {
	const char* fieldTitle{ "Lives : " };

	size_t fieldBorderPosX{ 56 };
	size_t fieldBorderPosY{ 2 };

	size_t fieldBorderWidth{ 14 };
	size_t fieldBorderHeight{ 4 };

	drawBorders(fieldBorderPosX, fieldBorderPosY, fieldBorderWidth, fieldBorderHeight);

	size_t fieldTitlePosX{ 58 };
	size_t fieldTitlePosY{ 4 };

	setCoursorToXY(fieldTitlePosX, fieldTitlePosY);
	std::cout << fieldTitle << noOfLIvesLeft;
}
void GameWindowDecorator::drawHangerField(const size_t noOfLivesLeft) const
{
	size_t hangBorderPosX{ 45 };
	size_t hangBorderPosY{ 10 };
	size_t hangBorderWidth{ 25 };
	size_t hangBorderHeight{ 17 };

	const size_t noOfRowsInHang{ 12 };
	const size_t noOfColsInHang{ 20 };

	drawBorders(hangBorderPosX, hangBorderPosY, hangBorderWidth, hangBorderHeight);

	char hang[noOfRowsInHang][noOfColsInHang]{
		" _____________    ",
		" |           |    ",
		" |           |    ",
		"             |    ",
		"             |    ",
		"             |    ",
		"             |    ",
		"             |    ",
		"             |    ",
		"             |    ",
		"             |    ",
		"         ---------"
	};

	size_t maxLives{ 7 };

	if (noOfLivesLeft < maxLives) {
		if (noOfLivesLeft <= 6) {
			hang[3][1] = 'O';
		}
		if (noOfLivesLeft <= 5) {
			hang[4][1] = '|';
		}
		if (noOfLivesLeft <= 4) {
			hang[4][0] = '/';
		}
		if (noOfLivesLeft <= 3) {
			hang[4][2] = '\\';
		}
		if (noOfLivesLeft <= 2) {
			hang[5][1] = '|';
		}
		if (noOfLivesLeft <= 1) {
			hang[6][0] = '/';
		}
		if (noOfLivesLeft == 0) {
			hang[6][2] = '\\';
		};
	}

	size_t hangerPosX{ hangBorderPosX + ((hangBorderWidth - noOfColsInHang) / 2 ) + BORDER_PADDING};
	size_t hangerPosY{ hangBorderPosY + ((hangBorderHeight - noOfRowsInHang) / 2 ) + BORDER_PADDING / 2};
	
	for (size_t curRow{}; curRow < noOfRowsInHang; curRow++)
	{
		setCoursorToXY(hangerPosX, hangerPosY + curRow);

		if (!noOfLivesLeft) {
			SET_TEXT_RED();
		}
		std::cout << hang[curRow];
	}

	if (!noOfLivesLeft) {
		SET_TEXT_RED();
	}
}
void GameWindowDecorator::drawGameResultField(bool isGuessedRight) const {

	size_t borderPosX{ 10 };
	size_t borderPosY{ 19 };
	size_t borderWidth{ 25 };
	size_t borderHeight{ 8 };
	drawBorders(borderPosX, borderPosY, borderWidth, borderHeight);

	SET_TEXT_RED();
	size_t messageLen{ 10 };
	size_t resultPosX{ (borderWidth - messageLen) / 2 + borderPosX + BORDER_PADDING};
	size_t resultPosY{ borderHeight / 2 + borderPosY};
	setCoursorToXY(resultPosX, resultPosY);

	if (isGuessedRight) {
		std::cout << "YOU WIN!";
	}
	else {
		std::cout << "YOU LOSE!";
	};
	SET_TEXT_BLUE();
}
void GameWindowDecorator::drawGuessResult(const bool isGuessGood) const {
	size_t messagePosX{ 12 };
	size_t messagePosY{ 14 };

	setCoursorToXY(messagePosX, messagePosY);

	if (isGuessGood) {
		std::cout << "                                ";
		setCoursorToXY(messagePosX, messagePosY);
		std::cout << "Good!";
	}
	else {
		SET_TEXT_RED();
		std::cout << "One step closer to death        ";
		SET_TEXT_BLUE();
	}
};
void GameWindowDecorator::drawInvalidInput() const {
	size_t messagePosX{ 12 };
	size_t messagePosY{ 14 };

	setCoursorToXY(messagePosX, messagePosY);

	std::cout << "                                ";
	SET_TEXT_RED();
	setCoursorToXY(messagePosX, messagePosY);
	std::cout << "Invalid input, please try again!";
	SET_TEXT_BLUE();

}
void GameWindowDecorator::drawUserGuessInputField() const {
	size_t guessPosX{ 12 };
	size_t guessPosY{ 11 };

	setCoursorToXY(guessPosX, guessPosY);
};

void StatisticsDecorator::drawStats() const {
	Player& curPlayer{ Player::getInstance() };
	SET_TEXT_BLUE();

	std::string nameField{ "Players name : " };
	std::string guessWordField{ "Word: " };
	std::string clueField{ "Clue: " };
	std::string noOfWinsField{ "Total number of wins: " };
	std::string noOfLossesField{ "Total number of losses: " };
	std::string scoreField{ "Total score: " };
	std::string lastGameResult{ "Last game result: " };
	std::string resultField{ "Result: " };
	std::string noOfTriesField{ "Total number of tries: " };
	std::string wrongLettersField{ "Wrong guesses: " };
	std::string timeTakesField{ "Time taken to guess: " };

	size_t clueFieldLen{ clueField.length() };
	size_t clueLen{ curPlayer.statistics().clue().length() };
	size_t noOfFields{ 11 };

	size_t statsWidth{ clueFieldLen + clueLen };
	size_t padding{ 2 };

	size_t statsPosX{ (innerField.noOfCols - statsWidth) / 2 };
	size_t statsPosY{ (innerField.noOfRows - noOfFields * 2) / 2 + BORDER_PADDING / 2};

	drawStatsField(nameField, curPlayer.name(), statsPosX, statsPosY);

	drawStatsField(noOfWinsField, std::to_string(curPlayer.statistics().noOfWins()), statsPosX, statsPosY += 2);

	drawStatsField(noOfLossesField, std::to_string(curPlayer.statistics().noOfLosses()), statsPosX, statsPosY += 2);

	drawStatsField(scoreField, std::to_string(curPlayer.statistics().score()), statsPosX, statsPosY += 2);

	drawStatsField(lastGameResult, "", statsPosX, statsPosY += 2);

	drawStatsField(guessWordField, curPlayer.statistics().guessWord(), statsPosX, statsPosY += 2);

	drawStatsField(clueField, curPlayer.statistics().clue(), statsPosX, statsPosY += 2);

	drawStatsField(resultField, (curPlayer.statistics().isWon() ? "Won" : "Lost"), statsPosX, statsPosY += 2);

	drawStatsField(noOfTriesField, std::to_string(curPlayer.statistics().noOfTries()), statsPosX, statsPosY += 2);

	drawStatsField(wrongLettersField, curPlayer.statistics().wrongLetters(), statsPosX, statsPosY += 2);

	drawStatsField(timeTakesField, curPlayer.statistics().timeElapsed(), statsPosX, statsPosY += 2);

}

void StatisticsDecorator::drawStatsField(const std::string& fieldName, const std::string& message, const size_t fieldPosX, const size_t fieldPosY) const {
	setCoursorToXY(fieldPosX, fieldPosY);
	std::cout << fieldName << message;
}