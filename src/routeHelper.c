#include "../include/rotfaifah.h"

void DisplayRoutes(Station *stations, routesNode *routeList, int Countroutes, int numStations, pricePair *priceTable, char *startStaCode, char *endStaCode){
    int end = 0;
    int endToShow = 0;
    int startpoint = 0;
    int selector = 0;
    int endpoint = 10;
    if(Countroutes < 10) endpoint = Countroutes;
    while(!end) {
        printSplitedLine();
        printf(ANSI_COLOR_LIGHT_WHITE "Found" ANSI_STYLE_BOLD ANSI_COLOR_GOLD " %d " ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE "routes for\n" ANSI_RESET_ALL, Countroutes);
        printf(ANSI_COLOR_LIGHT_WHITE "Departure station: ");
        printStationText(startStaCode, stations, numStations, 1);
        printf(ANSI_COLOR_LIGHT_WHITE "Destination station: ");
        printStationText(endStaCode, stations, numStations, 1);
        printSplitedLine();
        printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " [%s] " ANSI_COLOR_LIGHT_WHITE "To go up | " ANSI_COLOR_GOLD "[%s] " ANSI_COLOR_LIGHT_WHITE "To go down\n", ARROW_UP_UTF8, ARROW_DOWN_UTF8);
        printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " Enter " ANSI_COLOR_LIGHT_WHITE "To choose\n");
        printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " ESC " ANSI_COLOR_LIGHT_WHITE "To go back\n");
        printSplitedLine();
        for(int i = startpoint;i< endpoint;i++){
            char *asciiArrow = ARROW_UTF8_NULL;
            if(i == selector) asciiArrow = ARROW_UTF8;
            if(i == selector)
                printf(ANSI_COLOR_GOLD "%s " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "[Routes #%d]" ANSI_RESET_ALL ANSI_STYLE_BOLD ANSI_COLOR_LIGHT_CYAN "[Total: " ANSI_COLOR_GOLD "%d " ANSI_COLOR_LIGHT_CYAN "Stations | Fare: " ANSI_COLOR_GOLD "%d " ANSI_COLOR_LIGHT_CYAN "Baht]\n" ANSI_RESET_ALL,
                asciiArrow, i + 1,
                routeList[i].visitedCount, routeList[i].price );
            else
                printf(ANSI_COLOR_GOLD "%s " ANSI_COLOR_GOLD "[Routes #%d]" ANSI_RESET_ALL ANSI_COLOR_LIGHT_CYAN "[Total: " ANSI_COLOR_GOLD "%d " ANSI_COLOR_LIGHT_CYAN "Stations | Fare: " ANSI_COLOR_GOLD "%d " ANSI_COLOR_LIGHT_CYAN "Baht]\n" ANSI_RESET_ALL,
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
                    if(selector == startpoint - 1 && startpoint != 0){
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
            DisplaySelectedRoutes(stations,routeList[selector].visitedRoute, selector, 
            routeList[selector].visitedCount, routeList[selector].price, startStaCode, endStaCode, 
            numStations, priceTable);
            fflush(stdin);
            endToShow = 0;
            end = 0;
        }
    }
}

int DisplaySelectedRoutes(Station *stations, char *routes, int routeNo, int routeVisCount, 
                          int routeFare, char *startSta, char *endSta, int numStations, 
                          pricePair *priceTable) {
    
    printf(ANSI_COLOR_LIGHT_WHITE "Showing Routes " ANSI_COLOR_GOLD "#%d\n" ANSI_RESET_ALL, routeNo + 1);
    printSplitedLine();
    
    char *dupRoutes = strdup(routes);
    char *token = strtok(dupRoutes,",");
    char *startStation = NULL;
    char *latestStation = NULL;
    
    int count = 0;
    int passingAnInterchange = 0;
    int routeInterchange = 0;
    
    while(token != NULL){
        int index = 0;
        int length;
        int isToBeBold = 0;
        int isIntr = 0;
        
        char *temp = strdup(CodeToName(token,stations,numStations));
        char *tempFullCode = strdup(token);
        char *tempShortCode = strdup(CodeToShortCode(token,stations,numStations));
        
        if(strcmp(token,"INT") == 0) index = 10; 
        else if(strcmp(token,"IN0") == 0) index = 11; 
        
        if(index != 10){
            if(count == 0){
                startStation = strdup(token);
                isToBeBold = 1;
            }
            latestStation = strdup(token);
            count++; 
        }else{
            count = 0;
        }
        
        switch (index){
            case 0:
                if(strcmp(tempFullCode,"MRTBL_BL0X") == 0){ //MRTBL_BL0X : Interchange without fare Special
                    char *staColor = printStationColorOnly("MRTBL_BL01", stations, numStations);
                    printf(" %s%s ",staColor,ANSI_BLOCK);
                    printStationText("MRTBL_BL01", stations, numStations, 0);
                    printf(" %s%s ",staColor,ANSI_BLOCK);
                    routeInterchange++;
                    printf(ANSI_COLOR_LIGHT_WHITE"  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                    printf(ANSI_COLOR_LIGHT_WHITE "---------------------------------\n" ANSI_RESET_ALL);
                    printf(ANSI_COLOR_LIGHT_WHITE " INTERCHANGE STATION (No Fare) \n" ANSI_RESET_ALL);
                    printf(ANSI_COLOR_LIGHT_WHITE "---------------------------------\n" ANSI_RESET_ALL);
                    printf(" %s%s ",staColor,ANSI_BLOCK);
                    printf(ANSI_COLOR_LIGHT_WHITE"  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                    printf(" %s%s ",staColor,ANSI_BLOCK);
                    printStationText("MRTBL_BL01", stations, numStations, 1);
                    printf(" %s%s ",staColor,ANSI_BLOCK);
                    printf(ANSI_COLOR_LIGHT_WHITE"  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                }else{ //Normal case
                    char *staColor = printStationColorOnly(tempFullCode, stations, numStations);
                    if(passingAnInterchange) delLastLine();
                    if(passingAnInterchange) moveCursorUp(1);
                    // if(passingAnInterchange) moveCursorUp(1);
                    if(passingAnInterchange) printf(" %s%s ",staColor,ANSI_BLOCK);
                    if(passingAnInterchange) printf(ANSI_COLOR_LIGHT_WHITE"  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                    printf(" %s%s ",staColor,ANSI_BLOCK);
                    printStationText(tempFullCode, stations, numStations, isToBeBold);
                    printf(" %s%s ",staColor,ANSI_BLOCK);
                    printf(ANSI_COLOR_LIGHT_WHITE"  %s  \n" ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                    passingAnInterchange = 0;
                }
                break;
            case 10://INT
                passingAnInterchange = 1;
                routeInterchange++;
                int price = calculatePriceBetweenStation(priceTable, startStation, latestStation);
                printf(ANSI_COLOR_LIGHT_WHITE "Fare:" ANSI_COLOR_GOLD " ฿%d\n" ANSI_RESET_ALL, price);
                if(price == 0){
                    printf(ANSI_COLOR_LIGHT_WHITE "---------------------------------\n" ANSI_RESET_ALL);
                    printf(ANSI_COLOR_LIGHT_WHITE " INTERCHANGE STATION (No Fare)   \n" ANSI_RESET_ALL);
                    printf(ANSI_COLOR_LIGHT_WHITE "---------------------------------\n" ANSI_RESET_ALL);
                }else{
                    printf(ANSI_COLOR_LIGHT_WHITE "---------------------\n"ANSI_RESET_ALL);
                    printf(ANSI_COLOR_LIGHT_WHITE " INTERCHANGE STATION \n"ANSI_RESET_ALL);
                    printf(ANSI_COLOR_LIGHT_WHITE "---------------------\n"ANSI_RESET_ALL);
                }
                printf("%s ",ANSI_BLOCK);
                printf(ANSI_COLOR_LIGHT_WHITE"  %s  " ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                break;
            case 11://IN0 (Interchange without fare)
                passingAnInterchange = 1;
                routeInterchange++;
                printf(ANSI_COLOR_LIGHT_WHITE "---------------------------------\n" ANSI_RESET_ALL);
                printf(ANSI_COLOR_LIGHT_WHITE " INTERCHANGE STATION (No Fare)   \n" ANSI_RESET_ALL);
                printf(ANSI_COLOR_LIGHT_WHITE "---------------------------------\n" ANSI_RESET_ALL);
                printf("%s ",ANSI_BLOCK);
                printf(ANSI_COLOR_LIGHT_WHITE"  %s  " ANSI_RESET_ALL, ARROW_DOWN_UTF8);
                break;
            default:
                break;
        }
        free(temp);
        free(tempFullCode);
        free(tempShortCode);
        token = strtok(NULL,",");
    }
    delLastEnteredLine();
    moveCursorUp(1);
    printf(ANSI_COLOR_LIGHT_WHITE "Fare:" ANSI_COLOR_GOLD " ฿%d\n" ANSI_RESET_ALL, calculatePriceBetweenStation(priceTable, startStation, latestStation));
    moveCursorDown(1);
    printSplitedLine();
    
    printf(ANSI_COLOR_LIGHT_WHITE ANSI_STYLE_BOLD "Route(" ANSI_COLOR_GOLD "#%d" ANSI_COLOR_LIGHT_WHITE ")\n"ANSI_RESET_ALL, routeNo + 1);
    printf(ANSI_COLOR_LIGHT_WHITE ANSI_STYLE_BOLD " %s Departure station: " ANSI_RESET_ALL, ANSI_BULLET);
    printStationText(startSta, stations, numStations, 0);
    printf(ANSI_COLOR_LIGHT_WHITE ANSI_STYLE_BOLD " %s Destination station: " ANSI_RESET_ALL, ANSI_BULLET);
    printStationText(endSta, stations, numStations, 0);
    
    printf(ANSI_COLOR_LIGHT_WHITE ANSI_STYLE_BOLD " %s Total Fare: " ANSI_COLOR_GOLD "฿%d\n" ANSI_RESET_ALL, ANSI_BULLET, routeFare);
    printf(ANSI_COLOR_LIGHT_WHITE ANSI_STYLE_BOLD " %s Total Interchanged Station: " ANSI_COLOR_GOLD "%d Station(s)\n" ANSI_RESET_ALL, ANSI_BULLET, routeInterchange);
    printf(ANSI_COLOR_LIGHT_WHITE ANSI_STYLE_BOLD " %s Total Passed Station: " ANSI_COLOR_GOLD "%d Station(s)\n" ANSI_RESET_ALL, ANSI_BULLET, routeVisCount);
    
    printSplitedLine();
    
    free(startStation);
    free(latestStation);
    enterAnyKeyToGoBack();
    clearScreen();
}