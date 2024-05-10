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
                if (latestInter != NULL) {
                    for (int j = 0; j < MAX_PRICE_TABLE_SIZE; j++) {
                        if (((strcmp(latestInter, priceTable[j].staCode1) == 0) && (strcmp(prevStation, priceTable[j].staCode2) == 0)) ||
                        ((strcmp(latestInter, priceTable[j].staCode2) == 0) && (strcmp(prevStation, priceTable[j].staCode1) == 0))) {
                            // printf("route %d: from %s to %s, %d baht\n", i, latestInter, prevStation, priceTable[j].price);
                            routesPrice[i] += priceTable[j].price;
                            break;
                        }
                    }
                }
                else {
                    for (int j = 0; j < MAX_PRICE_TABLE_SIZE; j++) {
                        if (((strcmp(startStation, priceTable[j].staCode1) == 0) && (strcmp(prevStation, priceTable[j].staCode2) == 0)) ||
                        ((strcmp(startStation, priceTable[j].staCode2) == 0) && (strcmp(prevStation, priceTable[j].staCode1) == 0))) {
                            // printf("route %d: from %s to %s, %d baht\n", i, startStation, prevStation, priceTable[j].price);
                            routesPrice[i] += priceTable[j].price;
                            break;
                        }
                    }
                }
                latestInter = strdup(currentStation);
            }
            prevStation = strdup(currentStation);
            currentStation = strtok(NULL, ",");
        }
        if (latestInter != NULL) {
            // printf("[1]route %d: Last range from %s to %s\n", i, latestInter, prevStation);
            for (int j = 0; j < MAX_PRICE_TABLE_SIZE; j++) {
                if (((strcmp(latestInter, priceTable[j].staCode1) == 0) && (strcmp(prevStation, priceTable[j].staCode2) == 0)) ||
                ((strcmp(latestInter, priceTable[j].staCode2) == 0) && (strcmp(prevStation, priceTable[j].staCode1) == 0))) {
                    // printf("route %d: from %s to %s, ending %d baht\n", i, latestInter, prevStation, priceTable[j].price);
                    routesPrice[i] += priceTable[j].price;
                    break;
                }
            }
        }
        else {
            // printf("[2]route %d: Last range from %s to %s\n", i, startStation, prevStation);
            for (int j = 0; j < MAX_PRICE_TABLE_SIZE; j++) {
                if (((strcmp(prevStation, priceTable[j].staCode1) == 0) && (strcmp(startStation, priceTable[j].staCode2) == 0)) ||
                ((strcmp(prevStation, priceTable[j].staCode2) == 0) && (strcmp(startStation, priceTable[j].staCode1) == 0))) {
                    // printf("route %d: from %s to %s, ending %d baht\n", i, startStation, prevStation, priceTable[j].price);
                    routesPrice[i] += priceTable[j].price;
                    break;
                }
            }
        }
    }
    return routesPrice;
}

void sortingByPrice(char** routes, int* prices, int routesCount) {
    // selection sort (;
    for (int i = 0; i < routesCount; i++) {
        int jMin = i;
        for (int j = i + 1; j < routesCount; j++) {
            if (prices[j] < prices[jMin]) jMin = j;
        }
        if (jMin != i) {
            // swapping
            int temp = prices[i];
            prices[i] = prices[jMin];
            prices[jMin] = temp;

            char* tempR;
            strcpy(tempR, routes[i]);
            strcpy(routes[i], routes[jMin]);
            strcpy(routes[jMin], tempR);
        }
    }
}