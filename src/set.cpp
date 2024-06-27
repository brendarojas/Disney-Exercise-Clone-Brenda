#include "set.h"

Set::Set(std::string name) : _initialized(false), _name(name) {
    generateNameTexture();
    std::cout << _name << std::endl;
}

Set::~Set() {
    _name = "";
    _items.clear();
    //_nameTexture.freeTexture();
    _initialized = false;
}

bool Set::initialized() { return _initialized; }

size_t Set::fetchItems(const rapidjson::Value& set) {
    // iterate over all the "item" objects
    for (rapidjson::SizeType currItemsIdx = 0; currItemsIdx < set["items"].Size(); currItemsIdx++) {
        const rapidjson::Value& itemObj = set["items"][currItemsIdx];
        // initialize some strings to be used later
        std::string memberType = itemObj["image"]["tile"]["1.78"].MemberBegin()->name.GetString();
        std::string imgFilename =
            std::string(itemObj["image"]["tile"]["1.78"][memberType.c_str()]["default"]["masterId"].GetString()) +
            ".jpg";
        std::string mediaType = itemObj["text"]["title"]["full"].MemberBegin()->name.GetString();
        std::string contentName = itemObj["text"]["title"]["full"][mediaType.c_str()]["default"]["content"].GetString();
        if (imgFilename.empty()) {
            std::cerr << "ERROR! Filename is empty! Skipping program" << std::endl;
            continue;
        }

        if (!fileExists(imgFilename)) {
            // get the image from URL and save it in RESOURCES_DIR
            std::fstream imgFile(RESOURCES_DIR + imgFilename, std::ios_base::out | std::ios_base::ate);
            sDATA imgData{&imgFile, NULL};  // we only get the data in file format, not string

            // media type can be series, program, etc. So find what it is
            std::string url =
                std::string(itemObj["image"]["tile"]["1.78"][memberType.c_str()]["default"]["url"].GetString());
            if (!fetchDataFromURL(url, &imgData)) {
                std::cout << "WARNING! Couldn't fetch image data from url. Skipping program" << std::endl;
                continue;
            }
        } else {
            // Image file already exists on disk.
            std::cout << "*" << std::flush;  // add a star to note the reused image
        }

        // Instantiate the object
        Item program(contentName, imgFilename);

        // if the texture is properly loaded, we push the program into de set vector
        // otherwise the current program is skipped
        if (program.textureIsSet()) {
            _items.emplace_back(program);
        }
    }
    // we return the current size of the vector
    return _items.size();
}

void Set::generateNameTexture() {
    // blank construction of generic texture
    _nameTexture.loadFromText(_name, {0xFF, 0xFF, 0xFF, 0xFF});
}

void Set::setName(std::string name) { _name = name; }

std::string Set::getName() { return _name; }

const std::vector<Item>& Set::getItems() { return _items; }

LTexture Set::getTexture() { return _nameTexture; }