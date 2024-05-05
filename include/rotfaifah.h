#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include "structure.h"
#include "echo.h"
#include "textDecoration.h"
#include "BFSHelper.h"

void delay(int milli_seconds);
void clearScreen(void);
void getCurrentDate();
void delLastEnteredLine();
void TextShowUpDelay(char Text[], int _delay);
void printHeader(int totalLine, int totalStation);
void printSplitedLine();
void printOption(int opt, char *name);
void printEnterChoice();
void printMSGLightWhite(char *msg);
void printMenu();
void printError(char *msg);
int count_string(char *main_string, char *sub_string);
void enterAnyKey();
void parse_csv_line_graph_station(char *line, Station *station);