#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

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
