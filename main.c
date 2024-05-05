#include "include/echo.h"
#include "include/structure.h"
#include "include/textDecoration.h"
#include "include/rotfaifah.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
//Function prototypes

void firstPanel();


int numStations = 0;
Station stations[MAX_STATIONS];

// Function to display station information
void displayStationInfo(char *code) {
    for (int i = 0; i < numStations; i++) {
        if (strcmp(stations[i].fullCode, code) == 0) {
            printf("Station Name: %s\n", stations[i].name);
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

// Function to parse a CSV line and fill the Station struct
void parse_csv_line(char *line, Station *station) {
    const char *delim = ",";
    char *token = strtok(line, delim);

    int col = 0;
    int cCount = 0, iCount = 0;
    while (token != NULL) {
        switch (col) {
			case 0:
				station->staID = atoi(token);
				break;	
            case 1:
                strcpy(station->name, token);
                break;
            case 2:
                strcpy(station->shortCode, token);
                break;
            case 3:
                strcpy(station->fullCode, token);
                break;
            case 4:
                strcpy(station->connectionWith, token);
                break;
            case 5:
                strcpy(station->connectionWith2, token);
                break;
            case 6:
                station->conCount = atoi(token);
                cCount = atoi(token);
                break;
            case 7:
            case 11:
            case 15:
                station->connections[(col - 7)/4].staID = atoi(token);
                break;
            case 8:
            case 12:
            case 16:
                strcpy(station->connections[(col - 8)/4].sta, token);
                break;
            case 9:
            case 13:
            case 17:
                station->connections[(col - 9)/4].time = atoi(token);
                break;
            case 10:
            case 14:
            case 18:
                strcpy(station->connections[(col - 10)/4].platform, token);
                break;
            case 19:
                station->intCount = atoi(token);
                iCount = atoi(token);
                break;
            case 20:
            case 23:
            case 26:
            	station->interchanges[(col - 20)/3].staID = atoi(token);
                break;
            case 21:
            case 24:
            case 27:
                strcpy(station->interchanges[(col-21)/3].sta, token);
                break;
            case 22:
            case 25:
            case 28:
                station->interchanges[(col-22)/3].time = atoi(token);
                break;
            default:
                break;
        }
        col++;
        token = strtok(NULL, delim);
    }
    int unionTotal = 0;
    for(int i = 0;i < cCount;i++){
    	strcpy(station->connectAll[unionTotal].sta, station->connections[i].sta);
    	strcpy(station->connectAll[unionTotal].platform, station->connections[i].platform);
    	station->connectAll[unionTotal].time = station->connections[i].time;
    	station->connectAll[unionTotal].staID = station->connections[i].staID;
		station->connectAll[unionTotal].type = 1;
    	unionTotal++;
	}
	for(int i = 0; i < iCount;i++){
//		printf("Adding Interchange #%d of: %s %s\n", i, station->name, station->interchanges[i].sta);
		strcpy(station->connectAll[unionTotal].sta, station->interchanges[i].sta);
		station->connectAll[unionTotal].time = station->interchanges[i].time;
		char *platform = "999UKN";
		strcpy(station->connectAll[unionTotal].platform, platform);
		station->connectAll[unionTotal].staID = station->interchanges[i].staID;
		station->connectAll[unionTotal].type = 2;
		unionTotal++;
	}
	station->connectAllCount = unionTotal;
}

// Function to read station data from CSV
void readStationsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    char line[1024];
    char buffer[1024];
    int count = 0;
    fgets(buffer, 1024, file); //Skip first line
    while (fgets(line, 1024, file)) {
        Station station;
        parse_csv_line(line, &station);
        // Here you can store the parsed station information in an array or perform other operations
        // For demonstration, let's just print the station name
        // printf("Station Name: %s\n", station.name);
        stations[numStations++] = station;
        count++;
    }
    fclose(file);
}

// Function to find the index of a station in the graph
int findStationIndex(Station graph[], char* code) {
    for (int i = 0; i < MAX_STATIONS; i++) {
        if (strcmp(graph[i].fullCode, code) == 0) {
            return i; // Return the index if found
        }
    }
    return -1; // Return -1 if not found
}

// Function to create a new queue node
QueueNode* createQueueNode(char* station, char* path) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode != NULL) {
        newNode->station = strdup(station);
        newNode->path = strdup(path);
        newNode->next = NULL;
    }
    return newNode;
}

// Function to initialize a queue
Queue* initializeQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue != NULL) {
        queue->front = NULL;
        queue->rear = NULL;
    }
    return queue;
}

// Function to enqueue a station and path into the queue
void enqueue(Queue* queue, char* station, char* path) {
    QueueNode* newNode = createQueueNode(station, path);
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue a station and path from the queue
QueueNode* dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    return temp;
}

// Function to free memory allocated for a queue node
void freeQueueNode(QueueNode* node) {
    if (node != NULL) {
        free(node->station);
        free(node->path);
        free(node);
    }
}

// Function to free memory allocated for a queue
void freeQueue(Queue* queue) {
    if (queue != NULL) {
        while (queue->front != NULL) {
            QueueNode* temp = dequeue(queue);
            freeQueueNode(temp);
        }
        free(queue);
    }
}

// Function to find routes between startStation and endStation
char** FindRoute(Station graph[], char* startStation, char* endStation, int routeCount, int* foundRoutesCount) {
    if (!startStation || !endStation) {
        *foundRoutesCount = 0;
        return NULL;
    }

    // Initialize routes array
    char** routes = (char**)malloc(routeCount * sizeof(char*));
    if (routes == NULL) {
        *foundRoutesCount = 0;
        return NULL;
    }

    int routesCount = 0;

    // Initialize queue
    Queue* queue = initializeQueue();
    if (queue == NULL) {
        *foundRoutesCount = 0;
        free(routes);
        return NULL;
    }

    // Enqueue the start station
    enqueue(queue, startStation, "");

    // BFS loop
    while (queue->front != NULL && routesCount < routeCount) {
        // Dequeue a station and path
        QueueNode* node = dequeue(queue);
        char* currentStation = node->station;
        char* path = node->path;

        // Find the index of the current station in the graph
        int stationIndex = findStationIndex(graph, currentStation);
        if (stationIndex == -1) {
            continue; // Skip if station not found
        }

        // Update path
        char updatedPath[2000];
        if (strlen(path) > 0) {
            strcpy(updatedPath, path);
            strcat(updatedPath, ",");
            strcat(updatedPath, currentStation);
        } else {
            strcpy(updatedPath, currentStation);
        }

        // Check if we reached the destination
        if (strcmp(currentStation, endStation) == 0) {
            routes[routesCount] = strdup(updatedPath);
            routesCount++;
        }

        // Enqueue all connected stations
        for (int i = 0; i < graph[stationIndex].connectAllCount; i++) {
            char* nextStation = graph[stationIndex].connectAll[i].sta;
            if (!strstr(updatedPath, nextStation)) { // Avoid revisiting stations
                enqueue(queue, nextStation, updatedPath);
            }
        }

        freeQueueNode(node);
    }

    // Free memory allocated for the queue
    freeQueue(queue);

    // Set the count of found routes
    *foundRoutesCount = routesCount;

    // Return the routes array
    return routes;
}

int main() {
    readStationsFromFile("metro_graph.csv");
    int option = 0;
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
    int optionScan = scanf("%d", &option);
    if(optionScan != 1){
    	clearScreen();
	   	while (getchar() != '\n');
		printError("Invalid option");
        firstPanel();
    }
    char ch;
    switch (option) {
        case 1: {
        	clearScreen();
        	printHeader(10, numStations);
    		printSplitedLine();
    		printf(ANSI_COLOR_GOLD ANSI_STYLE_BOLD " Display Station Info\n" ANSI_RESET_ALL);
            char code[50];
            printf("Enter station full code: ");
            scanf("%s", code);
            displayStationInfo(code);
            enterAnyKey();
			clearScreen();
			firstPanel();
			break;
		}
        case 2: {
            clearScreen();
			char start[50], end[50];
			printf("Enter start station: ");
			scanf("%s", start);
			printf("Enter end station: ");
			scanf("%s", end);
			
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
            printf(ANSI_COLOR_LIGHT_CYAN "Exiting program...\n" ANSI_COLOR_LIGHT_YELLOW);
            exit(EXIT_SUCCESS);
            break;
        }
        default:
            printError("Invalid option");
            break;
    }
}

