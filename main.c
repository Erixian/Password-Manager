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

typedef struct User {
        char username[20];
        char pwd[20];
}user;

void toSleep();
const char* get_data_dir();
void setup_data_directory();
char* get_auth_file_path();
void init_auth_file();

//int authentication(user*);
int usernameValidation(user*);
int registerUser(user*);
void clearScreen();


int main(void) {

    user *user_data = malloc(sizeof(user));

    setup_data_directory(); //cria um diretorio com nome de "password_manager"
    init_auth_file();//cria um arquivo no "password_manager" com nome de auth_file

    while(1) {

        char choice = '0';
        clearScreen();
        system("clear");
        printf("WELCOME TO PASSWORD MANAGER!\n\n");
        printf("PLEASE ENTER AN NUMBER:\n");
        printf("1 - LOGIN\n");
        printf("2 - REGISTER USER\n");
        printf("3 - EXIT\n");

        scanf(" %c", &choice);

        switch(choice) {
            case '1':
                clearScreen();
                printf("LOGIN SCREEN\n");
                printf("PLEASE ENTER USERNAME:\t");
                scanf("%s", user_data->username);
                printf("PLEASE ENTER PASSWORD:\t");
                scanf("%s", user_data->pwd);

            /* authentication(user_data);

             if(authentication(user_data) == 1) {
                 printf("LOGIN SUCCESS\n");
             }*/
                toSleep(2);
                break;

            case '2':
                clearScreen();
                printf("REGISTER USER\n");
                printf("PLEASE ENTER USERNAME:\t");
                scanf("%s", user_data->username);
                printf("PLEASE ENTER PASSWORD:\t");
                scanf("%s", user_data->pwd);

                if(usernameValidation(user_data) == 1) {
                    if (registerUser(user_data) == 1) {
                        printf("REGISTER USER SUCCESSFULLY LOGGED!\n");
                    }
                    else
                        printf("USER REGISTRATION FAILED!");
                }
                else {
                    printf("INVALID USERNAME!\n");
                }
                toSleep(2);
                break;

            case '3':
                clearScreen();
                exit(0);
            default:
                printf("INVALID CHOICE\n");
                toSleep(2);
        }
    }
    free(user_data);
    return 0;
}

void toSleep() {
#ifdef _WIN32
    Sleep(secods * 1000);
#else
    sleep(1);
#endif
}

void clearScreen() {
#ifdef _WIN32
    system("cls");      // Windows command
#else
    system("clear");    // Linux/macOS/Unix command
#endif
}

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

int usernameValidation(user *user_data) {
    //read the file
    char buffer[100];
    int flag = 0;
    FILE *f = fopen(get_auth_file_path(), "r");
    if(f == NULL) {
        printf("FILE NOT FOUND\n");
        return 0;
    }

    while (fscanf(f, "%s %*s", buffer) != EOF) {
        if (strcmp(buffer, user_data->username) == 0)
            flag++;
    }

    fclose(f);

    return (flag > 0) ? 0 : 1;
}

int registerUser(user *user_data) {
    FILE *f = fopen(get_auth_file_path(), "a+");
    if(f == NULL) {
        printf("FILE NOT FOUND\n");
        return 0;
    }

    fprintf(f, "%s\t", user_data->username);
    fprintf(f, "%s\n", user_data->pwd);

    fclose(f);
    return 1;
}

