#include "stdafx.h"
#include "Field.h"

#include <vector>

Field::Field() {
	gameBlocksCount = mainBlocksCount * fieldSize;
	texture.loadFromFile(imageUrl);
	sprite = sf::Sprite(texture);
	sf::Vector2u textureSize = texture.getSize();

	for (int i = 0; i < mainBlocksCount; i++) {
		mainBlocksCoordinates.push_back(sf::Vector2u(coordinates.x + ((texture.getSize().x / fieldSize) * (2 * i)) + 2,
			coordinates.y + 2));
	}

	for (int i = 0; i < fieldSize; i++) {
		fieldBlocksCoordinates.push_back(std::vector<sf::Vector2u>());
		for (int j = 0; j < fieldSize; j++) {
			fieldBlocksCoordinates[i].push_back(sf::Vector2u(coordinates.x + (texture.getSize().x / fieldSize * i) + 4,
				coordinates.y + ((texture.getSize().y / (fieldSize + 1)) * (j + 1)) + 4));
		}
	}

	for (int i = 0; i < blockedBlocksCount; i++) {
		blockedBlocksPositions.push_back(sf::Vector2u((i < 3) ? 1 : 3, (i < 3) ? (i * 2) : ((i - 3) * 2)));
	}

	for (int i = 0; i < fieldSize; i += 2) {
		for (int j = 0; j < fieldSize; j++) {
			startGameBlocksPositions.push_back(sf::Vector2u(i, j));
		}
	}
}

void Field::setTexture(sf::Texture texture) {
	texture = texture;
	sprite = sf::Sprite(texture);
	sprite.setPosition(sf::Vector2f(coordinates));
}

void Field::move(sf::Vector2u vector) {
	coordinates += vector;
	sprite.setPosition(sf::Vector2f(vector.x, vector.y));
	for (int i = 0; i < mainBlocksCount; i++) {
		mainBlocksCoordinates[i] += vector;
	}
	for (int i = 0; i < fieldSize; i++) {
		for (int j = 0; j < fieldSize; j++) {
			fieldBlocksCoordinates[i][j] += vector;
		}
	}
}

sf::Texture Field::getTexture() {
	return texture;
}

void Field::setScale(float scale) {
	this->scale = scale;
	sprite.setScale(scale, scale);
	for (int i = 0; i < mainBlocksCount; i++) {
		mainBlocksCoordinates[i] = sf::Vector2u(mainBlocksCoordinates[i].x * scale,
			mainBlocksCoordinates[i].y * scale);
	}
	for (int i = 0; i < fieldSize; i++) {
		for (int j = 0; j < fieldSize; j++) {
			fieldBlocksCoordinates[i][j] = sf::Vector2u(fieldBlocksCoordinates[i][j].x * scale,
				fieldBlocksCoordinates[i][j].y * scale);
		}
	}
}

float Field::getScale() {
	return scale;
}

sf::Vector2f Field::getSize() {
	return sf::Vector2f(texture.getSize());
}

std::vector<sf::Vector2u> Field::getMainBlocksCoordinates() {
	return mainBlocksCoordinates;
}

std::vector<std::vector<sf::Vector2u>> Field::getFieldBlocksCoordinates() {
	return fieldBlocksCoordinates;
}

std::vector<sf::Vector2u> Field::getBlockedBlocksPositions() {
	return blockedBlocksPositions;
}

std::vector<sf::Vector2u> Field::getStartGameBlocksPositions() {
	return startGameBlocksPositions;
}

int Field::getVerticalFieldSize() {
	return (fieldSize + 1);
}

int Field::getHorizontalFieldSize() {
	return fieldSize;
}

int Field::getMainBlocksCount() {
	return mainBlocksCount;
}

int Field::getBlockedBlocksCount() {
	return blockedBlocksCount;
}

sf::Vector2i Field::getFieldPosition(sf::Vector2i cursorPosition) {
	sf::Vector2i result(-1, -1);
	if ((cursorPosition.x > coordinates.x) &&
		(cursorPosition.x < (coordinates.x + (texture.getSize().x * scale))) &&
		(cursorPosition.y > fieldBlocksCoordinates[0][0].y)) {
		cursorPosition.x -= coordinates.x;
		result.x = cursorPosition.x / (fieldBlocksCoordinates[1][0].x - fieldBlocksCoordinates[0][0].x);
		cursorPosition.y -= fieldBlocksCoordinates[0][0].y;
		result.y = cursorPosition.y / (fieldBlocksCoordinates[0][1].y - fieldBlocksCoordinates[0][0].y);
	}
	return result;
}

sf::Sprite Field::getSprite() {
	return sprite;
}

Field::~Field() {

}
