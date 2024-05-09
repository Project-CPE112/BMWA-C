#include "../include/rotfaifah.h"

void findStationByName(Station *station, char *code, int numStations, char *title){
    clearScreen();
    int selector = 0;
    int end = 0;
    int isESC = 0;
    printf(ANSI_COLOR_GOLD "%s ", title);
    char sname[50];
    printSplitedLine();
    printf("Find station: ");
    scanf(" %[^\n]", sname);
    int foundStation[numStations];
    int foundStationCnt = -1;
    char lowersname[50];
    strcpy(lowersname, sname);
    strlwr(lowersname);
    for (int i = 0; i < numStations; i++) {
        if (strstr(station[i].nameLowercase, lowersname) != NULL || strstr(station[i].shortCodeLowercase, lowersname) != NULL) {
            if(foundStationCnt == -1) foundStationCnt = 0;
            foundStation[foundStationCnt] = i;
            foundStationCnt++;
        }else{
            // Debugging search
            // printf("[%s | %s][%s | %s] Find with %s\n", station[i].name, station[i].shortCode, station[i].nameLowercase, station[i].shortCodeLowercase, lowersname);
        }
    }
    clearScreen();
    if(foundStationCnt == -1){
        printError("Station not found");
        int optionTry = 0;
        while(optionTry == 0){
            printSplitedLine();
            printMenu();
            printOption(1, "Try again");
            printOption(2, "Go back!");
            printEnterChoice();
            int scanfOption = scanf("%d", &optionTry);

            if(scanfOption != 1){
                clearScreen();
                while (getchar() != '\n');
                printError("Invalid option");
            }else{
                switch (optionTry) {
                    case 1:
                        clearScreen();
                        findStationByName(station, code, numStations, title);
                        break;
                    case 2:
                        clearScreen();
                        break;
                    default:
                        optionTry = 0;
                        break;
                }
            }
        }
        if(optionTry == 2) return;
    }else{
        int startPoint = 0;
        int endPoint = 10;
        if(foundStationCnt < 10) endPoint = foundStationCnt;
        while (!end) {
            printf(ANSI_COLOR_GOLD "%s", title);
            printf("STARTPOINT: %d, ENDPOINT: %d\n", startPoint, endPoint);
            printf(ANSI_COLOR_LIGHT_WHITE "Find station: " ANSI_COLOR_GOLD "%s\n", sname);
            printf(ANSI_COLOR_LIGHT_WHITE "Found total: " ANSI_COLOR_GOLD "%d\n" ANSI_RESET_ALL,foundStationCnt);
            printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " [%c] " ANSI_COLOR_LIGHT_WHITE "To go up | " ANSI_COLOR_GOLD "[%c] " ANSI_COLOR_LIGHT_WHITE "To go down\n", 24, 25);
            printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " Enter " ANSI_COLOR_LIGHT_WHITE "To choose\n");
            printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " ESC " ANSI_COLOR_LIGHT_WHITE "To go back\n");
            printSplitedLine();
            for(int i = startPoint; i < endPoint;i++){
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
            printSplitedLine();
            int trueCodeSkip = 0; //check press enter or up arrow or down arrow
            int ch;
            while(trueCodeSkip == 0){
                ch = getch();
                // Handle arrow keys
                switch (ch) {
                    case 72: // Up arrow
                        if(selector != 0) selector--;
                        trueCodeSkip = 1;
                        if(selector == startPoint && startPoint != 0){
                            startPoint--;
                            endPoint--;
                        }
                        clearScreen();
                        break;
                    case 80: // Down arrow
                        if(selector != foundStationCnt - 1) selector++;
                        trueCodeSkip = 1;
                        if(selector == endPoint && endPoint != foundStationCnt){
                            endPoint++;
                            startPoint++;
                        }
                        clearScreen();
                        break;
                    case 13: // Enter key
                        end = 1;
                        trueCodeSkip = 1;
                        break;
                    case 27 : // ESC key
                        end = 1;
                        trueCodeSkip = 1;
                        isESC = 1;
                        break;
                    default:
                        break;
                }
            }
        }
        if(isESC == 0){
            strcpy(code, station[foundStation[selector]].fullCode);
            clearScreen();
        }else{
            clearScreen();
            findStationByName(station, code, numStations, title);
        }
    }
    return;
}