# Homework
# D&D Game

Welcome to the **D&D Games**, a console-based adventure game where players explore dangerous dungeons, fight monsters, and search for treasures. This project is written in C.

### Game-Objective 

Extenguish the dragon in one of the rooms and escape from the dungeon.

### In-Game Command

- **`move <direction>`** : Move to a different room if possible.  
   - Directions: `up`, `down`, `left`, `right`.  
- **`look`** : Display the description of the current room, including items and creatures.  
- **`inventory`** : List the items the player has collected.  
- **`pickup <item>`** : Add an item to your inventory if it is present in the room.  
- **`attack`** : Fight a creature if there is one in the room

### Menu Commands 

- **`list`** : Lists the saved games.  
- **`save <filepath>`** : Saves the current game state to the specified file.  
- **`load <filepath>`** : Loads a previously saved game state from the specified file.
- **`exit`** 















### Requirements:
-C Compiler(GCC mingw etc.).
-I use Makefile instead of Cmake

### How to Run

Run the following command in your terminal:
cd "Game Path"(wherever you downloaded the game)
gcc main.c game.c file_io.c -o dungeons_game
.\dungeons_games

