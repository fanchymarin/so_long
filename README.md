# so_long - ✅Grade 125/100

<p align="center">
  <img src="https://github.com/fanchymarin/so_long/assets/102818788/16107ced-81b4-4b32-8f9a-978f158061fc" />
</p>

#### Grade rating
- ✅ = Okay project
- ⭐ = Outstanding project

## Table of Contents
- [Game Overview](#game-overview)
- [Installation](#installation)
- [How to Play](#how-to-play)
- [Map Description](#map-description)
- [Controls](#controls)
- [Graphics Management](#graphics-management)
- [Bonus Features](#bonus-features)

## Game Overview
In "so_long", your goal is to guide the main character through a map to collect all the collectibles and then reach the exit while taking the shortest possible route. The game is set in a visually engaging 2D world where you must avoid walls and strategically plan your moves.

## Installation
To play the game, follow these installation instructions:

1. Clone the repository to your local machine.
2. Compile the source files using the provided Makefile.

```shell
make
```

4. Run the game with a map description file ending in the `.ber` extension as a parameter.

```shell
./so_long your_map.ber
```

## How to Play
- Your objective is to collect all the "C" (collectible) items on the map and then reach the "E" (exit) while making the fewest possible moves.
- Avoid running into "1" (wall) tiles, as you cannot move through them.
- Keep track of your movement count displayed in the shell.

## Map Description
- Maps are constructed using three components: walls (1), collectibles (C), and free spaces (0).
- A valid map must contain at least one exit (E), one collectible (C), and one player's starting position (P).
- Duplicate characters for exit or starting position result in an error.
- Maps must be rectangular and enclosed by walls. If not, an error will be displayed.
- Valid paths in the map are checked to ensure playability.

## Controls
- Use the following keys to control the main character:
- W or Up Arrow: Move up
- A or Left Arrow: Move left
- S or Down Arrow: Move down
- D or Right Arrow: Move right
- You can also use ZQSD keys as an alternative.

## Graphics Management
- The game window is displayed using the MiniLibX (42school) graphics library.
- Window management remains smooth, allowing you to switch between windows, minimize, and close the game gracefully.
- Pressing ESC or clicking the window's close button will exit the game cleanly.

## Bonus Features
- While the main game adheres to the provided rules, some bonus features to enhance the gaming experience has been added:
- **Enemy Patrol**: Touching an enemy patrol results in the player losing the game.
- **Sprite Animation**: Enjoy animated sprites that bring the game world to life.
- **On-Screen Movement Count**: See your movement count directly on the screen for convenience.

