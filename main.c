#include "include/rotfaifah.h"

//Function prototypes
void firstPanel();

int numStations = 0;

Station stations[MAX_STATIONS];

// Function to display station information
void displayStationInfo(char *code) {
    for (int i = 0; i < numStations; i++) {
        if (strcmp(stations[i].fullCode, code) == 0) {
            printf("Station Name: %s\n", stations[i].name);
            printf("Station Name Lowercase: %s\n", stations[i].nameLowercase);
            printf("Short Code: %s\n", stations[i].shortCode);
            printf("Full Code: %s\n", stations[i].fullCode);
            if(!(strcmp(stations[i].connectionWith, "BLANK") == 0))
	            printf("Connection With: %s\n", stations[i].connectionWith);
            if(!(strcmp(stations[i].connectionWith2, "BLANK") == 0))
            	printf("Connection With: %s\n", stations[i].connectionWith2);
            printf("Connections (%d): \n", stations[i].conCount);
            for (int j = 0; j < stations[i].conCount; j++) {
                printf(" - %s (Time: %d, Platform: %s, ID: %d)\n", stations[i].connections[j].sta,
                        stations[i].connections[j].time, stations[i].connections[j].platform, stations[i].connections[j].staID);
            }
            printf("Interchanges (%d):\n", stations[i].intCount);
            for (int j = 0; j < stations[i].intCount; j++) {
                printf(" - %s (Time: %d, ID: %d)\n", stations[i].interchanges[j].sta, stations[i].interchanges[j].time, stations[i].interchanges[j].staID);
            }
            printf("All Connected Stations (%d):\n", stations[i].connectAllCount);
            for(int j = 0; j < stations[i].connectAllCount; j++){
            	if(stations[i].connectAll[j].type == 1){
            		printf(" - [C #%d] %s (Time: %d, Platform: %s, ID: %d)\n", j, stations[i].connectAll[j].sta, stations[i].connectAll[j].time, stations[i].connectAll[j].platform, stations[i].connectAll[j].staID);
				}else if(stations[i].connectAll[j].type == 2){
					printf(" - [I #%d] %s (Time: %d, Platform: Walking Connection, ID: %d)\n", j, stations[i].connectAll[j].sta, stations[i].connectAll[j].time, stations[i].connectAll[j].staID);
				}else{
					printf("Invalid Format\n");
				}
			}
            return;
        }
    }
    printError("Station not found!");
}

// Function to read station data from CSV
void readStationsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf(ANSI_COLOR_LIGHT_RED "Error: Could not open file %s\n" ANSI_RESET_ALL, filename);
        exit(1);
    }
    char line[1024];
    char buffer[1024];
    int count = 0;
    fgets(buffer, 1024, file); //Skip first line
    while (fgets(line, 1024, file)) {
        Station station;
        parse_csv_line_graph_station(line, &station);
        stations[numStations++] = station;
        count++;
    }
    fclose(file);
}

int main() {
    clearScreen();
    readStationsFromFile("metro_graph.csv");
    firstPanel();
    return 0;
}

char *CodeToName(char *code, Station *stations, int numStations) {
    for (int i = 0; i < numStations; i++) {
        if (strcmp(stations[i].fullCode, code) == 0) {
            return stations[i].name;
        }
    }
    return NULL; // Return NULL if code not found
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
            displayStationInfo(code);
            enterAnyKey();
			clearScreen();
			firstPanel();
			break;
		}
        case 2: {
            clearScreen();
			char start[50], end[50];

            // start changing fucking code 
            printOption(1, "Insert Departure First : ");
            printOption(2, "Insert Destination First : ");

            printEnterChoice();

            int choice;
            int optionScan = scanf("%d", &choice);
            if(optionScan != 1){
                clearScreen();
                while (getchar() != '\n');
                printError("Invalid option");
                firstPanel();
            }
            char show[50];
            char des[50], dep[50];

            switch (choice) {
                case 1: {
                    printf("Enter departure station: ");
                    findStationByName(stations, start, numStations,"Find Departure station\n", NULL);
                    
                    strcpy(dep,CodeToName(start, stations, numStations));

                    snprintf(show, sizeof(show), "Departure station : %s\n", dep);

                    findStationByName(stations, end, numStations,"Find Destination station\n",show);

                    strcpy(des,CodeToName(end, stations,numStations));


                    printf("Departure station : %s\n", dep);
			        printf("Destination station : %s\n", des);
                    break;
                }
                case 2: {
                    printf("Enter destination station: ");
                    findStationByName(stations, end, numStations,"Find Destination station\n", NULL);
                    strcpy(des,CodeToName(end, stations,numStations));
                    snprintf(show, sizeof(show), "Departure station : %s\n", des);


                    findStationByName(stations, start, numStations, "Find Departure station\n", show);

                    strcpy(des,CodeToName(end, stations,numStations));

                    printf("Destination station : %s\n", des);
                    printf("Departure station : %s\n", dep);
                    break;
                }
                break;
            }
			
			int foundRoutesCount;
			char** routes = FindRoute(stations, start, end, 20, &foundRoutesCount);
			
			if (routes != NULL && foundRoutesCount > 0) {
			    printf("Possible routes:\n");
			    for (int i = 0; i < foundRoutesCount; i++) {
			        printf("[Total: %d] %s\n", count_string(routes[i],",") + 1, routes[i]);
			        free(routes[i]); // Free each individual route
			    }
			    free(routes); // Free the routes array
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