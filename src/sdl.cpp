#include <signal.h>
#include <chrono>  //sleep
#include <thread>  //sleep
#include <vector>

#include "definitions.h"
#include "menu.h"
#include "sdl.h"

// The window renderer
SDL_Renderer* _renderer = NULL;
SDL_Window* _window = NULL;
TTF_Font* _font = NULL;
volatile bool _keepRunning = true;

SDL_Rect createCenteredRect(int w, int h) {
    return {(w < SCREEN_WIDTH) ? (SCREEN_WIDTH - w) : 0, (h < SCREEN_HEIGHT) ? (SCREEN_HEIGHT - h) : 0, w, h};
}

int createMainWindow() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "ERROR! Could not initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    // Create window
    _window = SDL_CreateWindow("DSS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN);
    if (_window == NULL) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    return 0;
}

int initSDL() {
    // First call the window creation function
    if (createMainWindow() != 0) {
        std::cerr << "SDL Initialization failed" << std::endl;
        return -1;
    }

    // create the renderer
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL) {
        std::cout << "Renderer could not be created. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // configure background color to black
    // SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  // black background

    SDL_Surface* screenSurface = SDL_GetWindowSurface(_window);  // create surface
    if (screenSurface == NULL) {
        std::cerr << "Screen surface initialization failed" << std::endl;
        return -1;
    }

    if (IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG) {
        std::cerr << "Could not initialize JPG library loader" << std::endl;
        return -1;
    }
    return 0;  // success
}

void closeSDL() {
    if (_font) {
        TTF_CloseFont(_font);
        _font = NULL;
    }
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _window = NULL;
    _renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    std::cout << "successfully closed SDL" << std::endl;
}

bool loadSDLFont() {
    if (TTF_Init() != 0) {
        std::cout << "ERROR! Failed to initialize TTF Library. Error: " << SDL_GetError() << std::endl;
        return false;
    }
    _font = TTF_OpenFont(FONT_FILE, 24);
    if (_font == NULL) {
        std::cout << "ERROR! Failed to load font. SDL_TTF Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void loadSplashImg(std::string imgFilename) {
    LTexture splashLogo = LTexture();

    std::cout << "Loading Image: " << imgFilename << std::endl;

    if (!splashLogo.loadImageFromFile(imgFilename)) {
        std::cerr << "Failed to load texture image!" << std::endl;
    }

    // create a rectangle based on half of the image dimensions
    SDL_Rect splashRect = createCenteredRect(splashLogo.getWidth() / 2, splashLogo.getHeight() / 2);

    // Clear screen
    SDL_RenderClear(_renderer);

    // Render texture to screen
    splashLogo.render(&splashRect);

    // Update Screen to show the picture
    SDL_RenderPresent(_renderer);
}

void clearScreen() {
    // put black background
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  // black background
    // Clear screen
    SDL_RenderClear(_renderer);
    // Update Screen to show the picture
    // SDL_RenderPresent(_renderer);
}

// maybe this won't be needed... check later
SDL_Surface* loadImage(std::string imgFile, SDL_Surface* refSurface) {
    SDL_RWops* rwop = SDL_RWFromFile(imgFile.c_str(), "rb");
    SDL_Surface* loadedImage = IMG_LoadJPG_RW(rwop);
    if (loadedImage == nullptr) {
        std::cerr << "Image failed to load! Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Surface* optimizedImage = SDL_ConvertSurface(loadedImage, refSurface->format, 0);
    if (optimizedImage == nullptr) {
        std::cerr << "Unable to optimize Image " << imgFile << " - Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_FreeSurface(loadedImage);
    return optimizedImage;
}

void handleEvents() {
    SDL_Event e;
    // wait for user input
    SDL_WaitEvent(&e);
    if (e.type == SDL_QUIT) {
        std::cout << "User closed window. Exiting program" << std::endl;
        _keepRunning = false;
    } else if (e.type == SDL_KEYDOWN) {
        // Select surfaces based on key press
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                std::cout << "KEY_PRESS_UP" << std::endl;
                selectPrevSet();
                break;

            case SDLK_DOWN:
                std::cout << "KEY_PRESS_DOWN" << std::endl;
                selectNextSet();
                break;

            case SDLK_LEFT:
                std::cout << "KEY_PRESS_LEFT" << std::endl;
                selectPrevItem();
                break;

            case SDLK_RIGHT:
                std::cout << "KEY_PRESS_RIGHT" << std::endl;
                selectNextItem();
                break;

            default:
                break;
        }
    }
}

void interruptHandler(int t) {
    UNUSED(t);  // supress unused parameter warning
    _keepRunning = false;
}
