#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "logic.h"

struct Graphics {
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;

    SDL_Texture* background = nullptr;
    SDL_Texture* cellEmpty = nullptr;
    SDL_Texture* cellX = nullptr;
    SDL_Texture* cellO = nullptr;

    SDL_Texture* menuBackground = nullptr;
    SDL_Texture* playButton = nullptr;
    SDL_Texture* quitButton = nullptr;

    void init() {
        initSDL();
        background = loadTexture("nenf.png");
        /*cellEmpty = loadTexture("cell_empty2.png");*/
        cellX = loadTexture("x1rr.png");
        cellO = loadTexture("o1rr.png");

        menuBackground = loadTexture("nen.png");
        playButton = loadTexture("playr.png");
        quitButton = loadTexture("quitr.png");
    }

    void render(const Tictactoe& game) {
        prepareScene(background);
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++) {
                int x = BOARD_X + j * CELL_SIZE;
                int y = BOARD_Y + i * CELL_SIZE;
                switch (game.board[i][j]) {
                    case EMPTY_CELL: renderTexture(cellEmpty, x, y); break;
                    case X_CELL: renderTexture(cellX, x, y); break;
                    case O_CELL: renderTexture(cellO, x, y); break;
                };
            };

        presentScene();
    }

    void renderMenu() {
        prepareScene(menuBackground);
        renderTexture(playButton, 175, 200);
        renderTexture(quitButton, 175, 300);
        presentScene();
    }

    void logErrorAndExit(const char* msg, const char* error) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

    void initSDL() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit("SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    void prepareScene(SDL_Texture * background) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
    }

    void prepareScene() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void presentScene() {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char *filename) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y) {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y) {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }

    void quit() {
        SDL_DestroyTexture(cellEmpty);
        cellEmpty = nullptr;
        SDL_DestroyTexture(cellX);
        cellX = nullptr;
        SDL_DestroyTexture(cellO);
        cellO = nullptr;
        SDL_DestroyTexture(menuBackground);
        SDL_DestroyTexture(playButton);
        SDL_DestroyTexture(quitButton);
        menuBackground = playButton = quitButton = nullptr;

        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

#endif // _GRAPHICS__H
