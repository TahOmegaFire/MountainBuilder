#include "Headers/TTFTextW.h"
#include <iostream>

extern SDL_Renderer* mainRenderer;

TextTexture::TextTexture()
{
	m_Texture = NULL;
	m_Font = NULL;
    m_Width = m_Height = 0;
}

TextTexture::~TextTexture()
{
	TTF_CloseFont(m_Font);
	m_Font = NULL;
	FreeTexture();
}

bool TextTexture::LoadTTF(const char* path, int size)
{
	m_Font = TTF_OpenFont(path, size);
	if(m_Font == NULL) 
		return false;
	return true; 
}

bool TextTexture::LoadTextTexture(std::string text, SDL_Color color)
{
	FreeTexture();
	SDL_Surface* nSurface = TTF_RenderText_Solid(m_Font, text.c_str(), color);
	if(nSurface == NULL)
	{
		std::cout << "\nCannot load text surface\n";
		return false;
	}
	
	m_Texture = SDL_CreateTextureFromSurface(mainRenderer, nSurface);
	
	if(m_Texture == NULL)
	{
		std::cout << "\nCannot load text texture\n";
		return false;
	}
	
	m_Width = nSurface->w;
	m_Height = nSurface->h;
	SDL_FreeSurface(nSurface);
	
	return true;
}


bool TextTexture::FreeTexture()
{
    if(m_Texture != NULL)
    {
        SDL_DestroyTexture(m_Texture);
        m_Texture = NULL;
        m_Width = 0;
        m_Height = 0;

        return true;
    }

    return false;
}

void TextTexture::Render(int x, int y)
{
    if(m_Texture != NULL)
    {
        SDL_Rect renderDest = { x, y, m_Width, m_Height };
        SDL_RenderCopy(mainRenderer, m_Texture, NULL, &renderDest);
    }
}