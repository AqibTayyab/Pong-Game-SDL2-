#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Screen dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Paddle dimensions
#define PADDLE_WIDTH 20
#define PADDLE_HEIGHT 100

// Ball dimensions
#define BALL_SIZE 15

// Speed constants
#define PADDLE_SPEED 10
#define BALL_SPEED_X 5
#define BALL_SPEED_Y 5

// Global variables
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Rect leftPaddle, rightPaddle, ball;
int ballVelocityX = BALL_SPEED_X, ballVelocityY = BALL_SPEED_Y;

// Function declarations
int init();
void closeGame();
void handleInput(SDL_Event *e);
void updateGame();
void render();
void moveBall();
void aiMove();
int checkCollision(SDL_Rect* a, SDL_Rect* b);

int main() {
    // Initialize SDL
    if (!init()) {
        printf("Failed to initialize SDL.\n");
        return 1;
    }

    // Game loop
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            handleInput(&e);
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Update game state
        updateGame();

        // Render game state
        render();

        // Delay to control game speed
        SDL_Delay(16); // ~60 FPS
    }

    // Clean up and close
    closeGame();
    return 0;
}

// Initialize SDL, window, and renderer
int init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Set the initial paddle and ball positions
    leftPaddle = (SDL_Rect){50, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT};
    rightPaddle = (SDL_Rect){SCREEN_WIDTH - 50 - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT};
    ball = (SDL_Rect){SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE, BALL_SIZE};

    return 1;
}

// Close the game and free resources
void closeGame() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Handle input from players
void handleInput(SDL_Event *e) {
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    // Player 1 (left paddle) movement
    if (keystate[SDL_SCANCODE_W] && leftPaddle.y > 0) {
        leftPaddle.y -= PADDLE_SPEED;
    }
    if (keystate[SDL_SCANCODE_S] && leftPaddle.y < SCREEN_HEIGHT - PADDLE_HEIGHT) {
        leftPaddle.y += PADDLE_SPEED;
    }

    // Player 2 (right paddle) movement
    if (keystate[SDL_SCANCODE_UP] && rightPaddle.y > 0) {
        rightPaddle.y -= PADDLE_SPEED;
    }
    if (keystate[SDL_SCANCODE_DOWN] && rightPaddle.y < SCREEN_HEIGHT - PADDLE_HEIGHT) {
        rightPaddle.y += PADDLE_SPEED;
    }
}

// Update the game state
void updateGame() {
    moveBall();
    aiMove();
}

// Move the ball, handle bouncing and scoring
void moveBall() {
    ball.x += ballVelocityX;
    ball.y += ballVelocityY;

    // Ball collision with top and bottom walls
    if (ball.y <= 0 || ball.y + BALL_SIZE >= SCREEN_HEIGHT) {
        ballVelocityY = -ballVelocityY;
    }

    // Ball collision with paddles
    if (checkCollision(&ball, &leftPaddle) || checkCollision(&ball, &rightPaddle)) {
        ballVelocityX = -ballVelocityX;
    }

    // Ball out of bounds (left or right)
    if (ball.x <= 0 || ball.x + BALL_SIZE >= SCREEN_WIDTH) {
        ball.x = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
        ball.y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;
        ballVelocityX = -ballVelocityX; // Reset direction
    }
}

// AI for right paddle (basic movement)
void aiMove() {
    if (ball.y < rightPaddle.y + PADDLE_HEIGHT / 2) {
        rightPaddle.y -= PADDLE_SPEED;
    } else if (ball.y > rightPaddle.y + PADDLE_HEIGHT / 2) {
        rightPaddle.y += PADDLE_SPEED;
    }

    // Keep AI paddle within screen bounds
    if (rightPaddle.y < 0) rightPaddle.y = 0;
    if (rightPaddle.y > SCREEN_HEIGHT - PADDLE_HEIGHT) rightPaddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
}

// Render the game objects
void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Render paddles and ball
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
    SDL_RenderFillRect(renderer, &leftPaddle);
    SDL_RenderFillRect(renderer, &rightPaddle);
    SDL_RenderFillRect(renderer, &ball);

    // Present the rendered frame
    SDL_RenderPresent(renderer);
}

// Check if two rectangles collide
int checkCollision(SDL_Rect* a, SDL_Rect* b) {
    return SDL_HasIntersection(a, b);
}
