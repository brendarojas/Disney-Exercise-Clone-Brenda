#include "item.h"

Item::Item(std::string name, std::string imgFilename) : _name(name), _imgFilename(imgFilename) {
    setTexture();
    std::cout << '\t' << _name << std::endl;
}

Item::~Item() {
    // _name = "";
    // _imgFilename = "";
}

void Item::setImgFilename(std::string newFilename) { _imgFilename = newFilename; }

void Item::setName(std::string newText) { _name = newText; }

/**
 * @brief set the texture of the item based on its corresponding image
 *
 */
void Item::setTexture() {
    if (!_texture.loadImageFromFile(_imgFilename)) {
        std::cerr << "WARNING! Texture failed to load." << std::endl;
    }
}

std::string Item::getImgFilename() { return _imgFilename; }

std::string Item::getName() { return _name; }

bool Item::textureIsSet() {
    if (_texture.getPtr() == NULL) {
        std::cerr << "WARNING! Texture is not set." << std::endl;
        return false;
    }
    return true;
}

SDL_Texture* Item::getTexPtr() { return _texture.getPtr(); }

LTexture Item::getTexture() { return _texture; }

bool fileExists(std::string filename) {
    struct stat buffer;
    return (stat((RESOURCES_DIR + filename).c_str(), &buffer) == 0);
}