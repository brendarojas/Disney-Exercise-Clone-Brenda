#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <fstream>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

/**
 * Parse a JSON message and validate it has a parent member "data"
 * @param json JSON message to parse
 * @param document JSON document generated
 * @return 0 if success, -1 otherwise
 */
int parseJSON(std::string json, rapidjson::Document& document);

#endif  // JSONPARSER_H