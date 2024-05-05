
#define ANSI_RESET_ALL                "\x1b[0m"

#define ANSI_COLOR_BLACK              "\x1b[30m"
#define ANSI_COLOR_RED                "\x1b[31m"
#define ANSI_COLOR_GREEN              "\x1b[32m"
#define ANSI_COLOR_YELLOW             "\x1b[33m"
#define ANSI_COLOR_BLUE               "\x1b[34m"
#define ANSI_COLOR_MAGENTA            "\x1b[35m"
#define ANSI_COLOR_CYAN               "\x1b[36m"
#define ANSI_COLOR_WHITE              "\x1b[37m"

#define ANSI_COLOR_LIGHT_BLACK        "\x1b[90m"
#define ANSI_COLOR_LIGHT_RED          "\x1b[91m"
#define ANSI_COLOR_LIGHT_GREEN        "\x1b[92m"
#define ANSI_COLOR_LIGHT_YELLOW       "\x1b[93m"
#define ANSI_COLOR_LIGHT_BLUE         "\x1b[94m"
#define ANSI_COLOR_LIGHT_MAGENTA      "\x1b[95m"
#define ANSI_COLOR_LIGHT_CYAN         "\x1b[96m"
#define ANSI_COLOR_LIGHT_WHITE        "\x1b[97m"

#define ANSI_RGB_COLOR(r, g, b)       "\x1b[38;2;" #r ";" #g ";" #b "m"

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

#define ANSI_COLOR_GOLD               ANSI_RGB_COLOR(255,223,0)
#define ANSI_BACKGROUND_GOLD          ANSI_RGB_BACKGROUND(255,223,0)

#define ANSI_STYLE_BOLD               "\x1b[1m"
#define ANSI_STYLE_ITALIC             "\x1b[3m"
#define ANSI_STYLE_UNDERLINE          "\x1b[4m"
#define ANSI_STYLE_STRIKE             "\x1b[9m"

#define ANSI_PLACEMENT_RESET          "\x1b[75m"
#define ANSI_PLACEMENT_SUB            "\x1b[74m"
#define ANSI_PLACEMENT_SUPER          "\x1b[73m"

#define ARROW_ASCII                   175

#define BOX_UpperLeft                 201 
#define BOX_UpperRight                187  
#define BOX_LowerLeft                 200  
#define BOX_LowerRight                188   
#define BOX_Vertical                  186    
#define BOX_Horizontal                205