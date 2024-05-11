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
	printf(" %s " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "RotFaiFah Application" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE "                     %s \n", BOX_Vertical, BOX_Vertical);
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
            printf(ANSI_COLOR_LIGHT_WHITE "Station Name: " ANSI_COLOR_LIGHT_CYAN "[%s]" ANSI_STYLE_BOLD ANSI_COLOR_GOLD " %s\n" ANSI_RESET_ALL, stations[i].shortCode, stations[i].name);
            
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
                printf(ANSI_COLOR_LIGHT_WHITE " - " ANSI_COLOR_LIGHT_CYAN "[%s]" ANSI_COLOR_LIGHT_WHITE " %s" ANSI_RESET_ALL " (" ANSI_COLOR_LIGHT_YELLOW "Time: %d " ANSI_COLOR_LIGHT_CYAN "Platform: %s" ANSI_RESET_ALL ")\n", 
                CodeToShortCode(stations[i].connections[j].sta, stations, numStations),
                CodeToName(stations[i].connections[j].sta, stations, numStations),
                stations[i].connections[j].time, stations[i].connections[j].platform, stations[i].connections[j].staID);
            }
            printSplitedLineColoring(73, 73, 73);
            if(stations[i].intCount != 0){
                printf(ANSI_COLOR_LIGHT_WHITE "Interchanges ("ANSI_STYLE_BOLD ANSI_COLOR_GOLD "%d" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE"): \n" ANSI_RESET_ALL, stations[i].intCount);
                for (int j = 0; j < stations[i].intCount; j++) {
                    printf(ANSI_COLOR_LIGHT_WHITE " - " ANSI_COLOR_LIGHT_CYAN "[%s]" ANSI_COLOR_LIGHT_WHITE " %s" ANSI_RESET_ALL " (" ANSI_COLOR_LIGHT_YELLOW "Time: %d" ANSI_RESET_ALL")\n", 
                    CodeToShortCode(stations[i].interchanges[j].sta, stations, numStations),
                    CodeToName(stations[i].interchanges[j].sta, stations, numStations),
                     stations[i].interchanges[j].time, stations[i].interchanges[j].staID);
                }
                printSplitedLineColoring(73, 73, 73);
            }
            return;
        }
    }
    printError("Station not found!");
}