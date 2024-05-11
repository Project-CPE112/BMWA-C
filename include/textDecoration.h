
#define ANSI_RESET_ALL                "\x1b[0m"

#define ANSI_COLOR_BLACK              "\x1b[30m"
#define ANSI_COLOR_RED                "\x1b[31m"
#define ANSI_COLOR_GREEN              "\x1b[32m"
#define ANSI_COLOR_YELLOW             "\x1b[33m"
#define ANSI_COLOR_BLUE               "\x1b[34m"
#define ANSI_COLOR_MAGENTA            "\x1b[35m"
#define ANSI_COLOR_CYAN               "\x1b[36m"
#define ANSI_COLOR_WHITE              "\x1b[37m"
#define ANSI_COLOR_PINK               "\x1b[95m"

#define ANSI_COLOR_LIGHT_BLACK        "\x1b[90m"
#define ANSI_COLOR_LIGHT_RED          "\x1b[91m"
#define ANSI_COLOR_LIGHT_GREEN        "\x1b[92m"
#define ANSI_COLOR_LIGHT_YELLOW       "\x1b[93m"
#define ANSI_COLOR_LIGHT_BLUE         "\x1b[94m"
#define ANSI_COLOR_LIGHT_MAGENTA      "\x1b[95m"
#define ANSI_COLOR_LIGHT_CYAN         "\x1b[96m"
#define ANSI_COLOR_LIGHT_WHITE        "\x1b[97m"

#define ANSI_RGB_COLOR(r, g, b)       "\x1b[38;2;" #r ";" #g ";" #b "m"
#define ANSI_RGB_COLOR2(r, g, b) ({ \
    char escape_sequence[20]; \
    sprintf(escape_sequence, "\x1b[38;2;%d;%d;%dm", r, g, b); \
    escape_sequence; \
})

#define ANSI_BACKGROUND_BLACK         "\x1b[40m"
#define ANSI_BACKGROUND_RED           "\x1b[41m"
#define ANSI_BACKGROUND_GREEN         "\x1b[42m"
#define ANSI_BACKGROUND_YELLOW        "\x1b[43m"
#define ANSI_BACKGROUND_BLUE          "\x1b[44m"
#define ANSI_BACKGROUND_MAGENTA       "\x1b[45m"
#define ANSI_BACKGROUND_CYAN          "\x1b[46m"
#define ANSI_BACKGROUND_WHITE         "\x1b[47m"

#define ANSI_BACKGROUND_LIGHT_BLACK   "\x1b[100m"
#define ANSI_BACKGROUND_LIGHT_RED     "\x1b[101m"
#define ANSI_BACKGROUND_LIGHT_GREEN   "\x1b[102m"
#define ANSI_BACKGROUND_LIGHT_YELLOW  "\x1b[103m"
#define ANSI_BACKGROUND_LIGHT_BLUE    "\x1b[104m"
#define ANSI_BACKGROUND_LIGHT_MAGENTA "\x1b[105m"
#define ANSI_BACKGROUND_LIGHT_CYAN    "\x1b[106m"
#define ANSI_BACKGROUND_LIGHT_WHITE   "\x1b[107m"

#define ANSI_RGB_BACKGROUND(r, g, b)  "\x1b[48;2;" #r ";" #g ";" #b "m"
#define ANSI_RGB_BACKGROUND2(r, g, b) ({ \
    char escape_sequence[20]; \
    sprintf(escape_sequence, "\x1b[48;2;%d;%d;%dm", r, g, b); \
    escape_sequence; \
})

#define ANSI_COLOR_GOLD               ANSI_RGB_COLOR(255,223,0)
#define ANSI_BACKGROUND_GOLD          ANSI_RGB_BACKGROUND(255,223,0)

#define ANSI_STYLE_BOLD               "\x1b[1m"
#define ANSI_STYLE_ITALIC             "\x1b[3m"
#define ANSI_STYLE_UNDERLINE          "\x1b[4m"
#define ANSI_STYLE_STRIKE             "\x1b[9m"

#define ANSI_PLACEMENT_RESET          "\x1b[75m"
#define ANSI_PLACEMENT_SUB            "\x1b[74m"
#define ANSI_PLACEMENT_SUPER          "\x1b[73m"

#define ARROW_UTF8                    "\u00bb"
#define ARROW_UTF8_NULL               "\u00a0"

#define ARROW_UP_UTF8                 "\u2191"
#define ARROW_DOWN_UTF8               "\u2193"
#define ARROW_LEFT_UTF8               "\u2190"
#define ARROW_RIGHT_UTF8              "\u2191"

#define BOX_UpperLeft                 "\u2554"
#define BOX_UpperRight                "\u2557"
#define BOX_LowerLeft                 "\u255a"
#define BOX_LowerRight                "\u255d"
#define BOX_Vertical                  "\u2551"
#define BOX_Horizontal                "\u2550"
