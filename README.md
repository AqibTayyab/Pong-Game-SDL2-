Pong Game (SDL2)
Introduction
A classic 2-player Pong game created using C and the SDL2 library. This game demonstrates basic collision physics, AI paddle movement, and can be extended with power-ups and difficulty levels.
Features
- 2-player mode: Control paddles using the keyboard.
- AI Player: The right paddle is controlled by AI.
- Ball physics: The ball bounces off the paddles and walls.
- Extendable: Easy to add more features like power-ups and difficulty levels.
Installation
1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/AqibTayyab/Pong-Game-SDL2-.git
   ```

2. Navigate to the project directory:
   ```bash
   cd Pong-Game-SDL2-
   ```

3. Install the SDL2 library if you haven't already:
- For Ubuntu/Debian:
  ```bash
  sudo apt-get install libsdl2-dev
  ```

- For macOS (using Homebrew):
  ```bash
  brew install sdl2
  ```

- For Windows: Download SDL2 from https://github.com/libsdl-org/SDL and set up the environment.
Building the Game
1. After installing SDL2, you can compile the game using the following command:
   ```bash
   gcc -o main.c -lSDL2
   ```

2. Run the game:
   ```bash
   ./main
   ```
How to Play
Player 1 (Left Paddle):
- Move up: Press `W`
- Move down: Press `S`
Player 2 (Right Paddle):
- Move up: Press `UP Arrow`
- Move down: Press `DOWN Arrow`
Game Rules:
1. Bouncing the ball past the opponent’s paddle is the objective.
2. If the ball passes one player's paddle, the game resets, and the ball is placed back in the center.
3. The ball will bounce off the top and bottom walls and the paddles.
4. The game runs in a loop until you close it manually.
Enhancements & TODO
- Power-ups: Add random power-ups like paddle size increase, ball speed increase, etc.
- Difficulty Levels: Adjust AI difficulty by changing its paddle speed based on the game’s difficulty setting.
- Scoring System: Implement a score counter and display it on the screen.
License
This project is licensed under the MIT License - see the LICENSE file for details.
