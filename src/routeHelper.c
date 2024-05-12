#include "../include/rotfaifah.h"

void DisplayRoutes(Station *stations, routesNode *routeList, int Countroutes, 
                   int numStations, pricePair *priceTable, char *startStaCode, char *endStaCode){
    int end = 0;
    int endToShow = 0;
    int startpoint = 0;
    int selector = 0;
    int endpoint = 10;
    if(Countroutes < 10) endpoint = Countroutes;
    while(!end) {
        printSplitedLine();
        printf(ANSI_COLOR_LIGHT_WHITE "Found" ANSI_STYLE_BOLD ANSI_COLOR_GOLD " %d " ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE "routes for\n" ANSI_RESET_ALL, Countroutes);
        printf(ANSI_COLOR_LIGHT_WHITE "Departure station: " ANSI_COLOR_LIGHT_CYAN "[%s]" ANSI_COLOR_LIGHT_WHITE " %s\n" ANSI_RESET_ALL, 
               CodeToShortCode(startStaCode, stations, numStations), 
               CodeToName(startStaCode, stations, numStations));
        printf(ANSI_COLOR_LIGHT_WHITE "Destination station: " ANSI_COLOR_LIGHT_CYAN "[%s]" ANSI_COLOR_LIGHT_WHITE " %s\n" ANSI_RESET_ALL, 
               CodeToShortCode(endStaCode, stations, numStations), 
               CodeToName(endStaCode, stations, numStations));
        printSplitedLine();
        printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " [%s] " ANSI_COLOR_LIGHT_WHITE "To go up | " ANSI_COLOR_GOLD "[%s] " ANSI_COLOR_LIGHT_WHITE "To go down\n", ARROW_UP_UTF8, ARROW_DOWN_UTF8);
        printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " Enter " ANSI_COLOR_LIGHT_WHITE "To choose\n");
        printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " ESC " ANSI_COLOR_LIGHT_WHITE "To go back\n");
        printSplitedLine();
        for(int i = startpoint;i< endpoint;i++){
            char *asciiArrow = ARROW_UTF8_NULL;
            if(i == selector) asciiArrow = ARROW_UTF8;
            if(i == selector)
                printf(ANSI_COLOR_GOLD "%s " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "[Routes #%d]" ANSI_RESET_ALL ANSI_STYLE_BOLD ANSI_COLOR_LIGHT_CYAN "[Total: %d Stations | Fare: %d Baht]\n" ANSI_RESET_ALL,
                asciiArrow, i + 1,
                routeList[i].visitedCount, routeList[i].price );
            else
                printf(ANSI_COLOR_GOLD "%s " ANSI_COLOR_GOLD "[Routes #%d]" ANSI_RESET_ALL ANSI_COLOR_LIGHT_CYAN "[Total: %d Stations | Fare: %d Baht]\n" ANSI_RESET_ALL,
                asciiArrow, i + 1, 
                routeList[i].visitedCount, routeList[i].price );
        }
    
        printSplitedLine();
        int trueCodeSkip = 0;
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
                    end = 0;
                    endToShow = 1;
                    trueCodeSkip = 1;
                    break;
                case 27 : // ESC key
                    end = 1;
                    endToShow = 0;
                    trueCodeSkip = 1;
                    break;
                default:
                    break;
            }
        }
        if(endToShow == 1 && end == 0){
            clearScreen();
            DisplaySelectedRoutes(stations,routeList[selector].visitedRoute, selector, routeList[selector].price, numStations, priceTable);
            fflush(stdin);
            endToShow = 0;
            end = 0;
        }
    }
}

int DisplaySelectedRoutes(Station *stations, char *routes, int routeNo, int routeFare, int numStations, pricePair *priceTable) {
    printf(ANSI_COLOR_LIGHT_WHITE "Showing Routes " ANSI_COLOR_GOLD "#%d\n\n", routeNo + 1);
    char *dupRoutes = strdup(routes);
    char *token = strtok(dupRoutes,",");
    char *startStation = NULL;
    char *latestStation = NULL;
    int count = 0;
    int thaphra33 = 0;
    int thaphra32 = 0;
    int thaphra02 = 0;
    int thaphraint = 0;
    if(strstr(routes,"MRTBL_BL32,MRTBL_BL01,MRTBL_BL02")) thaphraint = 1;
    else if(strstr(routes,"MRTBL_BL33,MRTBL_BL01,MRTBL_BL02")) thaphraint = 1;
    else if(strstr(routes,"MRTBL_BL02,MRTBL_BL01,MRTBL_BL32")) thaphraint = 1;
    else if(strstr(routes,"MRTBL_BL02,MRTBL_BL01,MRTBL_BL33")) thaphraint = 1;
    while(token != NULL){
        int index = findColour(token);
        char *temp = CodeToName(token,stations,numStations);
        char *tempShortCode = CodeToShortCode(token,stations,numStations);
        int length;
        if(strcmp(token,"INT") == 0) index = 10; 
        else if(strcmp(token,"IN0") == 0) index = 11; 
        if(index != 10){
            if(count == 0){
                startStation = strdup(token);
            }
            latestStation = strdup(token);
            count++; 
        }else{
            count = 0;
        }
        switch (index){
        case 0://MRTBL
            if(thaphraint == 1){
            //start of code that need 4 indent space
            if(strcmp(tempShortCode,"BL33") == 0) thaphra33 = 1;
            else if(strcmp(tempShortCode,"BL32") == 0) thaphra32 = 1;
            else if(strcmp(tempShortCode,"BL02") == 0) thaphra02 = 1;
            else if(strcmp(tempShortCode,"BL01") == 0){

            }else{
                printf(ANSI_COLOR_BLUE"[%s] ", tempShortCode);
                printf(ANSI_COLOR_LIGHT_WHITE "%s", temp);
                printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            }
            if(strcmp(tempShortCode,"BL01") == 0){
                if(thaphra02 == 1) thaphra02 = 2;
                if(thaphra32 == 1) thaphra32 = 2;
                if(thaphra33 == 1) thaphra33 = 2;
            }else{
                if(strcmp(tempShortCode,"BL33") == 0 && (thaphra02 == 2)) thaphra02 = 3;
                if(strcmp(tempShortCode,"BL32") == 0 && (thaphra02 == 2)) thaphra02 = 3;
                if(strcmp(tempShortCode,"BL02") == 0 && (thaphra33 == 2 || thaphra32 == 2)){
                    if(thaphra32 == 2) thaphra32 = 3;
                    if(thaphra33 == 2) thaphra33 = 3;
                }
            }
            if(strcmp(tempShortCode,"BL33") == 0 && thaphra02 == 3){
                delLastEnteredLine();
                delLastEnteredLine();
                printf(ANSI_COLOR_BLUE"[%s] ", "BL02");
                printf(ANSI_COLOR_LIGHT_WHITE "%s", "Charan 13");
                printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                printf(ANSI_COLOR_BLUE"[%s] ", "BL01");
                printf(ANSI_COLOR_LIGHT_WHITE "%s", "Tha Phra");
                printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                printf(ANSI_COLOR_LIGHT_WHITE "---------------------------------\n");
                printf(ANSI_COLOR_LIGHT_WHITE " INTERCHANGE STATION (No Fare) \n");
                printf(ANSI_COLOR_LIGHT_WHITE "---------------------------------\n");
                printf(ANSI_COLOR_LIGHT_WHITE"  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                printf(ANSI_COLOR_BLUE"[%s] ", "BL01");
                printf(ANSI_COLOR_LIGHT_WHITE "%s", "Tha Phra");
                printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                printf(ANSI_COLOR_BLUE"[%s] ", tempShortCode);
                printf(ANSI_COLOR_LIGHT_WHITE "%s", temp);
                printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            }
            if(strcmp(tempShortCode,"BL32") == 0 && thaphra02 == 3){
                delLastEnteredLine();
                delLastEnteredLine();
                printf(ANSI_COLOR_BLUE"[%s] ", "BL02");
                printf(ANSI_COLOR_LIGHT_WHITE "%s", "Charan 13");
                printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                printf(ANSI_COLOR_BLUE"[%s] ", "BL01");
                printf(ANSI_COLOR_LIGHT_WHITE "%s", "Tha Phra");
                printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                printf(ANSI_COLOR_LIGHT_WHITE "---------------------------------\n");
                printf(ANSI_COLOR_LIGHT_WHITE " INTERCHANGE STATION (No Fare) \n");
                printf(ANSI_COLOR_LIGHT_WHITE "---------------------------------\n");
                printf(ANSI_COLOR_LIGHT_WHITE"  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                printf(ANSI_COLOR_BLUE"[%s] ", "BL01");
                printf(ANSI_COLOR_LIGHT_WHITE "%s", "Tha Phra");
                printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                printf(ANSI_COLOR_BLUE"[%s] ", tempShortCode);
                printf(ANSI_COLOR_LIGHT_WHITE "%s", temp);
                printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            }
            if(strcmp(tempShortCode,"BL02") == 0 && (thaphra33 == 3 || thaphra32 == 3)){
                delLastEnteredLine();
                delLastEnteredLine();
                if(thaphra33 == 3){
                    printf(ANSI_COLOR_BLUE"[%s] ", "BL33");
                    printf(ANSI_COLOR_LIGHT_WHITE "%s", "Bang Phai");
                    printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                }else if(thaphra32 == 3){
                    printf(ANSI_COLOR_BLUE"[%s] ", "BL32");
                    printf(ANSI_COLOR_LIGHT_WHITE "%s", "Itsaraphap");
                    printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                }
                printf(ANSI_COLOR_BLUE"[%s] ", "BL01");
                printf(ANSI_COLOR_LIGHT_WHITE "%s", "Tha Phra");
                printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                printf(ANSI_COLOR_LIGHT_WHITE "---------------------------------\n");
                printf(ANSI_COLOR_LIGHT_WHITE " INTERCHANGE STATION (No Fare) \n");
                printf(ANSI_COLOR_LIGHT_WHITE "---------------------------------\n");
                printf(ANSI_COLOR_LIGHT_WHITE"  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                printf(ANSI_COLOR_BLUE"[%s] ", "BL01");
                printf(ANSI_COLOR_LIGHT_WHITE "%s", "Tha Phra");
                printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                printf(ANSI_COLOR_BLUE"[%s] ", tempShortCode);
                printf(ANSI_COLOR_LIGHT_WHITE "%s", temp);
                printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            }
            //end of code that need 4 indent space
            }else{
                printf(ANSI_COLOR_BLUE"[%s] ", tempShortCode);
                printf(ANSI_COLOR_LIGHT_WHITE "%s", temp);
                printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            }
            break;
        case 1://ARL
            printf(ANSI_COLOR_RED"[%s] ", tempShortCode);
            printf(ANSI_COLOR_LIGHT_WHITE "%s", temp);
            printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            break;
        case 2://BTSSIL
            printf(ANSI_COLOR_GREEN"[%s] ", tempShortCode);
            printf(ANSI_COLOR_LIGHT_WHITE "%s", temp);
            printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            break;
        case 3://BTSSUK
            printf(ANSI_COLOR_LIGHT_GREEN"[%s] ", tempShortCode);
            printf(ANSI_COLOR_LIGHT_WHITE "%s", temp);
            printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            break;
        case 4://BTSGL
            printf(ANSI_COLOR_GOLD"[%s] ", tempShortCode);
            printf(ANSI_COLOR_LIGHT_WHITE "%s", temp);
            printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            break;
        case 5://MRTYL
            printf(ANSI_COLOR_LIGHT_YELLOW"[%s] ", tempShortCode);
            printf(ANSI_COLOR_LIGHT_WHITE "%s", temp);
            printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            break;
        case 6://MRTPL
            printf(ANSI_COLOR_LIGHT_MAGENTA"[%s] ", tempShortCode);
            printf(ANSI_COLOR_LIGHT_WHITE "%s", temp);
            printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            break;
        case 7://MRTPK
            printf(ANSI_COLOR_PINK"[%s] ", tempShortCode);
            printf(ANSI_COLOR_LIGHT_WHITE "%s", temp);
            printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            break;
        case 8://SRTETLR
            printf(ANSI_COLOR_LIGHT_RED"[%s] ", tempShortCode);
            printf(ANSI_COLOR_LIGHT_WHITE "%s", temp);
            printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            break;
        case 9://SRTETDR
            printf(ANSI_COLOR_RED"[%s] ", tempShortCode);
            printf(ANSI_COLOR_LIGHT_WHITE "%s", temp);
            printf(ANSI_COLOR_LIGHT_WHITE"\n  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            break;
        case 10://INT
            printf(ANSI_COLOR_LIGHT_WHITE "Fare: %d\n", calculatePriceBetweenStation(priceTable, startStation, latestStation));
            printf(ANSI_COLOR_LIGHT_WHITE "---------------------\n");
            printf(ANSI_COLOR_LIGHT_WHITE " INTERCHANGE STATION \n");
            printf(ANSI_COLOR_LIGHT_WHITE "---------------------\n");
            printf(ANSI_COLOR_LIGHT_WHITE"  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            break;
        case 11://IN0 (Interchange without fare)
            printf(ANSI_COLOR_LIGHT_WHITE "---------------------------------\n");
            printf(ANSI_COLOR_LIGHT_WHITE " INTERCHANGE STATION (No Fare) \n");
            printf(ANSI_COLOR_LIGHT_WHITE "---------------------------------\n");
            printf(ANSI_COLOR_LIGHT_WHITE"  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
            break;
        default:
            break;
        }
        token = strtok(NULL,",");
    }
    delLastEnteredLine();
    printf(ANSI_COLOR_LIGHT_WHITE "Fare: %d\n\n" ANSI_RESET_ALL, calculatePriceBetweenStation(priceTable, startStation, latestStation));
    printf(ANSI_COLOR_LIGHT_WHITE ANSI_STYLE_BOLD "Total Fare: " ANSI_COLOR_GOLD "฿%d\n" ANSI_RESET_ALL, routeFare);

    enterAnyKeyToGoBack();
    clearScreen();
}

int findColour(char *station){
    char stationName[][10] = {"MRTBL","ARL","BTSSIL","BTSSUK","BTSGL","MRTYL","MRTPL","MRTPK","SRTETLR","SRTETDR"};
    int i;
    for(i=0;i<=9;i++){
        char* status = strstr(station,stationName[i]);
        if(status){
            return i;
        }
    }
}