#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "sdl.h"

// Texture wrapper class
class LTexture {
   public:
    // Initializes variables
    LTexture();

    // Deallocates memory
    ~LTexture();

    /**
     * @brief Load image from file that is inside RESOURCES_DIR.
     *
     * @param  filename the name of the file. it is asumed it is inside RESOURCES_DIR
     * @return true if file loaded correctly
     * @return false otherwise
     */
    bool loadImageFromFile(std::string filename);

    // Creates image from font string
    void loadFromText(std::string text, SDL_Color textColor);

    // Deallocates texture
    void freeTexture();

    // Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    // Set blending
    void setBlendMode(SDL_BlendMode blending);

    // Set alpha modulation
    void setAlpha(Uint8 alpha);

    // Renders texture at given point
    void render(SDL_Rect* renderQuad);

    void renderAt(int x, int y, bool selected);

    // Gets image dimensions
    int getWidth();
    int getHeight();
    SDL_Texture* getPtr();

   private:
    // The actual hardware texture
    SDL_Texture* _texture;

    // Image dimensions
    int _width;
    int _height;
};

#endif  // TEXTURE_H