#include <signal.h>
#include <fstream>
#include <iostream>
#include "curlhandler.h"
#include "jsonparser.h"
#include "menu.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "sdl.h"

int main() {
    // register the interrupt handler
    signal(SIGINT, interruptHandler);

    // SDL Initialization, window and renderer creation, etc.
    if (initSDL() != 0) {
        std::cerr << "Could not initialize SDL. Exiting" << std::endl;
        return -1;
    }

    // Load and render splash image (disney+ logo)
    loadSplashImg(SPLASH_IMG);

    if (!loadSDLFont()) {
        std::cerr << "Could not load Font. Exiting" << std::endl;
        return -1;
    }

    std::cout << "Loaded font" << std::endl;

    std::string json{};
    sDATA data{NULL, &json};  // we only the data in string format, not file

    if (!fetchDataFromURL(HOME_URL, &data)) {
        std::cerr << "ERROR: fetching data failed!";
        return -1;
    }

    rapidjson::Document home_doc;
    if (parseJSON(json, home_doc)) {
        std::cerr << "ERROR: Parsing JSON failed";
        return -1;
    }

    const rapidjson::Value& collection = home_doc["data"]["StandardCollection"]["containers"];
    populateMenu(collection);

    // std::cout << "TEXT: " << menuData.getMenu().front().getName() << std::endl;

    // once menu is populated we will start rendering
    clearScreen();

    renderMenu();

    // main loop
    while (_keepRunning) {
        handleEvents();
        clearScreen();
        renderMenu();
    }

    // terminate SDL instance
    closeSDL();

    return 0;
}
