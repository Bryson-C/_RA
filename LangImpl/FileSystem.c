//
// Created by Owner on 1/16/2026.
//

#include "FileSystem.h"

char* ReadFile(const char* path, size_t* fileSize) {
    FILE* file;
    fopen_s(&file, path, "r");
    fseek(file, 0L, SEEK_END);
    *fileSize = ftell(file);
    rewind(file);
    char* buffer = calloc((*fileSize)+1, sizeof(char));
    int bufferOffset = 0;

    char line[MAX_LINE_WIDTH];
    while (fgets(line, INT_MAX, file)) {
        strcpy(buffer+bufferOffset, line);
        bufferOffset += strlen(line);
    }
    fclose(file);
    buffer[*fileSize] = '\0';
    return buffer;
}
