#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void toSleep(int seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif
}

void clearScreen() {
#ifdef _WIN32
    system("cls");      // Windows command
#else
    system("clear");    // Linux/macOS/Unix command
#endif
}

void display_main_menu() {
    clearScreen();
    printf("WELCOME TO PASSWORD MANAGER!\n\n");
    printf("PLEASE ENTER AN NUMBER:\n");
    printf("1 - LOGIN\n");
    printf("2 - REGISTER USER\n");
    printf("3 - EXIT\n");
}

void display_login_screen() {
    clearScreen();
    printf("LOGIN SCREEN\n");
}

void display_register_screen() {
    clearScreen();
    printf("REGISTER USER\n");
}