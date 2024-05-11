void Displayroutes(Station *stations, routesNode *routeList, int Countroutes, 
                   int numStations, pricePair *priceTable, char *startStaCode, char *endStaCode);
int Displayselectedroutes(Station *stations, char *routes, int numStations, pricePair *priceTable);
char* DisplayColorStation(Station *stations, char *station);
int findcolour(char *station);
