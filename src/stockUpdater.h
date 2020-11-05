#include <string>

#ifndef Stockupdater_H_
#define Stockupdater_H_
char* constructAPIRequest(const char* symbol);

double getStockPrice(const char* symbol);
#endif
