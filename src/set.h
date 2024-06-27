#ifndef SET_H
#define SET_H

#include <sys/stat.h>
#include <algorithm>  //std::replace
#include <iostream>
#include <string>
#include <vector>
#include "curlhandler.h"
#include "definitions.h"
#include "item.h"
#include "jsonparser.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "texture.h"

#include "sdl.h"

class Set {
   public:
    Set(std::string name);

    ~Set();

    /**
     * @brief Check set initialization status
     *
     * @return true when the set is correctly initialized
     * @return false when it isn't
     */
    bool initialized();
    /**
     * @brief obtain the "item" objects from a "set", "curatedSet", "personalizedCuratedSet", etc.
     * And push the items in the set vector.
     * @param set the parent JSON object that contains the items
     * @return size of the populated vector
     */
    size_t fetchItems(const rapidjson::Value& set);

    /**
     * @brief create the texture of the set name, to be rendered on screen later
     *
     */
    void generateNameTexture();

    /**
     * @brief Set the Set Name object
     *
     * @param name the name of the Set
     */
    void setName(std::string name);

    /**
     * @brief Get the Set Name object
     * @return std::string the name of the set
     */
    std::string getName();

    /**
     * @brief Get the Items object
     * @return std::vector<Item> a vector of the items of the set
     */
    const std::vector<Item>& getItems();

    LTexture getTexture();

   private:
    // holds the initialization status of the set (if it's ready to be shown on screen)
    bool _initialized;
    // The set name
    std::string _name;
    // A vector containing the Items from the set
    std::vector<Item> _items;
    // A texture containing the name of the set to be rendered
    LTexture _nameTexture;
};

#endif  // SET_H