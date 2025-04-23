#include "graphics.h"

void Graphics::logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
    exit(1);
}

SDL_Texture *Graphics::loadTexture(const char *filename) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == nullptr)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Failed to load texture %s: %s", filename, IMG_GetError());
    return texture;
}

void Graphics::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG))
        logErrorAndExit("IMG_Init", IMG_GetError());

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) logErrorAndExit("CreateWindow", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) logErrorAndExit("CreateRenderer", SDL_GetError());

    background = loadTexture("assets/background.png");
    cellEmpty  = loadTexture("assets/cell_empty.png");
    cellX      = loadTexture("assets/cell_x.png");
    cellO      = loadTexture("assets/cell_o.png");
}

void Graphics::prepareScene() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Graphics::presentScene() {
    SDL_RenderPresent(renderer);
}

void Graphics::renderTexture(SDL_Texture *texture, int x, int y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Graphics::renderTextureScaled(SDL_Texture *texture, int x, int y, float scale) {
    SDL_Rect dest;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.x = x;
    dest.y = y;
    dest.w *= scale;
    dest.h *= scale;
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Graphics::render(const Tictactoe& game) {
    prepareScene();

    SDL_RenderCopy(renderer, background, NULL, NULL);

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            int x = BOARD_X + j * CELL_SIZE;
            int y = BOARD_Y + i * CELL_SIZE;

            switch (game.board[i][j]) {
                case EMPTY_CELL: renderTextureScaled(cellEmpty, x, y); break;
                case X_CELL:     renderTextureScaled(cellX, x, y); break;
                case O_CELL:     renderTextureScaled(cellO, x, y); break;
            }
        }
    }

    presentScene();
}

void Graphics::quit() {
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(cellEmpty);
    SDL_DestroyTexture(cellX);
    SDL_DestroyTexture(cellO);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

