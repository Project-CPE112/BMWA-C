#include "include/rotfaifah.h"

//Function prototypes
void firstPanel();

int numStations = 0;
int pricePairsCount = 0;

Station stations[MAX_STATIONS];
pricePair priceTable[MAX_PRICE_TABLE_SIZE]; 

// Function to read station data from CSV
void readStationsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf(ANSI_COLOR_LIGHT_RED "Error: Could not open file %s\n" ANSI_RESET_ALL, filename);
        exit(1);
    }
    char line[1024];
    char buffer[1024];
    fgets(buffer, 1024, file); //Skip first line
    while (fgets(line, 1024, file)) {
        Station station;
        parse_csv_line_graph_station(line, &station);
        stations[numStations++] = station;
    }
    fclose(file);
}

void createPriceTable(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf(ANSI_COLOR_LIGHT_RED "Error: Could not open file %s\n" ANSI_RESET_ALL, filename);
        exit(1);
    }
    char line[1024];
    char buffer[1024]; // heading exclude
    fgets(buffer, 1024, file); //Skip first line
    while (fgets(line, 1024, file)) {
        pricePair pair;
        readPriceDataFromCSV(line, &pair);
        priceTable[pricePairsCount++] = pair;
    }
    fclose(file);
}

int main() {
    changeLocale();
    printf(ANSI_COLOR_LIGHT_CYAN "Initialization Rotfaifah....." ANSI_RESET_ALL);
    clearScreen();
    readStationsFromFile("metro_graph.csv");
    createPriceTable("priceTable.csv");
    firstPanel();
    return 0;
}

void firstPanel(){
    int option;
    printHeader(10, numStations);
    printSplitedLine();
    printMenu();
    printOption(1, "Display station information");
    printOption(2, "Find routes");
    printOption(3, "Exit program");
    printEnterChoice();
    // printf("%s to %s : %d baht\n", priceTable[0].staCode1, priceTable[0].staCode2, priceTable[0].price);
    int optionScan = scanf("%d", &option);
    if(optionScan != 1){
    	clearScreen();
	   	while (getchar() != '\n');
		printError("Invalid option");
        firstPanel();
    }
    switch (option) {
        case 1: {
        	clearScreen();
        	printHeader(10, numStations);
    		printSplitedLine();
    		printf(ANSI_COLOR_GOLD ANSI_STYLE_BOLD " Find station to display it details\n" ANSI_RESET_ALL);
            char code[50];
            findStationByName(stations, code, numStations,"Find station to display it details\n", NULL);
            printStationInfo(code, stations, numStations);
            enterAnyKey();
			clearScreen();
			firstPanel();
			break;
		}
        case 2: {
            clearScreen();
			char start[50], end[50];

            // start changing fucking code 
            printOption(1, "Insert Departure First");
            printOption(2, "Insert Destination First");
            printOption(3, "Go back!");

            printEnterChoice();

            int choice;
            int optionScan = scanf("%d", &choice);
            if(optionScan != 1){
                clearScreen();
                while (getchar() != '\n');
                printError("Invalid option");
                firstPanel();
            }
            char show[5] = "SHOW";
            int optionPass = 0;
            switch (choice) {
                case 1: {
                    optionPass = 1;
                    printf("Enter departure station: ");
                    findStationByName(stations, start, numStations,"Find Departure station\n", NULL);
                    

                    printf(ANSI_COLOR_LIGHT_WHITE "Departure station: ");
                    printStationText(start, stations, numStations, 1);

                    findStationByName(stations, end, numStations,"Find Destination station\n",show);
                    break;
                }
                case 2: {
                    optionPass = 1;
                    printf("Enter destination station: ");
                    findStationByName(stations, end, numStations,"Find Destination station\n", NULL);
                    
                    printf(ANSI_COLOR_LIGHT_WHITE "Destination station: ");
                    printStationText(end, stations, numStations, 1);

                    findStationByName(stations, start, numStations, "Find Departure station\n", show);
                    break;
                }
                case 3: {
                    optionPass = 2;
                    break;
                }
                default:
                    optionPass = 0;
                    break;
            }
            if(optionPass == 2){
                enterAnyKey();
                clearScreen();
                firstPanel();
                break;
            }
            if(optionPass == 0){
                printError("Invalid Option!");
                enterAnyKey();
                clearScreen();
                firstPanel();
                break;
            }
			if(strcmp(start, end) == 0){
                printError("No path found!");
                enterAnyKey();
                clearScreen();
                firstPanel();
                break;
            }
            printf(ANSI_STYLE_BOLD ANSI_COLOR_LIGHT_CYAN "Finding your routes...\n");
            printf(ANSI_COLOR_LIGHT_WHITE "Departure station: ");
            printStationText(start, stations, numStations, 1);
            printf(ANSI_COLOR_LIGHT_WHITE "Destination station: ");
            printStationText(end, stations, numStations, 1);
			int foundRoutesCount;
			char** routes = FindRoute(stations, start, end, 20, &foundRoutesCount);
            int bangsueOverwriteRoutes[foundRoutesCount];
            for (int i = 0; i < foundRoutesCount; i++) {
                detectSpecialCases(routes[i]);
            }
			int* prices = calculateRoutesPrice(priceTable, routes, foundRoutesCount);
        
			if (routes != NULL && foundRoutesCount > 0) {
                routesNode routeList[foundRoutesCount];
                int realTotal = 0; //for remove bangsue interchange
                for(int i = 0; i < foundRoutesCount; i++){
                    int duplicatePath = 0;
                    for (int j = 0; j < realTotal; j++) {
                        if (i != j && strcmp(routes[i], routeList[j].visitedRoute) == 0) {
                            duplicatePath = 1;
                            break;
                        }
                    }

                    if (!duplicatePath){
                        routeList[realTotal].price = prices[i];
                        routeList[realTotal].visitedCount = count_string(routes[i], ",") + 1 - countSubString(routes[i], ",INT,") - countSubString(routes[i], ",IN0,");
                        routeList[realTotal].visitedRoute = strdup(routes[i]);
                        realTotal++;
                    }
                    free(routes[i]);
                }
                // die();
                int oldTotal = foundRoutesCount;
                foundRoutesCount = realTotal;
			    
                sortRoutes(routeList, foundRoutesCount);
                clearScreen();
			    DisplayRoutes(stations,routeList,foundRoutesCount,numStations, priceTable, start, end);
                for (int i = 0; i < oldTotal; i++) free(routes[i]);
                // int aea;
                // scanf("%d",&aea);
			    free(routes); // Free the routes array
                free(prices);
			} else {
			    printError("No routes found.");
			}

			enterAnyKey();
			clearScreen();
			firstPanel();
            break;
        }
        case 3: {
        	clearScreen();
            printf(ANSI_COLOR_GOLD "Exiting program...\n" ANSI_RESET_ALL);
            exit(EXIT_SUCCESS);
            break;
        }
        default:
            clearScreen();
            printError("Invalid option");
			firstPanel();
            break;
    }
}
