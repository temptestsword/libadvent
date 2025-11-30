#ifndef LIBADVENT_H_INCLUDED
#define LIBADVENT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define sys_sleep(seconds) Sleep(seconds * 1000)
    #define sys_clear() system("cls")
#elif defined(__APPLE__) || defined(__linux__)
    #include <unistd.h>
    #define sys_sleep(seconds) sleep(seconds)
    #define sys_clear() system("clear")
#endif

// Item structure for inventory management
typedef struct Item {
    char name[50];
    struct Item* next;
} Item;

// Quest structure for quests management
typedef struct Quest {
    char name[50];
    char description[200];
    bool completed;
} Quest;

// Entity structure for non-player characters
typedef struct Entity {
    char name[50];
    char dropitem[50];
    int health;
    int damage;
    bool isPassive;
} Entity;

// Player structure with inventory and stats
typedef struct Player {
    char name[20];
    Item** inventory; // A pointer to a pointer of items
    int health;
    int attack;
} Player;

// FUNCTION PROTOTYPES
static void displayQuests(const Quest* quests, int questCount, int start, int end);
static Item* createItem(const char* name);
static void addItem(Item** inventory, const char* name);
static void removeItem(Item** inventory, const char* name);
static void displayInventory(Item** inventory);
static bool isItemInInventory(Item** inventory, const char* itemName);
static void freeInventory(Item** inventory);
static void clearInputBuffer();
static void getstring(char* variable, int sizeofvariable);

// --------- Quest Management --------- //
static void displayQuests(const Quest* quests, int questCount, int start, int end) {
    if (start < 0 || end >= questCount || start > end) {
        printf("Invalid quest range.\n");
        return;
    }

    printf("=== Quests ===\n");
    for (int i = start; i <= end; i++) {
        printf("Quest #%d: %s\n", i + 1, quests[i].name);
        printf("  Status: %s\n", quests[i].completed ? "Completed" : "In Progress");
        printf("  Description: %s\n\n", quests[i].description);
    }

    printf("Press Enter to return to the main menu.\n");
    getchar(); // Wait for user input to return
}

// --------- Inventory Management --------- //

static Item* createItem(const char* name) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    if (!newItem) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    snprintf(newItem->name, sizeof(newItem->name), "%s", name);  // Safer way to copy string
    newItem->next = NULL;
    return newItem;
}

// Modified to accept player's inventory
static void addItem(Item** inventory, const char* name) {
    Item* newItem = createItem(name);
    if (newItem) {
        newItem->next = *inventory;  // Add to the beginning of the list
        *inventory = newItem;
    }
}

// Modified to accept player's inventory
static void removeItem(Item** inventory, const char* name) {
    Item* current = *inventory;
    Item* prev = NULL;

    while (current && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }

    if (current) {
        if (prev) {
            prev->next = current->next;
        } else {
            *inventory = current->next;
        }
        free(current);
    } else {
        printf("Item not found: %s\n", name);
    }
}

// Modified to accept player's inventory
static void displayInventory(Item** inventory) {
    if (!*inventory) {
        printf("Inventory is empty.\n");
        return;
    }

    printf("Inventory:\n");
    Item* current = *inventory;
    while (current) {
        printf("> %s\n", current->name);
        current = current->next;
    }
}


// Modified to accept player's inventory
static bool isItemInInventory(Item** inventory, const char* itemName) {
    const Item* current = (*inventory);
    while (current) {
        if (strcmp(current->name, itemName) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Modified to accept player's inventory
static void freeInventory(Item** inventory) {
    Item* current = *inventory;
    Item* nextItem;
    while (current) {
        nextItem = current->next;
        free(current);
        current = nextItem;
    }
    *inventory = NULL;
}

// --------- Input/Output Utils --------- //

static void clearInputBuffer() {
    while (getchar() != '\n');  // Clear the input buffer
}

static void getstring(char* variable, int sizeofvariable) {
    if (fgets(variable, sizeofvariable, stdin)) {
        size_t len = strlen(variable);
        if (len > 0 && variable[len - 1] == '\n') {
            variable[len - 1] = '\0';
        }
    } else {
        strcpy(variable, "\0");
        exit(EXIT_FAILURE);
    }
}

// --------- Pretty Printing --------- //

static void printColor(const char* msg, const char* colorCode) {
    printf("%s%s\033[0m", colorCode, msg);
}

static void dialoguebox(const char* name, const char* msg, const char* color) {
    static const char* colorCodes[] = {
        "cyan", "\033[1;36m", 
        "yellow", "\033[1;33m",
        "magenta", "\033[1;35m",
        "grey", "\033[1;90m", 
        "green", "\033[1;92m", 
        "blue", "\033[1;34m", 
        "red", "\033[1;91m"
    };

    for (int i = 0; i < sizeof(colorCodes)/sizeof(colorCodes[0]); i+=2) {
        if (strcmp(color, colorCodes[i]) == 0) {
            printColor(colorCodes[i+1], name);
            printf(" >> %s", msg);
            return;
        }
    }

    printf("Invalid color. Supported colors: cyan, yellow, lightyellow, magenta, grey, green, blue, red.\n");
}

#endif