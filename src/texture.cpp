#include "texture.h"

LTexture::LTexture() {
    // Initialize
    _texture = NULL;
    _width = 0;
    _height = 0;
}

LTexture::~LTexture() {
    // std::cout << "Destroying Texture" << std::flush;
    // Deallocate
    // freeTexture();
}

bool LTexture::loadImageFromFile(std::string filename) {
    SDL_RWops* rwop = SDL_RWFromFile((RESOURCES_DIR + filename).c_str(), "rb");
    SDL_Surface* loadedImage = IMG_LoadJPG_RW(rwop);
    if (loadedImage == NULL) {
        std::cerr << "Image failed to load! Error: " << IMG_GetError() << std::endl;
        return false;
    }

    _texture = SDL_CreateTextureFromSurface(_renderer, loadedImage);
    if (_texture == NULL) {
        std::cerr << "Unable to create texture from " << filename << ". Error: " << SDL_GetError() << std::endl;
        return false;
    }
    _width = loadedImage->w / 2;
    _height = loadedImage->h / 2;
    SDL_FreeSurface(loadedImage);
    return true;
}

void LTexture::loadFromText(std::string text, SDL_Color textColor) {
    // Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Shaded(_font, text.c_str(), textColor, {0, 0, 0, 0});
    if (textSurface == NULL) {
        std::cerr << "WARNING: Unable to render text surface! SDL_ttf Error: " << SDL_GetError() << std::endl;
        return;
    }
    // Create texture from surface pixels
    _texture = SDL_CreateTextureFromSurface(_renderer, textSurface);
    if (_texture == NULL) {
        std::cerr << "WARNING: Unable to create texture from rendered text! Error: " << SDL_GetError() << std::endl;
        return;
    }
    // Get image dimensions
    _width = textSurface->w;
    _height = textSurface->h;

    // Get rid of old surface
    SDL_FreeSurface(textSurface);
}

void LTexture::freeTexture() {
    if (_texture) {
        // std::cout << " (" << _texture << ") really destroyed texture" << std::endl;
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
        _width = 0;
        _height = 0;
    } /* else {
        std::cout << " - didn't destroy texture" << std::endl;
    } */
}

void LTexture::render(SDL_Rect* renderQuad) {
    if (renderQuad == NULL) {
        return;
    }
    // adjust size of picture to clip provided
    std::cout << "render x: " << renderQuad->x << ", y: " << renderQuad->y << ", w: " << renderQuad->w
              << ", h: " << renderQuad->h << std::endl;

    // render the whole picture in the adjusted quad
    SDL_RenderCopy(_renderer, _texture, NULL, renderQuad);
}

void LTexture::renderAt(int x, int y, bool selected) {
    // generate a rectangle based on own texture size
    SDL_Rect renderQuad = {x, y, _width, _height};
    if (selected) {
        const int borderSize = 2;
        SDL_Rect borderQuad = {renderQuad.x - borderSize, renderQuad.y - borderSize, renderQuad.w + borderSize * 2,
                               renderQuad.h + borderSize * 2};

        // gray color
        SDL_SetRenderDrawColor(_renderer, 0xD3, 0xD3, 0xD3, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(_renderer, &borderQuad);
        SDL_RenderFillRect(_renderer, &borderQuad);
    }
    SDL_RenderCopy(_renderer, _texture, NULL, &renderQuad);
}

int LTexture::getWidth() { return _width; }

int LTexture::getHeight() { return _height; }

SDL_Texture* LTexture::getPtr() { return _texture; }
