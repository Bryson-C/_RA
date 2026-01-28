#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef TEST_EDITOR
#include "Editor/Editor.h"
#endif

#include "LangImpl/Token.h"
#include "LangImpl/FileSystem.h"


// WHAT UP GANG!

int main(void) {

    size_t fileSize = 0;
    char* fileBuffer = ReadFile("Lang/Main.rp", &fileSize);

#ifdef TEST_EDITOR
    Editor editor = LaunchEditor();
    bool running = true;
    while (running) {
        SDL_Event event;
        SDL_PollEvent(&event);

        if (event.key.key == SDLK_ESCAPE || event.type == SDL_EVENT_QUIT) {
            running = false;
        }
        UpdateEditor(&editor, &event);

        SDL_RenderClear(editor.renderer);

        DrawEditorWindow(&editor);

        SDL_RenderPresent(editor.renderer);
    }
#endif

    size_t allocatedElements = 0;
    size_t tokArraySize = 0;
    Token* tokArray = TokenizeString(fileBuffer, &allocatedElements, &tokArraySize);

    for (int i = 0; i < tokArraySize; i++) {
        PrintToken(tokArray[i]);
        printf("\n");
    }

    return 0;
}
