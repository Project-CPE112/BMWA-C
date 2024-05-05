int findStationIndex(Station graph[], char* code);
QueueNode* createQueueNode(char* station, char* path);
Queue* initializeQueue();
void enqueue(Queue* queue, char* station, char* path);
QueueNode* dequeue(Queue* queue);
void freeQueueNode(QueueNode* node);
void freeQueue(Queue* queue);
char** FindRoute(Station graph[], char* startStation, char* endStation, int routeCount, int* foundRoutesCount);