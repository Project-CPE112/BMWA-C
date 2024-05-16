#include <stdio.h>
#include <stdlib.h>
// Helper function to generate the ANSI escape sequence
char* generate_ansi_rgb_color(int r, int g, int b) {
    // Allocate memory for the escape sequence string
    char* escape_sequence = (char*)malloc(20 * sizeof(char));
    if (escape_sequence != NULL) {
        // Format the escape sequence into the allocated memory
        snprintf(escape_sequence, 20, "\x1b[38;2;%d;%d;%dm", r, g, b);
    }
    return escape_sequence;
}
char* generate_ansi_rgb_bg_color(int r, int g, int b) {
    char* escape_sequence = (char*)malloc(20 * sizeof(char));
    if (escape_sequence != NULL) {
        // Format the escape sequence into the allocated memory
        snprintf(escape_sequence, 20, "\x1b[48;2;%d;%d;%dm", r, g, b);
    }
    return escape_sequence;
}