#ifndef TEXW_H
#define TEXW_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class TexW
{
public:
    TexW();
    ~TexW();

    //TexW operator=(const TexW& other);

    //Texture loading/unloading functions
    bool LoadTexture(const char* path, bool has_chroma);
    bool FreeTexture();

    //Rendering functions
    void Render(int x, int y);
    void Render(int sx, int sy, int dx, int dy, int w, int h, double angle, int alpha, bool flip_horizontaly);

    int m_Width, m_Height;
    std::string imagePath;

private:
    SDL_Texture* m_Texture;
};


#endif // TEXW_H
