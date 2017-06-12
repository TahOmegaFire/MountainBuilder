#include "Headers/TexW.h"

extern SDL_Renderer* mainRenderer;

TexW::TexW()
{
    m_Texture = NULL;
    m_Width = m_Height = 0;
}

TexW::~TexW()
{
    FreeTexture();
}

bool TexW::LoadTexture(const char* path, bool has_chroma)
{
    FreeTexture();

    SDL_Surface* nSurface = IMG_Load(path);

    if(nSurface == NULL)
    {
        SDL_FreeSurface(nSurface);
        return false;
    }

    if(has_chroma)
        SDL_SetColorKey(nSurface, SDL_TRUE, SDL_MapRGB(nSurface->format, 0xFF, 0, 0xFF));

    m_Texture = SDL_CreateTextureFromSurface(mainRenderer, nSurface);

    if(m_Texture == NULL)
    {
        SDL_FreeSurface(nSurface);
        return false;
    }

    m_Height = nSurface->h;
    m_Width = nSurface->w;

    SDL_FreeSurface(nSurface);
    imagePath = path;

    return true;
}

bool TexW::FreeTexture()
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

void TexW::Render(int x, int y)
{
    if(m_Texture != NULL)
    {
        SDL_Rect renderDest = { x, y, m_Width, m_Height };
        SDL_RenderCopy(mainRenderer, m_Texture, NULL, &renderDest);
    }
}

void TexW::Render(int sx, int sy, int dx, int dy, int w, int h, double angle, int alpha, bool flip_horizontaly)
{
    SDL_Rect renderDest = {dx, dy, w, h};
    SDL_Rect renderSrc = {sx, sy, w, h};
    SDL_SetTextureAlphaMod(m_Texture, alpha);
    SDL_RendererFlip flip;
    flip_horizontaly ? flip = SDL_FLIP_HORIZONTAL : flip = SDL_FLIP_NONE;

    SDL_RenderCopyEx(mainRenderer, m_Texture, &renderSrc, &renderDest, angle, NULL, flip);
}
