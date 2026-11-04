cmake_minimum_required(VERSION 4.2)
project(parseurTest C)

set(CMAKE_C_STANDARD 23)
include(FetchContent)

#git for lexer
FetchContent_Declare(
        alexer
        GIT_REPOSITORY https://github.com/tsoding/alexer.git
        GIT_TAG main
)
FetchContent_GetProperties(alexer)

if(NOT alexer_POPULATED)
    FetchContent_MakeAvailable(alexer)
endif()
add_library(alexer INTERFACE)
target_include_directories(alexer INTERFACE
        ${alexer_SOURCE_DIR}
)



#git for cglm
FetchContent_Declare(
        cglm
        GIT_REPOSITORY https://github.com/recp/cglm.git
        GIT_TAG        v0.9.7
)
FetchContent_MakeAvailable(cglm)
find_package(SDL3 REQUIRED)


add_executable(testWindows
        src/main.c
        src/3DMotor.c
        src/3DMotor.h
        src/fileReader.c
        src/fileReader.h
        src/OBJ_parser.h
        src/OBJ_parser.c
        src/Mechanical_arm.c
        src/Mechanical_arm.h
)

target_link_libraries(testWindows PRIVATE alexer)
target_link_libraries(testWindows PRIVATE cglm)
target_link_libraries(testWindows PRIVATE m)
target_link_libraries(testWindows PRIVATE SDL3::SDL3)
