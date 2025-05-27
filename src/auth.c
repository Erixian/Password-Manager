#include "auth.h"
#include "file_operations.h"
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int usernameValidation(User *user_data) {
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

int registerUser(User *user_data) {
    FILE *f = fopen(get_auth_file_path(), "a+");
    unsigned char hashed_password[64];
    if(f == NULL) {
        printf("FILE NOT FOUND\n");
        return 0;
    }

    fprintf(f, "%s\t", user_data->username);

    toHashPassword(user_data->pwd, hashed_password);

    fprintf(f, "%s\n", hashed_password);

    fclose(f);
    return 1;
}

int authentication(User* user_data) {
    // Implementação da autenticação
    return 0; // Temporário - implementar lógica real
}

void toHashPassword(const unsigned char *password, unsigned char *output_hash) {

    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(password, strlen(password), hash);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(output_hash + (i * 2), "%02x", hash[i]);
    }

    //output_hash[64] = '\0';
}