#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

#include "../include/rotfaifah.h"
#include "../include/textDecoration.h"

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

int getUnderscoreIndex(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '_') return i;
    }
    return -1;
}

char** insertInterchangeMarks(char** routes, int routesCount) {
    char** newRoutes = (char**)malloc(routesCount * sizeof(char*));
    if (newRoutes == NULL) {
        return NULL;
    }

    for (int i = 0; i < routesCount; i++) {
        char result[2000] = "";
        char* dupRoute = strdup(routes[i]);

        if (dupRoute == NULL) {
            return NULL;
        }

        char* sta1 = strtok(dupRoute, ",");
        char* sta2 = strtok(NULL, ",");

        while (sta1 != NULL && sta2 != NULL) {
            int udIndex1 = getUnderscoreIndex(sta1);
            int udIndex2 = getUnderscoreIndex(sta2);
            char* code1 = strdup(sta1);
            char* code2 = strdup(sta2);
            // remove station code after underscore of full code
            memset(code1 + udIndex1, '\0', sizeof(char) * strlen(sta1)-udIndex1);
            memset(code2 + udIndex2, '\0', sizeof(char) * strlen(sta2)-udIndex2);

            if (strcmp(code1, code2) != 0) {
                // interchange detected
                if (strlen(result) > 0) {
                    strcat(result, ",INT,");
                    strcat(result, sta2);
                } else {
                    strcpy(result, sta1);
                    strcat(result, ",INT,");
                    strcat(result, sta2);
                }
            } else {
                // no interchange
                if (strlen(result) > 0) {
                    strcat(result, ",");
                    strcat(result, sta2);
                } else {
                    strcpy(result, sta1);
                    strcat(result, ",");
                    strcat(result, sta2);
                }
            }
            sta1 = sta2;
            sta2 = strtok(NULL, ",");
        }

        newRoutes[i] = strdup(result); // Store result in newRoutes
        free(dupRoute);
    }

    return newRoutes;
}

// Function to find routes between startStation and endStation
char** FindRoute(Station graph[], char* startStation, char* endStation, int routeCount, int* foundRoutesCount) {
    int min = INT_MAX;
    if (!startStation || !endStation) {
        *foundRoutesCount = 0;
        return NULL;
    }

    // Initialize routes array
    char** routes = (char**)malloc(routeCount * sizeof(char*)); //array of string
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

    char* prevStation = NULL;

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
            // if (detectInterchange(currentStation, prevStation)) strcat(updatedPath, ",INT");
            strcat(updatedPath, currentStation);
        } else {
            strcpy(updatedPath, currentStation);
        }
        prevStation = strdup(currentStation);

        // Check if we reached the destination
        if (strcmp(currentStation, endStation) == 0) {
            int numRoute = count_string(updatedPath,",")+1;
            // Find minimum Route
            if(min > numRoute) {
                min = numRoute;
            } // Compare minimum Route if more than 10 don't push it to array
            if((numRoute-min) <= 10){
                routes[routesCount] = strdup(updatedPath);
                routesCount++;
            }
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
    return insertInterchangeMarks(routes, *foundRoutesCount);
}

int countSubString(const char *str, const char *substr){
    int count = 0;
    const char *tmp = str;
    while(tmp = strstr(tmp, substr))
    {
        count++;
        tmp++;
    }
    return count;
}

void detectBangSue(char* route) {
    // Bang Sue Interchange
    if (strstr(route, "MRTBL_BL11,INT,SRTETLR_RW01,INT,SRTETDR_RN01")) {
        char* subIndex = strstr(route, "MRTBL_BL11,INT,SRTETLR_RW01,INT,SRTETDR_RN01");
        memmove(subIndex + 10, subIndex + 27, strlen(subIndex + 27) + 1);
    }
    else if (strstr(route, "MRTBL_BL11,INT,SRTETDR_RN01,INT,SRTETLR_RW01")) {
        char* subIndex = strstr(route, "MRTBL_BL11,INT,SRTETDR_RN01,INT,SRTETLR_RW01");
        memmove(subIndex + 10, subIndex + 27, strlen(subIndex + 27) + 1);
    }
    else if (strstr(route, "SRTETLR_RW01,INT,MRTBL_BL11,INT,SRTETDR_RN01")) {
        char* subIndex = strstr(route, "SRTETLR_RW01,INT,MRTBL_BL11,INT,SRTETDR_RN01");
        memmove(subIndex + 12, subIndex + 27, strlen(subIndex + 27) + 1);
        *(subIndex + 15) = '0';
    }
    else if (strstr(route, "SRTETLR_RW01,INT,SRTETDR_RN01,INT,MRTBL_BL11")) {
        char* subIndex = strstr(route, "SRTETLR_RW01,INT,SRTETDR_RN01,INT,MRTBL_BL11");
        memmove(subIndex + 12, subIndex + 29, strlen(subIndex + 29) + 1);
    }
    else if (strstr(route, "SRTETDR_RN01,INT,MRTBL_BL11,INT,SRTETLR_RW01")) {
        char* subIndex = strstr(route, "SRTETDR_RN01,INT,MRTBL_BL11,INT,SRTETLR_RW01");
        memmove(subIndex + 12, subIndex + 27, strlen(subIndex + 27) + 1);
        *(subIndex + 15) = '0';
    }
    else if (strstr(route, "SRTETDR_RN01,INT,SRTETLR_RW01,INT,MRTBL_BL11")) {
        char* subIndex = strstr(route, "SRTETDR_RN01,INT,SRTETLR_RW01,INT,MRTBL_BL11");
        memmove(subIndex + 12, subIndex + 29, strlen(subIndex + 29) + 1);
    }

    // Siam CEN interchange
    if (strstr(route, "BTSSUK_CEN,INT,BTSSIL_CEN")) {
        char* subIndex = strstr(route, "BTSSUK_CEN,INT,BTSSIL_CEN");
        *(subIndex + 13) = '0';
    }
    else if (strstr(route, "BTSSIL_CEN,INT,BTSSUK_CEN")) {
        char* subIndex = strstr(route, "BTSSIL_CEN,INT,BTSSUK_CEN");
        *(subIndex + 13) = '0';
    }
}


void sortRoutes(routesNode *routeList, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compareRoutesNode(&routeList[j], &routeList[j + 1]) > 0) {
                // Swap routeList[j] and routeList[j+1]
                routesNode temp = routeList[j];
                routeList[j] = routeList[j + 1];
                routeList[j + 1] = temp;
            }
        }
    }
}

// Comparison function for qsort
int compareRoutesNode(routesNode *routeA, routesNode *routeB) {
        // Compare based on price
    if (routeA->price != routeB->price)
        return routeA->price - routeB->price;
    // If prices are equal, compare based on visitedCount
    else if (routeA->visitedCount != routeB->visitedCount)
        return routeA->visitedCount - routeB->visitedCount;
    // If visitedCounts are also equal, compare based on visitedRoute
    else
        return strcmp(routeA->visitedRoute, routeB->visitedRoute);
}