
// Platform-specific includes
#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <termios.h>
    #include <unistd.h>
#endif
// Function to enable or disable echo
void setEcho(int enable) {
    #ifdef _WIN32
        // Windows implementation
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;

        GetConsoleMode(hStdin, &mode);

        if (enable) {
            // Enable echo
            mode |= ENABLE_ECHO_INPUT;
        } else {
            // Disable echo
            mode &= ~ENABLE_ECHO_INPUT;
        }

        SetConsoleMode(hStdin, mode);
    #elif __linux__ || __APPLE__
        // Linux and macOS implementation
        struct termios tty;

        tcgetattr(STDIN_FILENO, &tty);

        if (enable) {
            // Enable echo
            tty.c_lflag |= ECHO;
        } else {
            // Disable echo
            tty.c_lflag &= ~ECHO;
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    #endif
}
