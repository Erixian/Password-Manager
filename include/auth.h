#ifndef AUTH_H
#define AUTH_H

#include "user.h"

int authentication(User*);
int usernameValidation(User*);
int registerUser(User*);
void toHashPassword(const unsigned char *, unsigned char *);

#endif