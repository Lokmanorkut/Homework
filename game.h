#ifndef GAME_H
#define GAME_H

#define MAX_ITEMS 10
#define INVENTORY_SIZE 10
#define ROOM_COUNT 9

// Room struct
typedef struct {
    char description[100];
    char items[MAX_ITEMS][50];
    int item_count;
    int monster_health;
    int monster_damage;
    int is_exit; // 1 if this room is an exit condition (lava or death)
    int monster_type; // 0 for none, 1 for goblin, 2 for witch, 3 for dragon, etc.
} Room;

// Game struct
typedef struct {
    Room rooms[ROOM_COUNT]; // 3x3 map, 9 rooms
    int current_room;
    int player_health;
    int player_damage;
    char inventory[INVENTORY_SIZE][50]; // Player's inventory
    int inventory_count;
} Game;

// Function declarations
void initialize_game(Game *game);
void look(Game *game);
void move(Game *game, const char *direction);
void pickup(Game *game, const char *item);
void drop(Game *game, const char *item);
void show_inventory(Game *game);
void attack(Game *game);
void handle_monster(Game *game);
void game_over(Game *game);

#endif // GAME_H
