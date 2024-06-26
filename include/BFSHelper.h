int findStationIndex(Station graph[], char* code);
QueueNode* createQueueNode(char* station, char* path);
Queue* initializeQueue();
void enqueue(Queue* queue, char* station, char* path);
QueueNode* dequeue(Queue* queue);
void freeQueueNode(QueueNode* node);
void freeQueue(Queue* queue);
char** FindRoute(Station graph[], char* startStation, char* endStation, int routeCount, int* foundRoutesCount);
int getUnderscoreIndex(char* str);
char** insertInterchangeMarks(char** routes, int routesCount);
int countSubString(const char *str, const char *substr);
void detectSpecialCases(char* route);

// Comparison function for qsort
void sortRoutes(routesNode *routeList, int size);
int compareRoutesNode(routesNode *routeA, routesNode *routeB);
char *replace_substring(const char *str, const char *old_sub, const char *new_sub);
void replaceSubstring(char *str, const char *search, const char *replace);