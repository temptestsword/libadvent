#ifndef LIBADVENT_H_INCLUDED
#define LIBADVENT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define sys_sleep(seconds) fflush(stdout); Sleep(seconds * 1000)
    #define sys_clear() fflush(stdout); system("cls")
#elif defined(__APPLE__) || defined(__linux__)
    #include <unistd.h>
    #define sys_sleep(seconds) fflush(stdout); sleep(seconds)
    #define sys_clear() fflush(stdout); system("clear")
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
static void displayQuests(const Quest* quests, size_t questCount, size_t start, size_t end);
static Item* createItem(const char* name);
static void addItem(Item** inventory, const char* name);
static void removeItem(Item** inventory, const char* name);
static void displayInventory(Item** inventory);
static bool isItemInInventory(Item** inventory, const char* itemName);
static void freeInventory(Item** inventory);
static inline void clearInputBuffer();
static void getstring(char* variable, size_t sizeofvariable);

// --------- Quest Management --------- //
static void displayQuests(const Quest* quests, size_t questCount, size_t start, size_t end) {
    // start < 0 always returns false so removed it
    if (end >= questCount || start > end) {
        printf("Invalid quest range.\n");
        return;
    }

    printf("=== Quests ===\n");
    for (size_t i = start; i <= end; i++) {
        printf("Quest [%zu]: %s\n", i + 1, quests[i].name);
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

static void addItem(Item** inventory, const char* name) {
    Item* newItem = createItem(name);
    if (newItem) {
        newItem->next = *inventory;  // Add to the beginning of the list
        *inventory = newItem;
    }
}

static void removeItem(Item** inventory, const char* name) {
    Item* current = *inventory;
    Item* prev = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                *inventory = current->next;
            }
            free(current);
            return;  // Exit early after freeing the item
        }
        prev = current;
        current = current->next;
    }
    printf("Item not found: %s\n", name);
}

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

static inline void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);  // Clear the input buffer
}

static void getstring(char* variable, size_t sizeofvariable) {
    if (!(fgets(variable, sizeofvariable, stdin))) {
        fprintf(stderr, "Error: Failed to read input.\n");
        exit(EXIT_FAILURE);
    } else {
        clearInputBuffer();
        size_t len = strlen(variable);

        // Remove newline if present
        if (len > 0 && len < sizeofvariable && variable[len - 1] == '\n') {
            variable[len - 1] = '\0';
        }
    }
}

// --------- Pretty Printing --------- //

static void printColor(const char* msg, const char* colorCode) {
    printf("%s%s\033[0m", colorCode, msg);
}

static void dialoguebox(const char* msg, const char* name, const char* colorCode) {
    printf("%s%s >> \033[0m", colorCode, name);
    printf("%s", msg);
}

#endif