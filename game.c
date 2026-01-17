#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "utils.h"

void addRoom(GameState* g){
    Room *r;
    int monster, item;

    r=malloc(sizeof(Room));

    r->visited=NOT_VISITED;
    r->id=g->roomCount;
    r->monster=NULL;
    r->item=NULL;
    r->x=0;
    r->y=0;
    r->next=NULL;

    if(g->roomCount>0){
        int id, d, x, y, newX, newY;
        Room *attachedR;

        // Print the map and room legend
        displayMap(g);
        printRoomLegend(g);

        id=getInt("Attach to room ID: ");
        attachedR = findRoomById(g, id);
        d=getInt("Direction (0=Up,1=Down,2=Left,3=Right): ");
        x=attachedR->x;
        y=attachedR->y;
        
        if((d==UP)&&(findRoomByCoordinates(g,x,y-1)==NULL)){
            r->x=x;
            r->y=y-1;
            return;
        }
        else if((d==DOWN)&&(findRoomByCoordinates(g,x,y+1)==NULL)){
            r->x=x;
            r->y=y+1;
            return;
        }
        else if((d==LEFT)&&(findRoomByCoordinates(g,x-1,y)==NULL)){
            r->x=x-1;
            r->y=y;
            return;
        }
        else if((d==RIGHT)&&(findRoomByCoordinates(g,x+1,y)==NULL)){
            r->x=x+1;
            r->y=y;
            return;
        }
        else{
            printf("Room exists there\n");
            free(r);
        }
    }
    
    monster=getInt("Add monster? (1=Yes, 0=No): ");
    // Add monster
    if(monster){
        Monster *m;
        int type;
    
        m=malloc(sizeof(Monster));

        m->name=getString("Monster name: ");

        type=getInt("Type (0-4): ");
        m->type=(MonsterType)type;

        m->hp=getInt("HP: ");

        m->attack=getInt("Attack: ");

        r->monster=m;
    }

    item=getInt("Add item? (1=Yes, 0=No): ");
    // Add item
    if(item){
        Item *i;
        int type;

        i=malloc(sizeof(Item));

        i->name=getString("Item name: ");

        type=getInt("Type (0=Armor, 1=Sword): ");
        i->type=(ItemType)type;
        
        i->value=getInt("Value: ");
        r->item=i;
    }
    // Add the room to the begining of the linked list
    r->next=g->rooms;
    g->rooms=r;
    printf("Created room %d at (%d,%d)" ,r->id,r->x,r->y);
}


void initPlayer(GameState* g){
    Player *p; 

    if(g->roomCount==0){
        printf("Create rooms first\n");
        return;
    }
    if(g->player!=NULL){
        printf("Player exists\n");
        return;
    }

    p=malloc(sizeof(Player));

    p->maxHp=g->configMaxHp;
    p->hp=g->configMaxHp;   
    p->baseAttack=g->configBaseAttack;
    p->bag=malloc(sizeof(BSTNode));
    p->defeatedMonsters=malloc(sizeof(BSTNode));
    g->player=p;
}


void playGame(GameState* g){
    Room *r;

    if(g->player==NULL){
        printf("Init player first\n");
        return;
    }

    r=findRoomById(g, 0);
    while (1){
        displayMap(g);
        printRoomLegend(g);    
        printf("--- Room %d ---" ,r->id);
        r->visited=NOT_VISITED;
        if(r->monster!=NULL){
            printf("Monster: %s (HP:%d)\n" ,r->monster->name ,r->monster->hp);
        }
        if(r->item!=NULL){
            printf("Item: %s", r->item->name);
        }
        printf("HP: %d/%d\n");
        printf("1.Move 2.Fight 3.Pickup 4.Bag 5.Defeated 6.Quit\n");
        if(MOVE){
            Room *nextRoom = move(g, r);
            if(nextRoom!=NULL){
                r=nextRoom;
            }
            continue;
        }
        if(FIGHT){

        }
        PlayerActionFunc actions[] = {};
    }
}
/* Play functions */

Room *move(GameState *g, Room *r){

    if(r->monster!=NULL){
        printf("Kill monster first\n");
        return NULL;
    }

    int dx[] = {0, 0, LEFT, RIGHT};
    int dy[] = {UP, DOWN, 0, 0};
    int d=getInt("Direction (0=Up,1=Down,2=Left,3=Right):");
    if((d<0)||(d>3)){
        return NULL;
    }
    int newX = r->x+dx[d];
    int newY = r->y+dy[d];
    Room *nextRoom = findRoomByCoordinates(g, newX, newY);
    if(nextRoom==NULL){
        printf("No room there");
        return NULL;
    }
    return nextRoom;
}
int fight(GameState *g, Room *r){
    if(r->monster==NULL){    
        printf("No monster\n");
        return 0;
    }    
    while(r->monster->hp>0||g->player->hp>0){
        printf("")
    }
    
}
void bag(GameState *g){
    printf("=== INVENTORY ===");
    printf("1.Preorder 2.Inorder 3.Postorder");
    g->player->bag;
}

/* Room functions*/
Room* findRoomById(GameState *g, int id){   
    Room *r;
    r=g->rooms;
    while (r!=NULL){
        if(r->id==id){
            return(r);
        }
        r=r->next;
    }
    return NULL;
}
Room* findRoomByCoordinates(GameState *g, int x, int y){
    Room *r;
    r=g->rooms;
    while (r!=NULL){
        if((r->x==x)&&(r->y==y)){
            return(r);
        }
        r=r->next;
    }
    return NULL;
}    


/* Map display functions */
static void displayMap(GameState* g) {
    if (!g->rooms) return;
    
    // Find bounds
    int minX = 0, maxX = 0, minY = 0, maxY = 0;
    for (Room* r = g->rooms; r; r = r->next) {
        if (r->x < minX) minX = r->x;
        if (r->x > maxX) maxX = r->x;
        if (r->y < minY) minY = r->y;
        if (r->y > maxY) maxY = r->y;
    }
    
    int width = maxX - minX + 1;
    int height = maxY - minY + 1;
    
    // Create grid
    int** grid = malloc(height * sizeof(int*));
    for (int i = 0; i < height; i++) {
        grid[i] = malloc(width * sizeof(int));
        for (int j = 0; j < width; j++) grid[i][j] = -1;
    }
    
    for (Room* r = g->rooms; r; r = r->next)
        grid[r->y - minY][r->x - minX] = r->id;
    
    printf("=== SPATIAL MAP ===\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid[i][j] != -1) printf("[%2d]", grid[i][j]);
            else printf("    ");
        }
        printf("\n");
    }
    
    for (int i = 0; i < height; i++) free(grid[i]);
    free(grid);
}

static void printRoomLegend(GameState *g){
    printf("=== ROOM LEGEND ===\n");
    for (Room  *r = g->rooms; r; r = r->next){
        char monster, item;
        monster = r->monster!=NULL ? 'V':'X';
        item = r->item!=NULL ? 'V':'X';
        printf("ID %d: [M:%c] [I:%c]\n" ,r->id ,monster ,item);
    }
    printf("===================\n");
}
