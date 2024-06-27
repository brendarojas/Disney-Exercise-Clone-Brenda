// sdl.h
#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "definitions.h"
#include "texture.h"

#define UNUSED(x) (void)(x)

// Key press surfaces constants
enum KeyPressSurfaces {
    KEY_PRESS_DEFAULT,
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT,
    KEY_PRESS_TOTAL
};

extern SDL_Renderer* _renderer;
extern SDL_Window* _window;
extern TTF_Font* _font;
volatile extern bool _keepRunning;

int initSDL();

SDL_Rect createCenteredRect(int w, int h);

int createMainWindow();

void loadSplashImg(std::string imgFilename);

void clearScreen();

bool loadSDLFont();

// event loop for handling input
void handleEvents();

void interruptHandler(int t);

// Frees media and shuts down SDL
void closeSDL();

#endif