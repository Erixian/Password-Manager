#include "user.h"
#include "file_operations.h"
#include "auth.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    User *user_data = malloc(sizeof(User));

    setup_data_directory(); // cria um diretorio com nome de "password_manager"
    init_auth_file(); // cria um arquivo no "password_manager" com nome de auth_file

    while(1) {
        char choice = '0';
        display_main_menu();
        scanf(" %c", &choice);

        switch(choice) {
            case '1':
                display_login_screen();
            printf("PLEASE ENTER USERNAME:\t");
            scanf("%s", user_data->username);
            printf("PLEASE ENTER PASSWORD:\t");
            scanf("%s", user_data->pwd);

            if(authentication(user_data) == 1) {
                printf("LOGIN SUCCESS\n");
            } else {
                printf("LOGIN FAILED\n");
            }
            toSleep(2);
            break;

            case '2':
                display_register_screen();
            printf("PLEASE ENTER USERNAME:\t");
            scanf("%s", user_data->username);
            printf("PLEASE ENTER PASSWORD:\t");
            scanf("%s", user_data->pwd);

            if(usernameValidation(user_data) == 1) {
                if (registerUser(user_data) == 1) {
                    printf("REGISTER USER SUCCESSFULLY LOGGED!\n");
                }
                else {
                    printf("USER REGISTRATION FAILED!");
                }
            } else {
                printf("INVALID USERNAME!\n");
            }
            toSleep(2);
            break;

            case '3':
                clearScreen();
            free(user_data);
            exit(0);

            default:
                printf("INVALID CHOICE\n");
            toSleep(2);
        }
    }

    free(user_data);
    return 0;
}