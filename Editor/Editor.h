//
// Created by Owner on 1/14/2026.
//

#ifndef INC_2DLANG_EDITOR_H
#define INC_2DLANG_EDITOR_H

#include <stdio.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>



#include <time.h>

typedef struct {
    clock_t time;
} Timer;

inline Timer createTimer() {
    Timer timer;
    timer.time = clock();
    return timer;
}
// Returns Whether The Delay Has Been Passed Since Last Call Or Initialization
inline bool isTimerComplete(Timer* timer, int delay) { return (clock() - timer->time > delay);  }
// Resets Timer
inline void resetTimer(Timer* timer) { timer->time = clock(); }
// Returns If The Timer Is Complete,
//      If It Is Complete, Reset The Timer And Return True,
//      Otherwise Let The Timer Continue And Return False
inline bool isTimerCompleteReset(Timer* timer, int delay) {
    bool complete = (clock() - timer->time > delay);
    if (complete) resetTimer(timer);
    return complete;
}
inline clock_t getTimerTime(Timer* timer) {
    return (clock()-timer->time);
}
inline void removeTimerTime(Timer* timer, clock_t delay) {
    timer->time -= delay;
}
inline float getTimerPercent(Timer* timer, clock_t delay) {
    return ((float)getTimerTime(timer)/(float)delay);
}


typedef enum {
    ET_None,
    ET_HorizontalWall,
    ET_VerticalWall,
    ET_Dot,
} EditorTile;

SDL_FRect GetEditorTileTextureLocation(EditorTile tile);

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* fontTexture;

    int editorWidth, editorHeight;
    int charPadding;

    int cursorX, cursorY;
    Timer updateTimer;
    int updateTick;
} Editor;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
Editor LaunchEditor();
void DrawEditorWindow(Editor* editor);
void UpdateEditor(Editor* editor, SDL_Event* event);






#endif //INC_2DLANG_EDITOR_H
