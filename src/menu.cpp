#include "menu.h"

bool _menuInitialized;
unsigned int _selectedSet = 0;
unsigned int _selectedItem = 0;
unsigned int _setPage = 0;
unsigned int _itemPage = 0;
std::vector<Set> menu;

void populateMenu(const rapidjson::Value& collection) {
    for (rapidjson::SizeType currContIdx = 0; currContIdx < collection.Size(); currContIdx++) {
        const rapidjson::Value& JSONset = collection[currContIdx]["set"];
        std::string tmpSetName = JSONset["text"]["title"]["full"]["set"]["default"]["content"].GetString();
        Set newSet(tmpSetName);  // temporary set, later is going to be pushed into the vector of sets
        if (JSONset.HasMember("refId")) {
            // get the JSON from the URL with the refId
            std::string refIdSet{};
            sDATA refSetData{NULL, &refIdSet};  // we only the data in string format, not file
            // build the URL of the refId set and fetch the json data from it.
            std::string refSetURL = SET_URL_PREFIX + std::string(JSONset["refId"].GetString()) + ".json";
            if (!fetchDataFromURL(refSetURL, &refSetData)) {
                std::cerr << "WARNING: fetching dynamic set data failed!" << std::endl;
                continue;
            }
            rapidjson::Document setDoc;
            if (parseJSON(refIdSet, setDoc)) {
                std::cerr << "WARNING: Something went wrong" << std::endl;
                continue;
            }
            // get the name of the set, could be "CuratedSet", "PersonalizedCuratedSet", etc.
            std::string setType = setDoc["data"].MemberBegin()->name.GetString();
            // this populates the sets
            newSet.fetchItems(setDoc["data"][setType.c_str()]);
        } else if (JSONset.HasMember("meta") && JSONset.HasMember("items")) {
            // Populate using available data.
            newSet.fetchItems(JSONset);
        } else {
            std::cout << "WARNING: Invalid set, ignoring";
            continue;
        }

        // push the populated set into the menu
        menu.push_back(newSet);

        // if the vector has data, consider the menu initialized.
        // this is for the effect of clearing the splash image and start rendering the menu to screen
        if (!_menuInitialized && menu.size()) {
            _menuInitialized = true;
        }
        std::cout << std::endl;  // newline
    }
}

void renderMenu() {
    // for each set...
    unsigned int setIdx = 0;
    for (auto setIt = menu.begin(); setIt != menu.end(); ++setIt, setIdx++) {
        // first we need to render the set name
        setIt->getTexture().renderAt(TEXT_X_COORD, TEXT_Y_COORD(setIdx), false);

        // then we need to render the images
        unsigned int itemIdx = 0;
        auto tmpItems = setIt->getItems();
        for (auto itemIt = tmpItems.begin(); itemIt != tmpItems.end(); ++itemIt, itemIdx++) {
            // finish computing the position of the sets
            itemIt->getTexture().renderAt(ITEM_X_COORD(itemIdx), ITEM_Y_COORD(setIdx),
                                          (_selectedSet == setIdx) && (_selectedItem == itemIdx));
        }
    }

    // Update Screen to show the picture
    SDL_RenderPresent(_renderer);
}

void selectPrevSet() {
    if (_selectedSet > 0) {
        _selectedSet--;
        _setPage = _selectedSet / SETS_PER_PAGE;
        std::cout << "set: " << _selectedSet << ", page: " << _setPage << std::endl;
    }
}

void selectNextSet() {
    std::cout << "menu size: " << menu.size() << std::endl;
    if (_selectedSet < menu.size() - 1) {
        _selectedSet++;
        _setPage = _selectedSet / SETS_PER_PAGE;
        std::cout << "set: " << _selectedSet << ", page: " << _setPage << std::endl;
    }
}

void selectPrevItem() {
    if (_selectedItem > 0) {
        _selectedItem--;
        _itemPage = _selectedItem / ITEMS_PER_PAGE;
        std::cout << "Item: " << _selectedItem << ", page: " << _itemPage << std::endl;
    }
}

void selectNextItem() {
    if (_selectedItem < menu.at(_selectedSet).getItems().size() - 1) {
        _selectedItem++;
        _itemPage = _selectedItem / ITEMS_PER_PAGE;
        std::cout << "Item: " << _selectedItem << ", page: " << _itemPage << std::endl;
    }
}