#include "Text.h"

Text::Text(std::string text, std::string fontLocation, SDL_Renderer* renderer)
	: text(text), fontLocation(fontLocation), renderer(renderer)
{
	//Set font size and colour to default
	fontSize = 10;
	fontColour = { (Uint8)0, (Uint8)0, (Uint8)0 };
	
	//Initialise font
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	//Create the text texture
	createTextTexture();
}

Text::Text(std::string text, std::string fontLocation, int fontSize, SDL_Renderer* renderer)
	: text(text), fontLocation(fontLocation), fontSize(fontSize), renderer(renderer)
{
	//Set font colour to default
	fontColour = { (Uint8)0, (Uint8)0, (Uint8)0 };

	//Initialise font
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	//Create the text texture
	createTextTexture();
}

Text::Text(std::string text, std::string fontLocation, SDL_Renderer* renderer, int r, int g, int b)
	: text(text), fontLocation(fontLocation), renderer(renderer)
{
	//Set font size to default
	fontSize = 10;

	//Set font colour
	fontColour = { (Uint8)r, (Uint8)g, (Uint8)b };

	//Initialise font
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	//Create the text texture
	createTextTexture();
}

Text::Text(std::string text, std::string fontLocation, SDL_Renderer* renderer, SDL_Colour fontColour)
	: text(text), fontLocation(fontLocation), renderer(renderer), fontColour(fontColour)
{
	//Set font size to default
	fontSize = 10;

	//Initialise font
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	//Create the text texture
	createTextTexture();
}

Text::Text(std::string text, std::string fontLocation, int fontSize, SDL_Renderer* renderer, int r, int g, int b)
	: text(text), fontLocation(fontLocation), fontSize(fontSize), renderer(renderer)
{
	//Set font colour
	fontColour = { (Uint8)r, (Uint8)g, (Uint8)b };

	//Initialise font
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	//Create the text texture
	createTextTexture();
}

Text::Text(std::string text, std::string fontLocation, int fontSize, SDL_Renderer* renderer, SDL_Colour fontColour)
	: text(text), fontLocation(fontLocation), fontSize(fontSize), renderer(renderer), fontColour(fontColour)
{
	//Initialise font
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	//Create the text texture
	createTextTexture();
}

Text::~Text()
{
	//deletes the texture from memory
	SDL_DestroyTexture(textureData);
	//delete font
	TTF_CloseFont(font);
	font = NULL;
}

void Text::pushToScreen(glm::vec2 pos)
{
	//Create the destination rectangle of the texture
	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (int)dimensions.x;
	destRect.h = (int)dimensions.y;

	//Copy the texture to the renderer at the destination rectangle
	SDL_RenderCopy(renderer, textureData, NULL, &destRect);
}

void Text::setColour(int r, int g, int b)
{
	//deletes the texture from memory
	SDL_DestroyTexture(textureData);

	//Set the font colour
	fontColour = { (Uint8)r, (Uint8)g, (Uint8)b };

	//Recreate the text texture
	createTextTexture();
}

void Text::setColour(SDL_Colour inFontColour)
{
	//deletes the texture from memory
	SDL_DestroyTexture(textureData);

	//Set the font colour
	fontColour = inFontColour;

	//Recreate the text texture
	createTextTexture();
}

void Text::setFontSize(int inFontSize)
{
	//deletes the texture from memory
	SDL_DestroyTexture(textureData);
	//delete font
	TTF_CloseFont(font);
	font = NULL;

	//Set the font size
	fontSize = inFontSize;

	//Set the font
	font = TTF_OpenFont(fontLocation.c_str(), inFontSize);

	//Recreate the text texture
	createTextTexture();
}

void Text::setFont(std::string inFontLocation)
{
	//deletes the texture from memory
	SDL_DestroyTexture(textureData);
	//delete font
	TTF_CloseFont(font);
	font = NULL;

	//Set the font
	font = TTF_OpenFont(inFontLocation.c_str(), fontSize);

	//Recreate the text texture
	createTextTexture();
}

void Text::setText(std::string inText)
{
	//deletes the texture from memory
	SDL_DestroyTexture(textureData);

	//Set the text
	text = inText;

	//Recreate the text texture
	createTextTexture();
}

glm::vec2 Text::getDimensions()
{
	return dimensions;
}

void Text::createTextTexture()
{
	//Declare the surface
	SDL_Surface *surface;

	//Create the surface from the font
	surface = TTF_RenderText_Solid(font, text.c_str(), fontColour);

	//Converts the surface into texture data
	textureData = SDL_CreateTextureFromSurface(renderer, surface);

	//Delete the surface from memory
	SDL_FreeSurface(surface);

	//Get the size of the texture
	int textureWidth;
	int textureHeight;
	SDL_QueryTexture(textureData, NULL, NULL, &textureWidth, &textureHeight);

	//Store the dimensions of the texture
	dimensions = glm::vec2(textureWidth, textureHeight);
}