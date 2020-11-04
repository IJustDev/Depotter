#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <iostream>

using namespace std;

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string *data) {
    data->append((char*) ptr, size *nmemb);
    return size *nmemb;
}

char* constructAPIRequest(char* symbol) {
    char url[] = "API_REQUEST_URL_HERE";
    return url;
}

int getStockPrice(char* symbol) {
    auto curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, constructAPIRequest(symbol));
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        string response_string;
        string header_string;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return 0;
}

