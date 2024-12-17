#include <stdio.h>
#include <string.h>
#include "game.h"
#include <stdlib.h>

// Initialize the game, rooms, and monsters
void initialize_game(Game *game) {
    game->player_health = 100;
    game->player_damage = 20;  // Default damage

    game->current_room = 6; // Start in the bottom-left room (index 6)
    game->inventory_count = 0;

    // Room 0 (Top-left): Dragon
    strcpy(game->rooms[0].description, "You encounter a Dragon!");
    game->rooms[0].monster_health = 70;
    game->rooms[0].monster_damage = 25;
    game->rooms[0].monster_type = 3;
    game->rooms[0].item_count = 0;

    // Room 1 (Top-center): Empty
    strcpy(game->rooms[1].description, "A deep silence, nothing here.");
    game->rooms[1].item_count = 0;
    game->rooms[1].monster_type = 0;

    // Room 2 (Top-right): Taurus Demon
    strcpy(game->rooms[2].description, "You face the Taurus Demon!");
    game->rooms[2].monster_health = 70;
    game->rooms[2].monster_damage = 30;
    game->rooms[2].monster_type = 4;
    game->rooms[2].item_count = 1;
    strcpy(game->rooms[2].items[0], "dagger");

    // Room 3 (Middle-left): Goblin, Sword and Shield
    strcpy(game->rooms[3].description, "You encounter a Goblin!");
    game->rooms[3].monster_health = 30;
    game->rooms[3].monster_damage = 10;
    game->rooms[3].monster_type = 1;
    game->rooms[3].item_count = 2;
    strcpy(game->rooms[3].items[0], "sword");
    strcpy(game->rooms[3].items[1], "shield");

    // Room 4 (Middle-center): Player's starting room
    strcpy(game->rooms[4].description, "You are in the starting room.");
    game->rooms[4].item_count = 0;
    game->rooms[4].monster_type = 0;

    // Room 5 (Middle-right): Orc, Spear
    strcpy(game->rooms[5].description, "You encounter an Orc!");
    game->rooms[5].monster_health = 60;
    game->rooms[5].monster_damage = 15;
    game->rooms[5].monster_type = 5;
    game->rooms[5].item_count = 1;
    strcpy(game->rooms[5].items[0], "spear");

    // Room 6 (Bottom-left): Witch, Healing Potion
    strcpy(game->rooms[6].description, "You encounter a Witch!");
    game->rooms[6].monster_health = 40;
    game->rooms[6].monster_damage = 15;
    game->rooms[6].monster_type = 2;
    game->rooms[6].item_count = 1;
    strcpy(game->rooms[6].items[0], "healing_potion");

    // Room 7 (Bottom-center): Empty
    strcpy(game->rooms[7].description, "A quiet and empty room.");
    game->rooms[7].item_count = 0;
    game->rooms[7].monster_type = 0;

    // Room 8 (Bottom-right): Hollow, Axe
    strcpy(game->rooms[8].description, "You encounter a Hollow!");
    game->rooms[8].monster_health = 45;
    game->rooms[8].monster_damage = 5;
    game->rooms[8].monster_type = 6;
    game->rooms[8].item_count = 1;
    strcpy(game->rooms[8].items[0], "axe");

    printf("Game initialized.\n");
}

// Look around the current room
void look(Game *game) {
    printf("Room: %s\n", game->rooms[game->current_room].description);
    printf("Items in the room:\n");
    for (int i = 0; i < game->rooms[game->current_room].item_count; i++) {
        printf("- %s\n", game->rooms[game->current_room].items[i]);
    }
    handle_monster(game);
}

// Move to a different room
void move(Game *game, const char *direction) {
    int next_room = game->current_room;

    if (strcmp(direction, "up") == 0 && game->current_room >= 3) {
        next_room -= 3; // Move up
    } else if (strcmp(direction, "down") == 0 && game->current_room <= 5) {
        next_room += 3; // Move down
    } else if (strcmp(direction, "left") == 0 && game->current_room % 3 != 0) {
        next_room -= 1; // Move left
    } else if (strcmp(direction, "right") == 0 && game->current_room % 3 != 2) {
        next_room += 1; // Move right
    } else {
        printf("Can't move in that direction.\n");
        return;
    }

    game->current_room = next_room;
    look(game);
}

// Pickup an item from the room
void pickup(Game *game, const char *item) {
    Room *room = &game->rooms[game->current_room];

    // Check if the item is in the room
    for (int i = 0; i < room->item_count; i++) {
        if (strcmp(room->items[i], item) == 0) {
            if (game->inventory_count < INVENTORY_SIZE) {
                strcpy(game->inventory[game->inventory_count], item);
                game->inventory_count++;
                printf("You picked up: %s\n", item);

                // Remove the item from the room
                for (int j = i; j < room->item_count - 1; j++) {
                    strcpy(room->items[j], room->items[j + 1]);
                }
                room->item_count--;
                return;
            } else {
                printf("Inventory is full!\n");
                return;
            }
        }
    }
    printf("Item not found in this room.\n");
}

// Drop an item from the inventory
void drop(Game *game, const char *item) {
    Room *room = &game->rooms[game->current_room];

    // Check if the item is in the inventory
    for (int i = 0; i < game->inventory_count; i++) {
        if (strcmp(game->inventory[i], item) == 0) {
            printf("You dropped: %s\n", item);

            // Remove the item from the inventory
            for (int j = i; j < game->inventory_count - 1; j++) {
                strcpy(game->inventory[j], game->inventory[j + 1]);
            }
            game->inventory_count--;

            // Add the item to the room
            strcpy(room->items[room->item_count], item);
            room->item_count++;
            return;
        }
    }
    printf("You don't have that item in your inventory.\n");
}

// Show the player's inventory
void show_inventory(Game *game) {
    printf("Your inventory:\n");
    for (int i = 0; i < game->inventory_count; i++) {
        printf("- %s\n", game->inventory[i]);
    }
}

// Attack the monster in the current room
// Attack the monster in the current room
void attack(Game *game) {
    Room *room = &game->rooms[game->current_room];

    if (room->monster_type == 0) {
        printf("There's no monster to attack in this room.\n");
        return;
    }

    printf("You attack the monster!\n");
    room->monster_health -= game->player_damage;

    // Check if the player is fighting the Dragon
    if (room->monster_type == 3) { // Dragon
        printf("The Dragon attacks you!\n");
        game->player_health -= room->monster_damage; // Dragon deals damage to player
        printf("You have %d health left.\n", game->player_health);
    }

    if (room->monster_health <= 0) {
        printf("You defeated the monster!\n");
        room->monster_type = 0; // Monster is defeated
        if (room->monster_type == 3) { // If it's the Dragon
            printf("You defeated the Dragon! You win!\n");
            exit(0);  // Exit the game
        }
    } else {
        printf("The monster has %d health left.\n", room->monster_health);
    }

    // If health is zero, the player loses
    if (game->player_health <= 0) {
        game_over(game);
    }
}
// Handle monster encounter based on room type
void handle_monster(Game *game) {
    Room *room = &game->rooms[game->current_room];

    if (room->monster_type == 1) { // Goblin
        printf("You encounter a Goblin!\n");
    } else if (room->monster_type == 2) { // Witch
        printf("You encounter a Witch!\n");
    } else if (room->monster_type == 3) { // Dragon
        printf("You encounter a Dragon!\n");
    } else if (room->monster_type == 4) { // Taurus Demon
        printf("You encounter the Taurus Demon!\n");
    } else if (room->monster_type == 5) { // Orc
        printf("You encounter an Orc!\n");
    } else if (room->monster_type == 6) { // Hollow
        printf("You encounter a Hollow!\n");
    }
}

// End the game if player loses
void game_over(Game *game) {
    printf("You have been defeated! Game Over.\n");
    exit(0);
}
