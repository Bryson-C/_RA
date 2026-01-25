cmake_minimum_required(VERSION 3.28)
project(2DLang C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Runtime)

include_directories(${PROJECT_SOURCE_DIR}/Lib/SDL3/include)
include_directories(${PROJECT_SOURCE_DIR}/Lib/SDL3_Image/include)
link_directories(${PROJECT_SOURCE_DIR}/Lib/SDL3/lib/x64)
link_directories(${PROJECT_SOURCE_DIR}/Lib/SDL3_Image/lib/x64)

add_executable(2DLang main.c
        Editor/Editor.h
        Editor/Editor.c
        LangImpl/Token.h
        LangImpl/Token.c
        LangImpl/FileSystem.h
        LangImpl/FileSystem.c
)

target_link_libraries(${PROJECT_NAME} SDL3.lib SDL3_image.lib)
