#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <glm/glm.hpp>

/**
@brief Creates a Text Texture for use with a renderer using the Text formating.
*/
class Text
{
public:
	/**
	@brief Constructs the Text Texture. Font size and colour will be default (size 10 and black).
	@param text The text to display.
	@param fontLocation The location of the font file.
	@param renderer The renderer.
	*/
	Text(std::string text, std::string fontLocation, SDL_Renderer* renderer);

	/**
	@brief Constructs the Text Texture. Font colour will be default (black).
	@param text The text to display.
	@param fontLocation The location of the font file.
	@param fontSize The size of the font.
	@param renderer The renderer.
	*/
	Text(std::string text, std::string fontLocation, int fontSize, SDL_Renderer* renderer);

	/**
	@brief Constructs the Text Texture. Font size will be default (size 10).
	@param text The text to display.
	@param fontLocation The location of the font file.
	@param renderer The renderer.
	@param r The value of red. (0-255)
	@param g The value of green. (0-255)
	@param b The value of blue. (0-255)
	*/
	Text(std::string text, std::string fontLocation, SDL_Renderer* renderer, int r, int g, int b);

	/**
	@brief Constructs the Text Texture. Font size will be default (size 10).
	@param text The text to display.
	@param fontLocation The location of the font file.
	@param renderer The renderer.
	@param fontColour The colour of the font.
	*/
	Text(std::string text, std::string fontLocation, SDL_Renderer* renderer, SDL_Colour fontColour);

	/**
	@brief Constructs the Text Texture.
	@param text The text to display.
	@param fontLocation The location of the font file.
	@param fontSize The size of the font.
	@param renderer The renderer.
	@param r The value of red. (0-255)
	@param g The value of green. (0-255)
	@param b The value of blue. (0-255)
	*/
	Text(std::string text, std::string fontLocation, int fontSize, SDL_Renderer* renderer, int r, int g, int b);

	/**
	@brief Constructs the Text Texture.
	@param text The text to display.
	@param fontLocation The location of the font file.
	@param fontSize The size of the font.
	@param renderer The renderer.
	@param fontColour The colour of the font.
	*/
	Text(std::string text, std::string fontLocation, int fontSize, SDL_Renderer* renderer, SDL_Colour fontColour);

	/**
	@brief Destructs the Text Texture.
	*/
	~Text();

	/**
	@brief Pushes the Text Texture to the Renderer to the XY Coordinates.
	@param pos The position to push the Text Texture to.
	*/
	void pushToScreen(glm::vec2 pos);

	/**
	@brief Sets the colour of the text.
	@param r The value of red. (0-255)
	@param g The value of green. (0-255)
	@param b The value of blue. (0-255)
	*/
	void setColour(int r, int g, int b);

	/**
	@brief Sets the colour of the text.
	@param colour The colour of the font.
	*/
	void setColour(SDL_Colour inFontColour);

	/**
	@brief Sets the font size of the text.
	@param fontSize The font size of the text.
	*/
	void setFontSize(int inFontSize);

	/**
	@brief Sets the font of the text.
	@param fontLocation The location of the font file.
	*/
	void setFont(std::string inFontLocation);

	/**
	@brief Sets the text.
	@param text The text to display.
	*/
	void setText(std::string text);

	/**
	@brief Gets the dimensions of the Text Texture.
	@returns The dimensions of the Text Texture.
	*/
	glm::vec2 getDimensions();

private:
	///Font
	TTF_Font* font;
	///Font colour
	SDL_Colour fontColour;
	///The Texture data
	SDL_Texture* textureData;
	///A pointer to the render
	SDL_Renderer* renderer;
	///Font size
	int fontSize;
	///The text and font location
	std::string text, fontLocation;
	///The Texture dimensions
	glm::vec2 dimensions;

	/**
	@brief Creates a Text Texture using the Text data.
	*/
	void createTextTexture();
};