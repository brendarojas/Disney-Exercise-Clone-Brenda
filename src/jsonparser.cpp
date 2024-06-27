#include "jsonparser.h"

int parseJSON(std::string json, rapidjson::Document& document) {
    if (document.Parse<0>(json.c_str()).HasParseError()) {
        std::cerr << "Error parsing JSON";
        return -1;
    }
    // validate correct data
    if (!document.IsObject() || !document.HasMember("data")) {
        std::cerr << "ERROR: Invalid JSON data" << std::endl;
        return -1;
    }
    return 0;
}