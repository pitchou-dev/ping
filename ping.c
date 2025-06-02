#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#define WINDOW_TITLE "ping pong game"
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

void sdl_initialise(struct Game *game);
void shutdown(struct Game *game);

int main (int argc, char *argv[]) {

    struct Game game = {
        .window = NULL,
        .renderer = NULL,
    };

    sdl_initialise(&game);

    while (1) { 
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    shutdown(&game);
                break;
                default:
                    break;
            }
        }

        SDL_RenderClear(game.renderer);

        SDL_RenderPresent(game.renderer);
        SDL_Delay(16);
    }

    return 0; 
}

void sdl_initialise (struct Game *game) {
    SDL_Init(SDL_INIT_EVERYTHING);

    game->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    game->renderer = SDL_CreateRenderer(game->window, -1, 0);
}

void shutdown(struct Game *game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
    exit(EXIT_SUCCESS);
}