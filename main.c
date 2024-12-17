#include <stdio.h>
#include <string.h>
#include "game.h"
#include "file_io.h"

void print_help(const char* command) {
    if (strcmp(command, "look") == 0) {
        printf("look: Describes your surroundings.\n");
    } else if (strcmp(command, "move") == 0) {
        printf("move [up/down/left/right]: Move in a specified direction.\n");
    } else if (strcmp(command, "pickup") == 0) {
        printf("pickup [item]: Pick up an item.\n");
    } else if (strcmp(command, "drop") == 0) {
        printf("drop [item]: Drop an item from your inventory.\n");
    } else if (strcmp(command, "attack") == 0) {
        printf("attack: Attack an enemy.\n");
    } else if (strcmp(command, "inventory") == 0) {
        printf("inventory: Display your current inventory.\n");
    } else if (strcmp(command, "save") == 0) {
        printf("save [name]: Save your game with the specified name.\n");
    } else if (strcmp(command, "load") == 0) {
        printf("load [name]: Load a previously saved game by name.\n");
    } else if (strcmp(command, "list") == 0) {
        printf("list: List all available saved games.\n");
    } else if (strcmp(command, "quit") == 0) {
        printf("quit: Exit the game.\n");
    } else {
        printf("Unknown command.\n");
    }
}

int main() {
    Game game;
    char command[50];
    char argument[50];

    initialize_game(&game);
    printf("Welcome! Commands: look, move [up/down/left/right], pickup [item], drop [item], attack, inventory, save [name], load [name], list, quit, help [command]\n");

    while (1) {
        printf("\nCommand: ");
        scanf("%s", command);

        // Help command
        if (strcmp(command, "help") == 0) {
            scanf("%s", argument);
            print_help(argument);
        }
        // Look command
        else if (strcmp(command, "look") == 0) {
            look(&game);
        }
        // Move command
        else if (strcmp(command, "move") == 0) {
            scanf("%s", argument);
            move(&game, argument);
        }
        // Pickup command
        else if (strcmp(command, "pickup") == 0) {
            scanf("%s", argument);
            pickup(&game, argument);
        }
        // Drop command
        else if (strcmp(command, "drop") == 0) {
            scanf("%s", argument);
            drop(&game, argument);
        }
        // Attack command
        else if (strcmp(command, "attack") == 0) {
            attack(&game);
            // Check if dragon is defeated
            if (game.player_health <= 0) {
                printf("You defeated the dragon! You win!\n");
                break;  // Exit the game
            }
        }
        // Inventory command
        else if (strcmp(command, "inventory") == 0) {
            show_inventory(&game);
        }
        // Save command
        else if (strcmp(command, "save") == 0) {
            scanf("%s", argument);
            save_game(argument, &game);
        }
        // Load command
        else if (strcmp(command, "load") == 0) {
            scanf("%s", argument);
            load_game(argument, &game);
        }
        // List saves command
        else if (strcmp(command, "list") == 0) {
            list_saves();
        }
        // Quit command
        else if (strcmp(command, "quit") == 0) {
            printf("Exiting game...\n");
            break;
        }
        // Unknown command
        else {
            printf("Unknown command.\n");
        }
    }

    return 0;
}
