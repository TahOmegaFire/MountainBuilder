#ifndef TTFTW_H
#define TTFTW_H

#include <SDL2/SDL_ttf.h>
#include "TexW.h"

class TextTexture : public TexW
{
public:
	TextTexture();
	~TextTexture();
	
	bool LoadTTF(const char* path, int size);
	bool LoadTextTexture(std::string text, SDL_Color color);
    bool FreeTexture();

    //Rendering functions
    void Render(int x, int y);
    void Render(int sx, int sy, int dx, int dy, int w, int h, double angle, int alpha, bool flip_horizontaly);

    int m_Width, m_Height;

	TTF_Font* m_Font;
private:
	
    SDL_Texture* m_Texture;
};

#endif //TTFTW_H
