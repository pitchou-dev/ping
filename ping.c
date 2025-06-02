#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#define WINDOW_TITLE "ping pong game"
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define PADDLE_WIDTH 20
#define PADDLE_HEIGHT 100
#define PADDLE_VELOCITY 5

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

    SDL_Rect paddles[2];
    paddles[0].x = 50;
    paddles[1].x = SCREEN_WIDTH - PADDLE_WIDTH -50;
    paddles[0].y = (SCREEN_HEIGHT - PADDLE_HEIGHT)/2;
    paddles[1].y = (SCREEN_HEIGHT - PADDLE_HEIGHT)/2;
    paddles[0].w = PADDLE_WIDTH;
    paddles[1].w = PADDLE_WIDTH;
    paddles[0].h = PADDLE_HEIGHT;
    paddles[1].h = PADDLE_HEIGHT;

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

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_W] && paddles[0].y > 0) {
            paddles[0].y -= PADDLE_VELOCITY;
        }
        if (state[SDL_SCANCODE_S] && paddles[0].y < SCREEN_HEIGHT - PADDLE_HEIGHT) {
            paddles[0].y += PADDLE_VELOCITY;
        }
        if (state[SDL_SCANCODE_UP] && paddles[1].y > 0) {
            paddles[1].y -= PADDLE_VELOCITY;
        }
        if (state[SDL_SCANCODE_DOWN] && paddles[1].y < SCREEN_HEIGHT - PADDLE_HEIGHT) {
            paddles[1].y += PADDLE_VELOCITY;
        }

        SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(game.renderer);

        SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(game.renderer, &paddles[0]);
        SDL_RenderFillRect(game.renderer, &paddles[1]);

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