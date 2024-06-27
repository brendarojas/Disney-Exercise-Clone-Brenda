#ifndef CURLHANDLER_H
#define CURLHANDLER_H

#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
#include <iostream>

#define HOME_URL "https://cd-static.bamgrid.com/dp-117731241344/home.json"
#define SET_URL_PREFIX "https://cd-static.bamgrid.com/dp-117731241344/sets/"

struct sDATA {
    std::fstream* file;
    std::string* str;
};

size_t writeCallback(void* ptr, size_t size, size_t nmemb, sDATA* data);

/**
 * Fetches JSON data from url
 * @param url the URL to fetch the JSON data
 * @param data the data to be written by the writeCallback
 * @return true if success, false if failed
 */
bool fetchDataFromURL(std::string url, sDATA* data);

#endif