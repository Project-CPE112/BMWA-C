void DisplayRoutes(Station *stations, routesNode *routeList, int Countroutes, 
                   int numStations, pricePair *priceTable, char *startStaCode, char *endStaCode);
int DisplaySelectedRoutes(Station *stations, char *routes, int routeNo, int routeFare, int numStations, pricePair *priceTable);
// char* DisplayColorStation(Station *stations, char *station);
int findColour(char *station);
