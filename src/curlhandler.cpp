#include "curlhandler.h"

size_t writeCallback(void* ptr, size_t size, size_t nmemb, sDATA* data) {
    size_t numBytes = size * nmemb;

    if (data->file) data->file->write((char*)ptr, numBytes);

    if (data->str) *(data->str) += std::string((char*)ptr, numBytes);

    return numBytes;
}

bool fetchDataFromURL(std::string url, sDATA* data) {
    // TODO Implement retries

    CURL* curl;
    CURLcode res;

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl = curl_easy_init();

    if (!curl) {
        std::cerr << "ERROR: curl initialization failed! curl = " << std::endl;
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    if (res != CURLE_OK) {
        std::cerr << "ERROR: curl failed! res = " << res << std::endl;
        return false;
    }
    return true;  // success
}
