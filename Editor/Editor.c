//
// Created by Owner on 1/14/2026.
//

#include "Editor.h"

Editor LaunchEditor() {
    Editor editor;
    SDL_Init(SDL_INIT_VIDEO);
    editor.window = SDL_CreateWindow("Editor", 800, 600, SDL_WINDOW_RESIZABLE);
    editor.renderer = SDL_CreateRenderer(editor.window, "");

    editor.editorWidth = editor.editorHeight = 10;
    editor.charPadding = 2;
    editor.cursorX = editor.cursorY = 0;

    editor.updateTimer = createTimer();
    editor.updateTick = 0;

    editor.fontTexture = loadTexture(editor.renderer, "Asset/font.png");
    return editor;
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path) {
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! \n", path);
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_DestroySurface( loadedSurface );
    }
    return newTexture;
}


SDL_FRect GetGridTilePosition(int gridX, int gridY, int size, int width, int height, int padding) {
    return (SDL_FRect){(gridX) * (size+(padding)), (gridY) * (size+(padding)), size, size};
}
SDL_FRect  GetGridTilePositionFromIndex(int i, int size, int width, int height, int padding) {
    return (SDL_FRect){(i%width) * (size+(padding)), (i/height) * (size+(padding)), size, size};
}

SDL_FRect GetEditorTileTextureLocation(EditorTile tile) {
    switch (tile) {
        case ET_VerticalWall:
            return (SDL_FRect){10 * 16, 11 * 16, 16.0f, 16.0f};
        case ET_HorizontalWall:
            return (SDL_FRect){13 * 16, 12 * 16, 16.0f, 16.0f};

        case ET_Dot:
            return (SDL_FRect){9 * 16, 15 * 16, 16.0f, 16.0f};

        case ET_None:
        default:
            return (SDL_FRect){0.0f,0.0f,0.0f,0.0f};
    }
}

void DrawEditorWindow(Editor* editor) {

    Uint8 r,g,b,a;
    SDL_GetRenderDrawColor(editor->renderer, &r, &g, &b, &a);
    //SDL_SetRenderDrawBlendMode(editor->renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(editor->renderer, 255, 255, 255, 255);
    SDL_SetTextureScaleMode(editor->fontTexture, SDL_SCALEMODE_NEAREST);

    float charSize = 16.0f * 2.0f;

    SDL_SetTextureColorMod(editor->fontTexture, 255, 0, 0);
    SDL_FRect rect = GetGridTilePosition(editor->cursorX, editor->cursorY, charSize, editor->editorWidth, editor->editorHeight, editor->charPadding);
    SDL_FRect cursorSrc;

    if (editor->updateTick % 5000 > 2500)
        cursorSrc = (SDL_FRect){15 * 16, 15 * 16, 16, 16};
    else
        cursorSrc = (SDL_FRect){14 * 16, 15 * 16, 16, 16};
    SDL_RenderTexture(editor->renderer, editor->fontTexture, &cursorSrc, &rect);





    SDL_SetTextureColorMod(editor->fontTexture, 255, 255, 255);

    for (int i = 0; i < editor->editorWidth * editor->editorHeight; i++) {

        SDL_FRect src = GetEditorTileTextureLocation(ET_Dot);



        SDL_FRect rect = GetGridTilePositionFromIndex(i, charSize, editor->editorWidth, editor->editorHeight, editor->charPadding);
        SDL_RenderTexture(editor->renderer, editor->fontTexture, &src, &rect);
    }






    SDL_SetRenderDrawColor(editor->renderer, r, g, b, a);
}

void UpdateEditor(Editor* editor, SDL_Event* event) {
    if (!isTimerComplete(&(editor->updateTimer), 100)) return;
    switch (event->key.scancode) {
        case SDL_SCANCODE_RIGHT: editor->cursorX++; break;
        case SDL_SCANCODE_LEFT: editor->cursorX--; break;
        case SDL_SCANCODE_UP: editor->cursorY--; break;
        case SDL_SCANCODE_DOWN: editor->cursorY++; break;
        default: break;
    }
    if (editor->cursorX < 0) editor->cursorX = 0;
    if (editor->cursorY < 0) editor->cursorY = 0;
    if (editor->cursorX > editor->editorWidth-1) editor->cursorX = editor->editorWidth-1;
    if (editor->cursorY > editor->editorHeight-1) editor->cursorY = editor->editorHeight-1;
    if (event->key.down == true) resetTimer(&(editor->updateTimer));
    editor->updateTick++;
}