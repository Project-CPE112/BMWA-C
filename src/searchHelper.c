#include "../include/rotfaifah.h"

void findStationByName(Station *station, char *code, int numStations, char *title){
    clearScreen();
    int selector = 0;
    int end = 0;
    int searched = 0;
    printf(ANSI_COLOR_GOLD "%s ", title);
    char sname[50];
    printSplitedLine();
    printf("Find station: ");
    scanf(" %[^\n]", sname);
    int foundStation[numStations];
    int foundStationCnt = -1;
    for (int i = 0; i < numStations; i++) {
        if (strstr(station[i].name, sname) != NULL || strstr(station[i].shortCode, sname) != NULL) {
            if(foundStationCnt == -1) foundStationCnt = 0;
            foundStation[foundStationCnt] = i;
            foundStationCnt++;
        }
    }
    clearScreen();
    while (!end) {
        if(searched == 0){
            searched = 1;
        }
        printf(ANSI_COLOR_GOLD "%s ", title);
        printf(ANSI_COLOR_LIGHT_WHITE "Find station: " ANSI_COLOR_GOLD "%s\n", sname);
        printf(ANSI_COLOR_LIGHT_WHITE "Found total: " ANSI_COLOR_GOLD "%d\n",foundStationCnt);
        printSplitedLine();
        for(int i = 0; i < foundStationCnt;i++){
            int asciiArrow = 0;
            if(i == selector) asciiArrow = ARROW_ASCII;
            if(i == selector)
                printf(ANSI_COLOR_GOLD "%c " ANSI_STYLE_BOLD ANSI_COLOR_LIGHT_CYAN " [%s] " ANSI_COLOR_LIGHT_YELLOW "%s\n" ANSI_RESET_ALL,
                    asciiArrow,
                    station[foundStation[i]].shortCode, station[foundStation[i]].name);
            else
                printf(ANSI_COLOR_GOLD "%c " ANSI_COLOR_LIGHT_CYAN " [%s] " ANSI_COLOR_LIGHT_YELLOW "%s\n" ANSI_RESET_ALL,
                    asciiArrow,
                    station[foundStation[i]].shortCode, station[foundStation[i]].name);
        }
        int trueCodeSkip = 0; //check press enter or up arrow or down arrow
        int ch;
        while(trueCodeSkip == 0){
            ch = getch();
            // Handle arrow keys
            switch (ch) {
                case 72: // Up arrow
                    if(selector != 0) selector--;
                    trueCodeSkip = 1;
                    clearScreen();
                    break;
                case 80: // Down arrow
                    if(selector != foundStationCnt - 1) selector++;
                    trueCodeSkip = 1;
                    clearScreen();
                    break;
                case 13: // Enter key
                    end = 1;
                    trueCodeSkip = 1;
                    break;
                default:
                    break;
            }
        }
    }
    strcpy(code, station[foundStation[selector]].fullCode);
    clearScreen();
    return;
}