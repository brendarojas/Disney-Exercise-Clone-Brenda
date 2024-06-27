#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include "curlhandler.h"
#include "jsonparser.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "set.h"

extern unsigned int _selectedSet;
extern unsigned int _selectedItem;

void populateMenu(const rapidjson::Value& collection);
void renderMenu();

void selectPrevSet();
void selectNextSet();
void selectPrevItem();
void selectNextItem();

#endif  // MENU_H