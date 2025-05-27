cmake_minimum_required(VERSION 3.30)
project(pwdmanager_C C)

set(CMAKE_C_STANDARD 99)

# Find OpenSSL package
find_package(OpenSSL REQUIRED)

# List all source files
set(SOURCE_FILES
        src/main.c
        src/file_operations.c
        src/auth.c
        src/ui.c
)

# List all header directories
include_directories(
        include/
        ${OPENSSL_INCLUDE_DIR}
)

# Create the executable and link OpenSSL
add_executable(pwdmanager_C ${SOURCE_FILES})
target_link_libraries(pwdmanager_C PRIVATE OpenSSL::Crypto)