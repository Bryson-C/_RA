//
// Created by Owner on 1/16/2026.
//

#ifndef INC_2DLANG_FILESYSTEM_H
#define INC_2DLANG_FILESYSTEM_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_WIDTH 512
char* ReadFile(const char* path, size_t* fileSize);

#endif //INC_2DLANG_FILESYSTEM_H
