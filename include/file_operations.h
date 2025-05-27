#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "user.h"

const char* get_data_dir();
void setup_data_directory();
char* get_auth_file_path();
void init_auth_file();

#endif