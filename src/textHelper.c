#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/rotfaifah.h"

void printHeader(int totalLine, int totalStation){
	int MAX_DATE_LENGTH = 12;
	char currentDate[MAX_DATE_LENGTH];
    getCurrentDate(currentDate, sizeof(currentDate));
	char UpperLeft, UpperRight;
	char LowerLeft, LowerRight;
	char Vertical, Horizontal;
    //set to ASCII Character 218, 191, 192, 217, 179, 196 to create the box for header

	printf(ANSI_COLOR_LIGHT_WHITE);
	printf(" %s", BOX_UpperLeft);
	for(int i = 0;i<43;i++){
		printf("%s", BOX_Horizontal);
	}
	printf("%s \n", BOX_UpperRight);
//	printf(" %s                                           %s \n", BOX_Vertical, BOX_Vertical);
	printf(" %s " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "MOD METRO Application" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE "                     %s \n", BOX_Vertical, BOX_Vertical);
//	printf(" %s                                           %s \n", BOX_Vertical, BOX_Vertical);
	printf(" %s Current Date: " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "%s" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE "                  %s \n", BOX_Vertical, currentDate, BOX_Vertical);
//	printf(" %s                                           %s \n", BOX_Vertical, BOX_Vertical);
	printf(" %s Total Station: " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "%3d" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE " | Total Line: " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "%3d" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE "      %s \n", BOX_Vertical, totalStation, totalLine, BOX_Vertical);
//	printf(" %s                                           %s \n", BOX_Vertical, BOX_Vertical);
	printf(" %s", BOX_LowerLeft);
	for(int i = 0;i<43;i++){
		printf("%s", BOX_Horizontal);
	}
	printf("%s \n", BOX_LowerRight);
	printf(ANSI_RESET_ALL);
}

void printSplitedLine() { printf(ANSI_COLOR_LIGHT_GREEN ANSI_STYLE_STRIKE ANSI_STYLE_BOLD "=================================================\n" ANSI_RESET_ALL); }

void printSplitedLineColoring(int r, int g, int b) { 
	printf("%s" ANSI_STYLE_STRIKE ANSI_STYLE_BOLD "=================================================\n" ANSI_RESET_ALL, ANSI_RGB_COLOR2(r,g,b)); 
}

void printOption(int opt, char *name) { printf("  %s " ANSI_COLOR_GOLD "[%d]" ANSI_RESET_ALL " %s\n", ARROW_UTF8, opt, name); }

void printEnterChoice(){ printf(ANSI_COLOR_LIGHT_WHITE ANSI_STYLE_BOLD " Enter your choice: " ANSI_RESET_ALL); }

void printMSGLightWhite(char *msg){ printf(ANSI_COLOR_LIGHT_WHITE ANSI_STYLE_BOLD "%s" ANSI_RESET_ALL, msg); }

void printMenu() { printf(ANSI_STYLE_BOLD " Menu:\n" ANSI_RESET_ALL); }

void printError(char *msg) { printf(ANSI_COLOR_LIGHT_RED "%s\n" ANSI_RESET_ALL, msg); }

// Function to display station information
void printStationInfo(char *code, Station *stations, int numStations) {
    for (int i = 0; i < numStations; i++) {
        if (strcmp(stations[i].fullCode, code) == 0) {
            printSplitedLineColoring(73, 73, 73);
            printf(ANSI_COLOR_LIGHT_WHITE "Station Name: ");
            printStationText(stations[i].fullCode,stations,numStations,1);
            printSplitedLineColoring(73, 73, 73);
            if(!(strcmp(stations[i].connectionWith, "BLANK") == 0)){
	            printf(ANSI_COLOR_LIGHT_MAGENTA "Connection With: " ANSI_STYLE_BOLD ANSI_COLOR_LIGHT_RED "%s\n" ANSI_RESET_ALL, stations[i].connectionWith);
                if((strcmp(stations[i].connectionWith2, "BLANK") == 0))
                    printSplitedLineColoring(73, 73, 73);
            }
            if(!(strcmp(stations[i].connectionWith2, "BLANK") == 0)){
            	printf(ANSI_COLOR_LIGHT_MAGENTA "Connection With: " ANSI_STYLE_BOLD ANSI_COLOR_LIGHT_RED "%s\n" ANSI_RESET_ALL, stations[i].connectionWith2);
                printSplitedLineColoring(73, 73, 73);
            }
            printf(ANSI_COLOR_LIGHT_WHITE "Connections ("ANSI_STYLE_BOLD ANSI_COLOR_GOLD "%d" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE"): \n" ANSI_RESET_ALL, stations[i].conCount);
            for (int j = 0; j < stations[i].conCount; j++) {
                printf(ANSI_COLOR_LIGHT_WHITE " - ");
                printStationText(stations[i].connections[j].sta,stations,numStations,1);
                printf(ANSI_COLOR_LIGHT_WHITE "     (" ANSI_COLOR_LIGHT_YELLOW "Time: %d" ANSI_RESET_ALL ", " ANSI_COLOR_LIGHT_CYAN "Platform: %s" ANSI_COLOR_LIGHT_WHITE ")\n" ANSI_RESET_ALL, 
                stations[i].connections[j].time, stations[i].connections[j].platform);
            }
            printSplitedLineColoring(73, 73, 73);
            if(stations[i].intCount != 0){
                printf(ANSI_COLOR_LIGHT_WHITE "Interchanges ("ANSI_STYLE_BOLD ANSI_COLOR_GOLD "%d" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE"): \n" ANSI_RESET_ALL, stations[i].intCount);
                for (int j = 0; j < stations[i].intCount; j++) {
                    printf(ANSI_COLOR_LIGHT_WHITE " - ");
                    printStationText(stations[i].interchanges[j].sta,stations,numStations,1);
                    printf(ANSI_COLOR_LIGHT_WHITE "     (" ANSI_COLOR_LIGHT_YELLOW "Time: %d" ANSI_COLOR_LIGHT_WHITE")\n" ANSI_RESET_ALL, stations[i].interchanges[j].time);
                }
                printSplitedLineColoring(73, 73, 73);
            }
            return;
        }
    }
    printError("Station not found!");
}

void printStationText(char *code, Station *stations, int numStations, int needBold){
    char lineName[][10] = {"BTSSUK","MRTBL","BTSSIL","MRTPL","ARL","BTSGL","SRTETDR","SRTETLR","MRTYL","MRTPK"};
    int rColor[10] = {113,49,49,104,232,204,240,217,230,226};
    int gColor[10] = {176,96,93,50,86,153,24,106,230,163};
    int bColor[10] = {71,158,54,121,88,51,24,106,23,193};
    int print = 0;
    for(int i=0;i<=9;i++){
        if(print == 1) break;
        if(strstr(code,lineName[i]) != NULL){
            print = 1;
            if(needBold == 1) printf(ANSI_STYLE_BOLD);
            printf(ANSI_RGB_COLOR2(rColor[i],gColor[i],bColor[i]));
            if(needBold == 1)
                printf("[%s]" ANSI_RESET_ALL ANSI_STYLE_BOLD ANSI_COLOR_LIGHT_WHITE " %s\n" ANSI_RESET_ALL, CodeToShortCode(code,stations,numStations), CodeToName(code,stations,numStations));
            else
                printf("[%s]" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE " %s\n" ANSI_RESET_ALL, CodeToShortCode(code,stations,numStations), CodeToName(code,stations,numStations));

        }
    }
}