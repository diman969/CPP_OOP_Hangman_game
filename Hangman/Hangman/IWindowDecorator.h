#pragma once
#include "IWindow.h"

#define BORDER_TOP_LEFT_CORNER static_cast <char>(201)
#define BORDER_TOP_RIGHT_CORNER static_cast <char>(187)
#define BORDER_HORIZONTAL static_cast <char>(205)
#define BORDER_BOTTOM_LEFT_CORNER static_cast <char>(200)
#define BORDER_BOTTOM_RIGHT_CORNER static_cast <char>(188)
#define BORDER_VERTICAL static_cast <char>(186)
#define BORDER_PADDING 2

#define TITLE_HEIGHT 7
#define AVERAGE_NAME_LENGTH 7
#define MAX_LIVES 7

class Window : public IWindow {
public:
	Window() = default;
	void draw() const override {
	};
};

class IWindowDecorator : public IWindow {
public:
	explicit IWindowDecorator(IWindow* const wrapee) :
		_wrappee{ wrapee }
	{};
	~IWindowDecorator() {
		if (_wrappee) {
			delete _wrappee;
		}
	}
protected:
	IWindow* const _wrappee;
	void drawBorders(const size_t xCoord, const size_t yCoord, const size_t width, const size_t height) const;
};

class BorderDecorator : public IWindowDecorator {
public:
	using IWindowDecorator::IWindowDecorator;
	void draw() const override {
		_wrappee->draw();
		drawMainBorder();
	}
	~BorderDecorator() = default;
protected:
	void drawMainBorder() const;
};

class TitleDecorator : public IWindowDecorator {
public:
	using IWindowDecorator::IWindowDecorator;
	void draw() const override {
		_wrappee->draw();
		drawTitle();
	}
protected:
	void drawTitle() const;
};

class MenuDecorator : public IWindowDecorator {
public:
	using IWindowDecorator::IWindowDecorator;
	void draw() const override {
		_wrappee->draw();
		drawMenu();
	}
protected:
	void drawMenu() const;
};

class InstructionsDecorator : public IWindowDecorator {
public:
	using IWindowDecorator::IWindowDecorator;
	void draw() const override {
		system("cls");
		_wrappee->draw();
		drawInstructions();
	}
protected:
	void drawInstructions() const;
};

class NameChangeDecorator : public IWindowDecorator {
public:
	using IWindowDecorator::IWindowDecorator;
	void draw() const override {
		system("cls");
		_wrappee->draw();
		drawNameChangeWindow();
	}
protected:
	void drawNameChangeWindow() const;
};

class GameWindowDecorator : public IWindowDecorator {
public:
	using IWindowDecorator::IWindowDecorator;
	void draw(const std::string& hiddenWord, const std::string& clue, const size_t noOfLives) const;
	void drawGameResultField(bool isGuessedRight) const;
	void drawGuessResult(const bool isGuessGood) const;
	void drawInvalidInput() const;
	void drawHangerField(const size_t noOfLivesLeft) const;
	void drawUserGuessInputField() const;
	void drawHiddenWordField(const std::string& hiddenWord) const;
	void drawLivesLeftField(const size_t noOfLivesLeft) const;
protected:
	void draw() const override {
		_wrappee->draw();
	}
	void drawClueField(const std::string& clue) const;

};

class StatisticsDecorator : public IWindowDecorator {
public:
	using IWindowDecorator::IWindowDecorator;
	void draw() const override {
		system("cls");
		_wrappee->draw();
		drawStats();
	}
protected:
	void drawStats() const;
	void drawStatsField(const std::string& fieldName, const std::string& message, const size_t fieldPosX, const size_t fieldPosY) const;
};
