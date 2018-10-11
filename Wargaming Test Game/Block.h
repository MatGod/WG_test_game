#pragma once

#include "SFML\Graphics.hpp"

enum Colour { RED, YELLOW, GREEN, BLOCKED, EMPTY };
enum FixMode { UNFIXED, FIXED };

class Block {
private:
	FixMode fixed = FIXED;
	sf::Texture *texture;
	sf::Texture *selectedTexture = NULL;
	sf::Sprite sprite;
	sf::Vector2u coordinates;
	Colour colour;
	float scale = 1.f;
public:
	Block();
	Block(Colour colour, sf::Texture *texture, sf::Texture *selectedTexture);
	Block(Colour color, sf::Texture *texture);
	void setTexture(sf::Texture texture);
	sf::Texture getTexture();
	sf::Sprite getSprite();
	void setScale(float scale);
	float getScale();
	sf::Vector2u getSize();
	void setPosition(sf::Vector2u vector);
	Colour getColour();
	FixMode getFixMode();
	void select();
	void unselect();
	void move(sf::Vector2f vector);
	~Block();
};

