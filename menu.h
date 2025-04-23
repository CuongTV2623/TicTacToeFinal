#ifndef _MENU_H
#define _MENU_H

#include <SDL.h>
#include "graphics.h"

inline bool showMainMenu(Graphics& graphics) {
    SDL_Event e;
    bool quit = false;
    bool playSelected = false;

    SDL_Texture* background = graphics.loadTexture("nen.png");
    SDL_Texture* playButton = graphics.loadTexture("playr.png");
    SDL_Texture* quitButton = graphics.loadTexture("quitr.png");

    int screenWidth = 550;
    int screenHeight = 550;
    SDL_Rect playRect = { (screenWidth - 200) / 2, screenHeight / 3, 200, 60 };
    SDL_Rect quitRect = { (screenWidth - 200) / 2, screenHeight / 2, 200, 60 };

    while (!quit) {
        SDL_RenderClear(graphics.renderer);
        SDL_RenderCopy(graphics.renderer, background, NULL, NULL);
        SDL_RenderCopy(graphics.renderer, playButton, NULL, &playRect);
        SDL_RenderCopy(graphics.renderer, quitButton, NULL, &quitRect);
        SDL_RenderPresent(graphics.renderer);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x >= playRect.x && x <= playRect.x + playRect.w &&
                    y >= playRect.y && y <= playRect.y + playRect.h) {
                    playSelected = true;
                    quit = true;
                } else if (x >= quitRect.x && x <= quitRect.x + quitRect.w &&
                           y >= quitRect.y && y <= quitRect.y + quitRect.h) {
                    quit = true;
                }
            }
        }
    }

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(playButton);
    SDL_DestroyTexture(quitButton);

    return playSelected;
}

#endif // _MENU_H
