#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"
#include "logic.h"
#include "menu.h"

using namespace std;

void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}

void processClick(int x, int y, Tictactoe& game) {
    int clickedCol = (x - BOARD_X) / CELL_SIZE;
    int clickedRow = (y - BOARD_Y) / CELL_SIZE;
    game.move(clickedRow, clickedCol);
}

int main(int argc, char* argv[]) {
    Graphics graphics;
    graphics.init();

    bool running = true;
    while (running) {
        bool playSelected = showMainMenu(graphics);

        if (!playSelected) break;

        Tictactoe game;
        game.init();
        graphics.render(game);

        bool inGame = true;
        while (inGame) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                    inGame = false;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    processClick(x, y, game);
                    graphics.render(game);

                    char result = game.checkWinner();
                    if (result == X_CELL || result == O_CELL) {
                        cout << "Player " << result << " wins!" << endl;
                        waitUntilKeyPressed();
                        inGame = false;  // back to menu
                    } else if (result == 'D') {
                        cout << "Draw!" << endl;
                        waitUntilKeyPressed();
                        inGame = false;  // back to menu
                    }
                }
            }
            SDL_Delay(100);
        }
    }

    graphics.quit();
    return 0;
}
