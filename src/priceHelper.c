#include <stdio.h>
#include <stdlib.h>

#include "../include/rotfaifah.h"

void readPriceDataFromCSV(char* line, pricePair* pair) {
    char *token = strtok(line, ",");
    int col = 0;

    while (token != NULL) {
        switch(col) {
            case 2:
                strcpy(pair->staCode1, token);
                break;
            case 5:
                strcpy(pair->staCode2, token);
                break;
            case 6:
                pair->price = atoi(token);
                break;
            default:
                break;
        }
        col++;
        token = strtok(NULL, ",");
    }
}

int* calculateRoutesPrice(pricePair* priceTable, char** routes, int routesCount) {
    // char** routes = (char**)malloc(routesCount * sizeof(char*));
    int* routesPrice = calloc(routesCount, sizeof(int));
    for (int i = 0; i < routesCount; i++) {
        // routes[i] = strdup(inputRoutes);
        char* route = strdup(routes[i]);
        char* currentStation = strtok(route, ",");
        char* startStation = strdup(currentStation);
        char* prevStation = NULL;
        char* latestInter = NULL;
        while (currentStation != NULL) {
            if (strcmp(currentStation, "INT") == 0) {
                // interchanged, calculate this range price
                currentStation = strtok(NULL, ",");
                if (latestInter != NULL) routesPrice[i] += calculatePriceBetweenStation(priceTable, latestInter, prevStation);
                else routesPrice[i] += calculatePriceBetweenStation(priceTable, startStation, prevStation);
                latestInter = strdup(currentStation);
            }
            prevStation = strdup(currentStation);
            currentStation = strtok(NULL, ",");
        }
        if (latestInter != NULL) routesPrice[i] += calculatePriceBetweenStation(priceTable, latestInter, prevStation);
        else routesPrice[i] += calculatePriceBetweenStation(priceTable, startStation, prevStation);
    }
    printf("%d\n", routesPrice[0]);
    return routesPrice;
}

int calculatePriceBetweenStation(pricePair* priceTable, char* srcStation, char* destStation){
    int priceBetweenStation = 0;
    for (int j = 0; j < MAX_PRICE_TABLE_SIZE; j++) {
        if (((strcmp(destStation, priceTable[j].staCode1) == 0) && (strcmp(srcStation, priceTable[j].staCode2) == 0)) ||
        ((strcmp(destStation, priceTable[j].staCode2) == 0) && (strcmp(srcStation, priceTable[j].staCode1) == 0))) {
            priceBetweenStation += priceTable[j].price;
            break;
        }
    }
    return priceBetweenStation;
}