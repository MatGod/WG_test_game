#include "stdafx.h"

#include <vector>
#include <algorithm>
//#include <random>

#include "SFML\Graphics.hpp"

#include "Field.h"
#include "Block.h"

int main()
{
	//Set VideoMode
	//sf::VideoMode videoMode = *sf::VideoMode::getFullscreenModes().begin();
	//sf::RenderWindow window(videoMode, "WARGAMING Test Game", sf::Style::Fullscreen);
	sf::RenderWindow window(sf::VideoMode(800, 600), "WARGAMING Test Game");
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	//Get size of window
	//int windowWidth = videoMode.width;
	//int windowHeight = videoMode.height;
	int windowWidth = 800;
	int windowHeight = 600;

	sf::Font font;
	if (!font.loadFromFile("res/Retron2000.ttf")) {
		printf("Error\n");
	}

	sf::Texture cursorTexture;
	cursorTexture.loadFromFile("res/cursor.png");
	sf::Sprite cursorSprite;
	cursorSprite.setTexture(cursorTexture);
	cursorSprite.setScale((float)50 / cursorTexture.getSize().x, (float)50 / cursorTexture.getSize().x);

	sf::Text winMessage;
	winMessage.setFont(font);
	winMessage.setCharacterSize(windowHeight / 16);
	winMessage.setPosition(170.f, 150.f);
	//winMessage.setFillColor(sf::Color::White);
	winMessage.setString("Congratulations!\nYou done it!\nPress \"ESC\" to exit from game.");

	//Set background
	Field field;

	//Rescale bkg
	float bkgScale = (float)windowHeight / field.getSize().y;
	field.setScale(bkgScale);

	//Move bkg to center
	field.move(sf::Vector2u((windowWidth / 2) - (field.getSize().x * bkgScale / 2), 0));

	//Init main blocks
	sf::Texture redBlockTexture;
	redBlockTexture.loadFromFile("res/red_block.png");
	sf::Texture yellowBlockTexture;
	yellowBlockTexture.loadFromFile("res/yellow_block.png");
	sf::Texture greenBlockTexture;
	greenBlockTexture.loadFromFile("res/green_block.png");

	std::vector<Block> mainBlocks = {
		Block(RED, &redBlockTexture),
		Block(YELLOW, &yellowBlockTexture),
		Block(GREEN, &greenBlockTexture)
	};
	float redBlockScale = (float)windowHeight / (mainBlocks[0].getSize().y * field.getVerticalFieldSize());
	mainBlocks[0].setScale(redBlockScale);

	float yellowBlockScale = (float)windowHeight / (mainBlocks[1].getSize().y * field.getVerticalFieldSize());
	mainBlocks[1].setScale(yellowBlockScale);

	float greenBlockScale = (float)windowHeight / (mainBlocks[2].getSize().y * field.getVerticalFieldSize());
	mainBlocks[2].setScale(greenBlockScale);

	std::random_shuffle(mainBlocks.begin(), mainBlocks.end());
	mainBlocks[0].setPosition(field.getMainBlocksCoordinates()[LEFT]);
	mainBlocks[1].setPosition(field.getMainBlocksCoordinates()[CENTER]);
	mainBlocks[2].setPosition(field.getMainBlocksCoordinates()[RIGHT]);

	//Init empty blocks
	Block emptyBlock;

	//Init blocked blocks
	sf::Texture blockedBlockTexture;
	blockedBlockTexture.loadFromFile("res/blocked_block.png");
	int blockedBlocksCount = field.getBlockedBlocksCount();
	std::vector<Block> blockedBlocks(blockedBlocksCount);
	for (int i = 0; i < blockedBlocksCount; i++) {
		blockedBlocks[i] = Block(BLOCKED, &blockedBlockTexture);
		blockedBlocks[i].setPosition(field.getFieldBlocksCoordinates()[field.getBlockedBlocksPositions()[i].x][field.getBlockedBlocksPositions()[i].y]);
		blockedBlocks[i].setScale((float)windowHeight / (blockedBlocks[i].getSize().y * field.getVerticalFieldSize()));
	}

	//Init selected blocks textures
	sf::Texture selectedRedBlockTexture;
	selectedRedBlockTexture.loadFromFile("res/selected_red_block.png");
	sf::Texture selectedYellowBlockTexture;
	selectedYellowBlockTexture.loadFromFile("res/selected_yellow_block.png");
	sf::Texture selectedGreenBlockTexture;
	selectedGreenBlockTexture.loadFromFile("res/selected_green_block.png");

	std::vector<Block> startGameBlocks = {
		Block(RED, &redBlockTexture, &selectedRedBlockTexture),
		Block(RED, &redBlockTexture, &selectedRedBlockTexture),
		Block(RED, &redBlockTexture, &selectedRedBlockTexture),
		Block(RED, &redBlockTexture, &selectedRedBlockTexture),
		Block(RED, &redBlockTexture, &selectedRedBlockTexture),
		Block(YELLOW, &yellowBlockTexture, &selectedYellowBlockTexture),
		Block(YELLOW, &yellowBlockTexture, &selectedYellowBlockTexture),
		Block(YELLOW, &yellowBlockTexture, &selectedYellowBlockTexture),
		Block(YELLOW, &yellowBlockTexture, &selectedYellowBlockTexture),
		Block(YELLOW, &yellowBlockTexture, &selectedYellowBlockTexture),
		Block(GREEN, &greenBlockTexture, &selectedGreenBlockTexture),
		Block(GREEN, &greenBlockTexture, &selectedGreenBlockTexture),
		Block(GREEN, &greenBlockTexture, &selectedGreenBlockTexture),
		Block(GREEN, &greenBlockTexture, &selectedGreenBlockTexture),
		Block(GREEN, &greenBlockTexture, &selectedGreenBlockTexture),
	};
	std::random_shuffle(startGameBlocks.begin(), startGameBlocks.end());

	for (int i = 0; i < startGameBlocks.size(); i++) {
		startGameBlocks[i].setScale(redBlockScale);
		startGameBlocks[i].setPosition(field.getFieldBlocksCoordinates()[field.getStartGameBlocksPositions()[i].x]
			[field.getStartGameBlocksPositions()[i].y]);
	}

	std::vector<std::vector<Block*>> gameField(field.getHorizontalFieldSize());
	for (int i = 0; i < gameField.size(); i++) {
		gameField[i] = std::vector<Block*>(gameField.size());
		if (i % 2 == 0) {
			for (int j = 0; j < gameField[i].size(); j++) {
				gameField[i][j] = &startGameBlocks[i / 2 * gameField[i].size() + j];
			}
		}
		else {
			for (int j = 0; j < gameField[i].size(); j++) {
				gameField[i][j] = &emptyBlock;
			}
		}
	}
	for (int i = 0; i < field.getBlockedBlocksCount(); i++) {
		gameField[field.getBlockedBlocksPositions()[i].x][field.getBlockedBlocksPositions()[i].y] =
			&blockedBlocks[i];
	}

	Block *selectedBlock = NULL;
	FixMode isFixed;
	sf::Vector2i selectedBlockPos;
	int i, j;
	bool isPlaying = true;

	window.draw(field.getSprite());
	for (int i = 0; i < mainBlocks.size(); i++) {
		window.draw(mainBlocks[i].getSprite());
	}
	for (int i = 0; i < blockedBlocksCount; i++) {
		window.draw(blockedBlocks[i].getSprite());
	}
	for (int i = 0; i < startGameBlocks.size(); i++) {
		window.draw(startGameBlocks[i].getSprite());
	}
	window.display();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			//Exit from game
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
				window.close();
			}
			if (isPlaying) {
				if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Left)) {
					sf::Vector2i pos = field.getFieldPosition(sf::Mouse::getPosition(window));

					if (pos.x >= 0 && pos.y >= 0) {
						isFixed = gameField[pos.x][pos.y]->getFixMode();
						if (isFixed == UNFIXED || gameField[pos.x][pos.y]->getColour() == EMPTY) {
							if (selectedBlock != NULL) {
								if (gameField[pos.x][pos.y]->getColour() == EMPTY &&
									(std::abs(pos.x - selectedBlockPos.x) + std::abs(pos.y - selectedBlockPos.y)) == 1) {

									selectedBlock->setPosition(field.getFieldBlocksCoordinates()[pos.x][pos.y]);
									std::swap(gameField[selectedBlockPos.x][selectedBlockPos.y], gameField[pos.x][pos.y]);

									for (i = 0; i < gameField.size(); i += 2) {
										for (j = 0; j < gameField[i].size(); j++) {
											if (gameField[i][j]->getColour() != mainBlocks[i / 2].getColour()) {
												break;
											}
										}

										if (j < gameField[i].size()) {
											break;
										}
									}

									if (i >= gameField.size()) {
										isPlaying = false;
									}

									selectedBlockPos = pos;
								}
								else {
									if (gameField[pos.x][pos.y]->getColour() != EMPTY && gameField[pos.x][pos.y]->getColour() != BLOCKED) {
										selectedBlock->unselect();
										selectedBlock = gameField[pos.x][pos.y];
										selectedBlock->select();
										selectedBlockPos = pos;
									}
								}
							}
							else {
								if (isFixed == UNFIXED) {
									selectedBlock = gameField[pos.x][pos.y];
									selectedBlock->select();
									selectedBlockPos = pos;
								}
								else {
									selectedBlock = NULL;
								}
							}
						}
					}
				}
			}

			window.clear();
			cursorSprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
			if (isPlaying) {
				window.draw(field.getSprite());
				for (i = 0; i < mainBlocks.size(); i++) {
					window.draw(mainBlocks[i].getSprite());
				}
				for (i = 0; i < blockedBlocksCount; i++) {
					window.draw(blockedBlocks[i].getSprite());
				}
				for (i = 0; i < startGameBlocks.size(); i++) {
					window.draw(startGameBlocks[i].getSprite());
				}
			}
			else {
				window.draw(winMessage);
			}
			window.draw(cursorSprite);
			window.display();
		}
	}
	return 0;
}