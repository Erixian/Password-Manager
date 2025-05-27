#include "file_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #define mkdir(dir) _mkdir(dir)
    #define PATH_SEP '\\'
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #define PATH_SEP '/'
#endif

// Returns the OS-specific data directory path
const char* get_data_dir() {
    static char path[256];

#ifdef _WIN32
    const char *appdata = getenv("APPDATA");
    snprintf(path, sizeof(path), "%s%spassword_manager", appdata, PATH_SEP);
#else
    const char *home = getenv("HOME");
    snprintf(path, sizeof(path), "%s%cpassword_manager", home, PATH_SEP);
#endif

    return path;
}

// Creates the data directory if it doesn't exist
void setup_data_directory() {
    const char *dir = get_data_dir();

#ifdef _WIN32
    _mkdir(dir);
#else
    mkdir(dir, 0700);  // Linux/macOS: rwx permissions for owner
#endif
}

// Returns the full path to auth_user.txt
char* get_auth_file_path() {
    static char path[256];
    snprintf(path, sizeof(path), "%s%cauth_user.txt", get_data_dir(), PATH_SEP);
    return path;
}

// Initialize data file (create if missing)
void init_auth_file() {
    FILE *file = fopen(get_auth_file_path(), "a+");  // Opens or creates file
    if (file) {
        fclose(file);
    } else {
        perror("Failed to initialize auth file");
        exit(1);
    }
}