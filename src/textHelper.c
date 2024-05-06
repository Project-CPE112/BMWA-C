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
	printf(" %c", BOX_UpperLeft);
	for(int i = 0;i<43;i++){
		printf("%c", BOX_Horizontal);
	}
	printf("%c \n", BOX_UpperRight);
//	printf(" %c                                           %c \n", BOX_Vertical, BOX_Vertical);
	printf(" %c " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "RotFaiFah Application" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE "                     %c \n", BOX_Vertical, BOX_Vertical);
//	printf(" %c                                           %c \n", BOX_Vertical, BOX_Vertical);
	printf(" %c Current Date: " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "%s" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE "                  %c \n", BOX_Vertical, currentDate, BOX_Vertical);
//	printf(" %c                                           %c \n", BOX_Vertical, BOX_Vertical);
	printf(" %c Total Station: " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "%3d" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE " | Total Line: " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "%3d" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE "      %c \n", BOX_Vertical, totalStation, totalLine, BOX_Vertical);
//	printf(" %c                                           %c \n", BOX_Vertical, BOX_Vertical);
	printf(" %c", BOX_LowerLeft);
	for(int i = 0;i<43;i++){
		printf("%c", BOX_Horizontal);
	}
	printf("%c \n", BOX_LowerRight);
	printf(ANSI_RESET_ALL);
}

void printSplitedLine() { printf(ANSI_COLOR_LIGHT_GREEN ANSI_STYLE_STRIKE ANSI_STYLE_BOLD "=================================================\n" ANSI_RESET_ALL); }

void printOption(int opt, char *name) { printf("  %c " ANSI_COLOR_GOLD "[%d]" ANSI_RESET_ALL " %s\n", ARROW_ASCII, opt, name); }

void printEnterChoice(){ printf(ANSI_COLOR_LIGHT_WHITE ANSI_STYLE_BOLD " Enter your choice: " ANSI_RESET_ALL); }

void printMSGLightWhite(char *msg){ printf(ANSI_COLOR_LIGHT_WHITE ANSI_STYLE_BOLD "%s" ANSI_RESET_ALL, msg); }

void printMenu() { printf(ANSI_STYLE_BOLD " Menu:\n" ANSI_RESET_ALL); }

void printError(char *msg) { printf(ANSI_COLOR_LIGHT_RED "%s\n" ANSI_RESET_ALL, msg); }