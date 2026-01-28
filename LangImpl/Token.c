//
// Created by Owner on 1/16/2026.
//
#include "Token.h"

Token NewToken(TokenType type, char* str, size_t size) {
    Token t;
    t.type = type;
    if (str != NULL) {
        t.strSize = size;
        t.str = str;
    }

    return t;
}

char* GetTokenTypeAsString(TokenType tt) {
    switch (tt) {
        case TT_UserToken: return "UserToken";
        case TT_StringLit: return "StrLit";
        default: break;
    }
    return "None";
}
void PrintToken(Token tok) {
#define DEBUG_TOK_PRINT
#ifdef DEBUG_TOK_PRINT
    printf("(%s) %*.*s", GetTokenTypeAsString(tok.type), 0, (int)tok.strSize, tok.str);
#else
    printf("%*.*s", 0, (int)tok.strSize, tok.str);
#endif
}

typedef enum { None, Number, Alpha, Symbol, Space } CharType;
CharType GetCharTypeFromChar(char c) {
    if (isalpha(c)) return Alpha;
    else if (isdigit(c)) return Number;
    else if (isspace(c)) return Space;
    else if (!isalnum(c) && !isspace(c)) return Symbol;
    return None;
}


TokenType getOperatorFromBufferLookAhead(char* buffer, int* it) {
    printf("Look Ahead: ");
    // Will Search Until Alphanumeric Character Is Found
    int i = *it;
    size_t size = strlen(buffer);
    while (i+1 < size && !isalnum(buffer[i]) && !isspace(buffer[i])) {
        printf("%c", buffer[i]);
        i++;
    }
    printf("\n");
    return TT_None;
}


Token* TokenizeString(char* buffer, size_t* allocatedCount, size_t* tokenCount) {
    *allocatedCount = 256;
    Token* array = malloc(sizeof(Token) * (*allocatedCount));

    CharType lastReadType = GetCharTypeFromChar(buffer[0]);
    Token tok;
    int startPos = 0;
    // Fixme: if end of token is at end of file, parser will ignore, make sure the token is appended
    for (int i = 0; i < strlen(buffer); i++) {
        /*if (buffer[i] == '\"') {
            //continue;
        }*/

        // split on characters
        if (!isalnum(buffer[i]) && buffer[i] != '\n') {
            getOperatorFromBufferLookAhead(buffer, &i);

            tok.str = buffer+startPos;
            tok.strSize = ((i)-startPos);

            if (tok.strSize > 0 && !(tok.strSize == 1 && isspace(tok.str[0])))
                array[(*tokenCount)++] = tok;


            lastReadType = GetCharTypeFromChar(buffer[i]);
            startPos = i;
            continue;
        }

        if (lastReadType != GetCharTypeFromChar(buffer[i]) || buffer[i] == '\n') {
            tok.str = buffer+startPos;
            tok.strSize = ((i)-startPos);

            if (tok.strSize > 0 && !(tok.strSize == 1 && isspace(tok.str[0])))
                array[(*tokenCount)++] = tok;

            lastReadType = GetCharTypeFromChar(buffer[i]);
            startPos = i;
            continue;
        }



    }
    tok.str = buffer+startPos;
    tok.strSize = (-startPos);
    array[(*tokenCount)++] = tok;

    return array;
}