#pragma once
#include "SFML\Graphics.hpp"

#include <vector>

enum mainPositions { LEFT, CENTER, RIGHT };

class Field {
private:
	const char *imageUrl = (char*)"res/pole_fon.jpg";
	sf::Texture texture;
	sf::Sprite sprite;
	float scale = 1.f;
	sf::Vector2u coordinates = sf::Vector2u(0, 0);
	const int fieldSize = 5;
	const int mainBlocksCount = 3;
	const int blockedBlocksCount = 6;
	int gameBlocksCount;
	std::vector<sf::Vector2u> mainBlocksCoordinates;
	std::vector<std::vector<sf::Vector2u>> fieldBlocksCoordinates;
	std::vector<sf::Vector2u> blockedBlocksPositions;
	std::vector<sf::Vector2u> startGameBlocksPositions;
public:
	Field();
	void setTexture(sf::Texture texture);
	void move(sf::Vector2u vector);
	sf::Texture getTexture();
	sf::Sprite getSprite();
	void setScale(float scale);
	float getScale();
	sf::Vector2f getSize();
	std::vector<sf::Vector2u> getMainBlocksCoordinates();
	std::vector<std::vector<sf::Vector2u>> getFieldBlocksCoordinates();
	std::vector<sf::Vector2u> getBlockedBlocksPositions();
	std::vector<sf::Vector2u> getStartGameBlocksPositions();
	int getVerticalFieldSize();
	int getHorizontalFieldSize();
	int getMainBlocksCount();
	int getBlockedBlocksCount();
	sf::Vector2i getFieldPosition(sf::Vector2i cursorPosition);
	~Field();
};

