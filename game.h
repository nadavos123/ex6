#ifndef GAME_H
#define GAME_H

#define SIZE_FINAL_CHAR  1

#define VISITED 1
#define NOT_VISITED 0

#include "bst.h"

typedef enum { ARMOR, SWORD } ItemType;
typedef enum { PHANTOM, SPIDER, DEMON, GOLEM, COBRA } MonsterType;
typedef enum { UP=-1, DOWN=1, LEFT=-1, RIGHT=1} Directions;
typedef enum { MOVE, FIGHT, PICKUP, BAG, DEFEATED, QUIT} PlayerAction;


typedef struct Item {
    char* name;
    ItemType type;
    int value;
} Item;

typedef struct Monster {
    char* name;
    MonsterType type;
    int hp;
    int maxHp;
    int attack;
} Monster;

typedef struct Room {
    int id;
    int x, y;
    int visited;
    Monster* monster;
    Item* item;
    struct Room* next;
} Room;

typedef struct Player {
    int hp;
    int maxHp;
    int baseAttack;
    BST* bag;
    BST* defeatedMonsters;
    Room* currentRoom;
} Player;

typedef struct {
    Room* rooms;
    Player* player;
    int roomCount;
    int configMaxHp;
    int configBaseAttack;
} GameState;

// Print functions
static void displayMap(GameState* g);
static void printRoomLegend(GameState *g);

// Monster functions
void freeMonster(void* m);
int compareMonsters(void* a, void* b);
void printMonster(void* data);

// Item functions
void freeItem(void* i);
int compareItems(void* a, void* b);
void printItem(void* data);

// Game functions
void addRoom(GameState* g);
void initPlayer(GameState* g);
void playGame(GameState* g);
void freeGame(GameState* g);
int checkVictory(GameState* g);

// Play functions
Room* move(GameState *g, Room *r);
int fight(GameState *g, Room *r);
int damgeMonster(GameState *g, Monster *m);
int damagePlayer(GameState *g, Monster *m);
void pickup(GameState *g, Room *r);
void bag(GameState *g);
void defeated(GameState *g);

// Room functions
Room* findRoomById(GameState* g, int id);
Room* findRoomByCoordinates(GameState *g, int x, int y);

int compareInt(int a, int b);
#endif
