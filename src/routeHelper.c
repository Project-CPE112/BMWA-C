#include "../include/rotfaifah.h"

void Displayroutes(routesNode *routeList,int Countroutes){
    int end = 0;
    int startpoint = 0;
    int selector = 0;
    int endpoint = 10;
    if(Countroutes < 10) endpoint = Countroutes;
     printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " [%c] " ANSI_COLOR_LIGHT_WHITE "To go up | " ANSI_COLOR_GOLD "[%c] " ANSI_COLOR_LIGHT_WHITE "To go down\n", 24, 25);
            printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " Enter " ANSI_COLOR_LIGHT_WHITE "To choose\n");
            printf(ANSI_COLOR_LIGHT_WHITE "Press" ANSI_COLOR_GOLD " ESC " ANSI_COLOR_LIGHT_WHITE "To go back\n");
    
    while(!end) {
        printSplitedLine();
        for(int i = startpoint;i< endpoint;i++){
            int asciiArrow = 0;
             if(i == selector) asciiArrow = ARROW_ASCII;
             if(i == selector)
                    printf(ANSI_COLOR_GOLD "%c " "[%d] " ANSI_STYLE_BOLD ANSI_COLOR_LIGHT_CYAN "[Total: %d | Price: %d]\n\n",asciiArrow,i,
                    routeList[i].visitedCount, routeList[i].price );
            else
                    printf(ANSI_COLOR_GOLD "%c " "[%d] " ANSI_STYLE_BOLD ANSI_COLOR_LIGHT_CYAN "[Total: %d | Price: %d]\n\n",asciiArrow,i, 
                    routeList[i].visitedCount, routeList[i].price );
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
                        if(selector == startpoint && startpoint != 0){
                            startpoint--;
                            endpoint--;
                        }
                        clearScreen();
                        break;
                    case 80: // Down arrow
                        if(selector != Countroutes - 1) selector++;
                        trueCodeSkip = 1;
                        if(selector == endpoint && endpoint != Countroutes){
                            endpoint++;
                            startpoint++;
                        }
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
            if(end == 1)
                Displayselectedroutes(routeList[selector].visitedRoute);

    }
}

void Displayselectedroutes(char *routes){
    char *token = strtok(routes,",");
    while(token != NULL){
        printf("%s\n->\n",token);
        token = strtok(NULL,",");
    }
}