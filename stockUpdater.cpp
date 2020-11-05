#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <cjson/cJSON.h>

using namespace std;

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string *data) {
    data->append((char*) ptr, size *nmemb);
    return size *nmemb;
}

char* constructAPIRequest(const char* symbol) {
    string symbol_string(symbol);
    char* urlPartOne = "https://query2.finance.yahoo.com/v10/finance/quoteSummary/"; 
    char *urlPartTwo = "?formatted=true&lang=de-DE&region=DE&modules=price";
    char *url;
    asprintf(&url, "%s%s%s", urlPartOne, symbol, urlPartTwo);

    return url;
}

double parseYahooResponse(const char* const response) {
    const cJSON *response_json = cJSON_Parse(response);
    const cJSON *quoteSummary = cJSON_GetObjectItemCaseSensitive(response_json, "quoteSummary");
    const cJSON *result = cJSON_GetObjectItemCaseSensitive(quoteSummary, "result");
    const cJSON *first_result = cJSON_GetArrayItem(result, 0);
    const cJSON *price = cJSON_GetObjectItemCaseSensitive(first_result, "price");
    const cJSON *regularMarketPrice = cJSON_GetObjectItemCaseSensitive(price, "regularMarketPrice");
    const cJSON *finalPrice = cJSON_GetObjectItemCaseSensitive(regularMarketPrice, "raw");
    return finalPrice->valuedouble;
}

double getStockPrice(const char* symbol) {
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

        const char *response_chars = response_string.c_str();
        return parseYahooResponse(response_chars);
    }
    return -1;
}

