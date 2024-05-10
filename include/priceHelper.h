#define MAX_PRICE_TABLE_SIZE 5000

typedef struct pricePair{
    char staCode1[50];
    char staCode2[50];
    int price;
}pricePair;

void readPriceDataFromCSV(char* line, pricePair* pair);
int* calculateRoutesPrice(pricePair* priceTable, char** routes, int routesCount);