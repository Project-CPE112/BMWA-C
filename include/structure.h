#define MAX_CONNECTIONS 300
#define MAX_INTERCHANGES 300
#define MAX_STATIONS 400
#define MAX_CONNECT 600
#define MAX_ROUTES 400

typedef struct {
	int staID;
    char name[50];
    char nameLowercase[50];
    char shortCode[10];
    char shortCodeLowercase[10];
    char fullCode[50];
    char connectionWith[150];
    char connectionWith2[150];
	int conCount;
    struct {
        char sta[70];
        int time;
        int staID;
        char platform[10];
    } connections[MAX_CONNECTIONS];
    int intCount;
    struct {
        char sta[70];
        int time;
        int staID;
    } interchanges[MAX_INTERCHANGES];
    int connectAllCount;
    struct{
    	char sta[70];
    	int time;
    	int staID;
    	char platform[10];
    	int type;
	} connectAll[MAX_CONNECT];
} Station;

typedef struct QueueNode {
    char* station;
    char* path;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

typedef struct routesNode{
	int visitedCount;
	int price;
	char *visitedRoute;
} routesNode;
