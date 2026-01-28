//
// Created by Owner on 1/16/2026.
//

#ifndef INC_2DLANG_TOKEN_H
#define INC_2DLANG_TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TT_None,
    TT_UserToken,
    TT_StringLit,

    TT_OP_EQ,
} TokenType;

typedef struct {
    TokenType type;
    char* str;
    size_t strSize;
} Token;

Token NewToken(TokenType type, char* str, size_t size);

void PrintToken(Token tok);

Token* TokenizeString(char* buffer, size_t* allocatedCount, size_t* tokenCount);


#endif //INC_2DLANG_TOKEN_H
