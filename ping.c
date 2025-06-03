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
#define BALL_VELOCITY 5 // to modify 
#define BALL_SIZE 10

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

struct Ball {
    SDL_Rect rect;
    int x_vel;
    int y_vel;
};

void sdl_initialise(struct Game *game);
void shutdown(struct Game *game);
int check_collision(struct Ball *ball, SDL_Rect *paddle);
int manage_screen_collision(struct Ball *ball);

int main (int argc, char *argv[]) {

    struct Game game = {
        .window = NULL,
        .renderer = NULL,
    };

    struct Ball ball;
    ball.rect.w = BALL_SIZE;
    ball.rect.h = BALL_SIZE;
    ball.rect.x = SCREEN_WIDTH / 2;
    ball.rect.y = SCREEN_HEIGHT / 2;
    ball.x_vel = BALL_VELOCITY;
    ball.y_vel = 2;     //should be BALL_VELOCITY but keep it 2 for testing 

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

        if (check_collision(&ball, &paddles[0]) || check_collision(&ball, &paddles[1])) {
            ball.x_vel *= -1;
        }

        manage_screen_collision(&ball);

        ball.rect.x += ball.x_vel;
        ball.rect.y += ball.y_vel;

        SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(game.renderer);

        SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(game.renderer, &paddles[0]);
        SDL_RenderFillRect(game.renderer, &paddles[1]);
        SDL_RenderFillRect(game.renderer, &ball.rect);

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

int check_collision(struct Ball *ball, SDL_Rect *paddle) {
    return (
        ball->rect.x < paddle->x + paddle->w &&
        ball->rect.x + ball->rect.w > paddle->x &&
        ball->rect.y < paddle->y + paddle->h &&
        ball->rect.y + ball->rect.h > paddle->y
    );
}

int manage_screen_collision(struct Ball *ball) {
    if (ball->rect.y < 0) {
        ball->y_vel *= -1;
    }
    if (ball->rect.y > SCREEN_HEIGHT - BALL_SIZE) {
        ball->y_vel *= -1;
    }
}