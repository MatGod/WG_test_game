#include "stdafx.h"
#include "Block.h"

Block::Block() {
	colour = EMPTY;
}

Block::Block(Colour colour, sf::Texture *texture) {
	this->colour = colour;
	this->texture = texture;
	sprite.setTexture(*texture);
}

Block::Block(Colour colour, sf::Texture *texture, sf::Texture *selectedTexture) {
	this->selectedTexture = selectedTexture;
	this->colour = colour;
	this->texture = texture;
	sprite.setTexture(*texture);
	fixed = UNFIXED;
}

void Block::setTexture(sf::Texture texture) {
	this->texture = &texture;
	sprite.setTexture(texture);
}

sf::Texture Block::getTexture() {
	return *texture;
}

sf::Sprite Block::getSprite() {
	return sprite;
}

void Block::setScale(float scale) {
	this->scale = scale;
	sprite.setScale(scale, scale);
}

float Block::getScale() {
	return scale;
}

sf::Vector2u Block::getSize() {
	return texture->getSize();
}

void Block::setPosition(sf::Vector2u vector) {
	coordinates = vector;
	sprite.setPosition(sf::Vector2f(coordinates.x, coordinates.y));
}

Colour Block::getColour() {
	return colour;
}

FixMode Block::getFixMode() {
	return fixed;
}

void Block::select() {
	sprite.setTexture(*selectedTexture);
	sprite.setScale(scale, scale);
}

void Block::unselect() {
	sprite.setTexture(*texture);
	sprite.setScale(scale, scale);
}

void Block::move(sf::Vector2f vector) {
	coordinates += sf::Vector2u(vector.x, vector.y);
	sprite.setPosition(sf::Vector2f(coordinates.x, coordinates.y));
}

Block::~Block() {

}
