#include "../include/rotfaifah.h"

void Displayroutes(Station *stations,routesNode *routeList,int Countroutes,int numStations, pricePair *priceTable){
    int end = 0;
    int startpoint = 0;
    int selector = 0;
    int endpoint = 10;
    if(Countroutes < 10) endpoint = Countroutes;
     printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " [%c] " ANSI_COLOR_LIGHT_WHITE "To go up | " ANSI_COLOR_GOLD "[%c] " ANSI_COLOR_LIGHT_WHITE "To go down\n", 24, 25);
            printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " Enter " ANSI_COLOR_LIGHT_WHITE "To choose\n");
            printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " ESC " ANSI_COLOR_LIGHT_WHITE "To go back\n");
    
    while(!end) {
        printSplitedLine();
        for(int i = startpoint;i< endpoint;i++){
            int asciiArrow = 0;
             if(i == selector) asciiArrow = ARROW_ASCII;
             if(i == selector)
                    printf(ANSI_COLOR_GOLD "%c " "[%d] " ANSI_STYLE_BOLD ANSI_COLOR_LIGHT_CYAN "[Total: %d | Price: %d]\n\n",asciiArrow,i,
                    routeList[i].visitedCount, routeList[i].price );
            else
                    printf(ANSI_COLOR_GOLD "%c " "[%d] " ANSI_STYLE_BOLD ANSI_COLOR_LIGHT_CYAN "[Total: %d | Price: %d]\n\n",asciiArrow,i, 
                    routeList[i].visitedCount, routeList[i].price );
        }
    
    printSplitedLine();
    int trueCodeSkip = 0; //check press enter or up arrow or down arrow
    int ch;
    while(trueCodeSkip == 0){
                ch = getch();
                // Handle arrow keys
                switch (ch) {
                    case 72: // Up arrow
                        if(selector != 0) selector--;
                        trueCodeSkip = 1;
                        if(selector == startpoint && startpoint != 0){
                            startpoint--;
                            endpoint--;
                        }
                        clearScreen();
                        break;
                    case 80: // Down arrow
                        if(selector != Countroutes - 1) selector++;
                        trueCodeSkip = 1;
                        if(selector == endpoint && endpoint != Countroutes){
                            endpoint++;
                            startpoint++;
                        }
                        clearScreen();
                        break;
                    case 13: // Enter key
                        end = 1;
                        trueCodeSkip = 1;
                        break;
                    default:
                        break;
                }
            }
            if(end == 1)
                Displayselectedroutes(stations,routeList[selector].visitedRoute,numStations, priceTable);
    }
}

void Displayselectedroutes(Station *stations, char *routes, int numStations, pricePair *priceTable){
    char *token = strtok(routes,",");
    char *startStation = NULL;
    char *latestStation = NULL;
    int count = 0;
    while(token != NULL){
        int index = findcolour(token);
        char *temp = CodeToName(token,stations,numStations);
        char *underscore_pos = strchr(token, '_');
        int length;
        if (underscore_pos != NULL) {
            length = underscore_pos - token;
        }
        if(strcmp(token,"INT") == 0) index = 10; 
        if(index != 10){
            if(count == 0){
                startStation = strdup(token);
            }
            latestStation = strdup(token);
            count++; 
        }else{
            count = 0;
        }
        switch (index)
        {
        case 0://MRTBL
            printf(ANSI_COLOR_WHITE"[%.*s] ", length, token);
            printf(ANSI_COLOR_BLUE "%s" "\n->\n", temp);
            break;
        case 1://ARL
            printf(ANSI_COLOR_WHITE"[%.*s] ", length, token);
            printf(ANSI_COLOR_RED "%s" "\n->\n", temp);
            break;
        case 2://BTSSIL
            printf(ANSI_COLOR_WHITE"[%.*s] ", length, token);
            printf(ANSI_COLOR_GREEN "%s" "\n->\n", temp);
            break;
        case 3://BTSSUK
            printf(ANSI_COLOR_WHITE"[%.*s] ", length, token);
            printf(ANSI_COLOR_LIGHT_GREEN "%s" "\n->\n", temp);
            break;
        case 4://BTSGL
            printf(ANSI_COLOR_WHITE"[%.*s] ", length, token);
            printf(ANSI_COLOR_GOLD "%s" "\n->\n", temp);
            break;
        case 5://MRTYL
            printf(ANSI_COLOR_WHITE"[%.*s] ", length, token);
            printf(ANSI_COLOR_LIGHT_YELLOW "%s" "\n->\n", temp);
            break;
        case 6://MRTPL
            printf(ANSI_COLOR_WHITE"[%.*s] ", length, token);
            printf(ANSI_COLOR_LIGHT_MAGENTA "%s" "\n->\n", temp);
            break;
        case 7://MRTPK
            printf(ANSI_COLOR_WHITE"[%.*s] ", length, token);
            printf(ANSI_COLOR_PINK "%s" "\n->\n", temp);
            break;
        case 8://SRTETLR
            printf(ANSI_COLOR_WHITE"[%.*s] ", length, token);
            printf(ANSI_COLOR_LIGHT_RED "%s" "\n->\n", temp);
            break;
        case 9://SRTETDR
            printf(ANSI_COLOR_WHITE"[%.*s] ", length, token);
            printf(ANSI_COLOR_RED "%s" "\n->\n", temp);
            break;
        case 10://INT
            printf(ANSI_COLOR_WHITE "Price: %d\n", calculatePriceBetweenStation(priceTable, startStation, latestStation));
            printf(ANSI_COLOR_WHITE "--------------\n");
            printf(ANSI_COLOR_WHITE "INTERCHANGE\n");
            printf(ANSI_COLOR_WHITE "--------------\n");
            printf(ANSI_COLOR_WHITE "->\n");
            break;
        default:
            break;
        }
        // printf("%s\n->\n",token);
        token = strtok(NULL,",");
    }
    printf(ANSI_RESET_ALL"Price: %d\n", calculatePriceBetweenStation(priceTable, startStation, latestStation));
}

char* DisplayColorStation(Station *stations, char *station){
    int index = findcolour(station);
    switch (index)
    {
    case 0://MRTBL
        return ANSI_COLOR_BLUE;
        break;
    case 1://ARL
        return ANSI_COLOR_RED;
        break;
    case 2://BTSSIL
        return ANSI_COLOR_GREEN;
        break;
    case 3://BTSSUK
        return ANSI_COLOR_LIGHT_GREEN;
        break;
    case 4://BTSGL
        return ANSI_COLOR_GOLD;
        break;
    case 5://MRTYL
        return ANSI_COLOR_LIGHT_YELLOW;
        break;
    case 6://MRTPL
        return ANSI_COLOR_LIGHT_MAGENTA;
        break;
    case 7://MRTPK
        return ANSI_COLOR_PINK;
        break;
    case 8://SRTETLR
        return ANSI_COLOR_LIGHT_RED;
        break;
    case 9://SRTETDR
        return ANSI_COLOR_RED;
        break;
    default:
        break;
    }
}

int findcolour(char *station){
    char stationName[][10] = {"MRTBL","ARL","BTSSIL","BTSSUK","BTSGL","MRTYL","MRTPL","MRTPK","SRTETLR","SRTETDR"};
    int i;
    for(i=0;i<=9;i++){
        char* status = strstr(station,stationName[i]);
        if(status){
            return i;
        }
    }
}