#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <glm/glm.hpp>
#include "Utilities.h"

/**
@brief Creates a Texture for use with a renderer.
*/
class Texture
{
public:
	/**
	@brief Constructs the Texture using an RGB value. This will create a 1x1 rectangle of that colour that can be scaled.
	@param renderer A pointer to the renderer.
	@param r The red value.
	@param g The green value.
	@param b The blue value.
	*/
	Texture(SDL_Renderer* renderer, int r, int g, int b);

	/**
	@brief Constructs the Texture using an RGB value. This will create a 1x1 rectangle of that colour that can be scaled.
	@param renderer A pointer to the renderer.
	@param colour The colour value.
	*/
	Texture(SDL_Renderer* renderer, SDL_Colour colour);

	/**
	@brief Constructs the Texture using an image location and a renderer. This is for use with SDL image.
	@param fileLocation The location of the image file.
	@param renderer A pointer to the renderer.
	*/
	Texture(std::string fileLocation, SDL_Renderer* renderer);

	/**
	@brief Constructs the Texture using an image location and a renderer. The magenta pixels of this image can represent alpha if needed.
	@param fileLocation The location of the image file.
	@param renderer A pointer to the renderer.
	@param magentaAlpha If true any magenta pixels in the image will be converted to alpha.
	*/
	Texture(std::string fileLocation, SDL_Renderer* renderer, bool magentaAlpha);

	/**
	@brief Destructs Texture.
	*/
	~Texture();

	/**
	@brief Gets a pointer to the Texture.
	@returns A pointer to the Texture.
	*/
	SDL_Texture* getTexture();

	/**
	@brief Gets the Texture dimensions.
	@returns The Texture dimensions.
	*/
	glm::vec2 getDimensions();

	/**
	@brief Pushes the image to the Renderer at the XY Coordinates.
	@param renderer A pointer to the renderer.
	@param pos The position of the image.
	*/
	void pushToScreen(SDL_Renderer* renderer, glm::vec2 pos);

	/**
	@brief Pushes the image to the Renderer at the XY Coordinates. 
	This is scaled to the dimensions inputed.
	@param renderer A pointer to the renderer.
	@param pos The position of the image.
	@param scale The dimensions of the image.
	*/
	void pushToScreen(SDL_Renderer* renderer, glm::vec2 pos, glm::vec2 scale);

	/**
	@brief Pushes the image to the Renderer at the XY Coordinates. 
	Only displays the source rectangle inputed.
	@param renderer A pointer to the renderer.
	@param pos The position of the image.
	@param spritePos The position of the sprite in the spritesheet.
	@param spriteDimensions The dimensions of the sprite.
	*/
	void pushSpriteToScreen(SDL_Renderer* renderer, glm::vec2 pos, glm::vec2 spritePos, glm::vec2 spriteDimensions);

	/**
	@brief Pushes the image to the Renderer, to the XY Coordinates. 
	Only displays the source rectangle inputed.
	This is scaled to the width and height inputed.
	@param renderer A pointer to the renderer.
	@param pos The position of the image.
	@param scale The dimensions of the image.
	@param spritePos The position of the sprite in the spritesheet.
	@param spriteDimensions The dimensions of the sprite.
	*/
	void pushSpriteToScreen(SDL_Renderer* renderer, glm::vec2 pos, glm::vec2 scale, glm::vec2 spritePos, glm::vec2 spriteDimensions);

	/**
	@brief Tints the texture with the inputed colour.
	@param r The red value.
	@param g The green value.
	@param b The blue value.
	*/
	void setColourTint(int r, int g, int b);

	/**
	@brief Tints the texture with the inputed colour.
	@param colour The colour.
	*/
	void setColourTint(SDL_Colour colour);

private:
	///The Texture data
	SDL_Texture* textureData;
	///The Texture dimensions.
	glm::vec2 dimensions;
};