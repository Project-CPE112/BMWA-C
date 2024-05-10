#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#ifdef _WIN32
    #include <conio.h>
#endif

#include "structure.h"
#include "echo.h"
#include "textDecoration.h"
#include "BFSHelper.h"
#include "textHelper.h"
#include "searchHelper.h"
#include "priceHelper.h"

void delay(int milli_seconds);
void clearScreen(void);
void getCurrentDate(char *dateStr, int size);
void delLastEnteredLine();
void TextShowUpDelay(char Text[], int _delay);
int count_string(char *main_string, char *sub_string);
void enterAnyKey();
void parse_csv_line_graph_station(char *line, Station *station);