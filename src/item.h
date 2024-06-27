#ifndef ITEM_H
#define ITEM_H

#include <sys/stat.h>
#include <iostream>
#include <string>
#include <vector>
#include "definitions.h"
#include "texture.h"

class Item {
   public:
    Item(std::string name, std::string imgFilename);

    ~Item();

    void setImgFilename(std::string filename);
    void setName(std::string newName);
    void setTexture();

    std::string getName();
    std::string getImgFilename();
    SDL_Texture* getTexPtr();
    LTexture getTexture();
    bool textureIsSet();

   private:
    std::string _name;
    std::string _imgFilename;
    LTexture _texture;
};

/**
 * Check if a file exists
 * @param name name of the file or full path
 * @return true if it exists, false otherwise
 */
bool fileExists(std::string filename);

#endif  // ITEM_H