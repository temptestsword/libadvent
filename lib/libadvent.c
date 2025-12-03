#include "../lib/libadvent.h"


// --- Simple definitions --- //

const char* adv_cyan = "\033[1;36m";
const char* adv_yellow = "\033[1;33m";
const char* adv_magenta = "\033[1;35m";
const char* adv_grey = "\033[1;90m";
const char* adv_green = "\033[1;92m"; 
const char* adv_blue = "\033[1;34m";
const char* adv_red = "\033[1;91m";


// Simple UI pause
inline void ui_wait() {
    printf("\nPress Enter to continue..."); getchar();
}

void combatscene(Player player, Entity enemy) {
    sys_clear();
    printf("You encounter a %s!\n", enemy.name);

    bool ranAway = false;

    while (enemy.health > 0 && player.health > 0 && ranAway == false) {
        printf("\nYour Health: %d | %s's Health: %d\n", player.health, enemy.name, enemy.health);
        printf("1. Attack\n");
        printf("2. Use Potion\n");
        printColor("3. Run\n", adv_grey);
        printColor("Choose your action: ", adv_blue);
        
        char action[10];
        getstring(action, 10);

        if (strcmp(action, "1") == 0) {
            enemy.health -= player.attack;
            printf("You attack the %s for %d damage!\n", enemy.name, player.attack);
        } else if (strcmp(action, "2") == 0 && isItemInInventory(player.inventory, "Healing Potion")) {
            player.health += 10;
            removeItem(player.inventory, "Healing Potion");
            printf("You used a Healing Potion! Your health is now %d.\n", player.health);
        } else if (strcmp(action, "3") == 0) {
            if (enemy.isPassive == true){
                printf("You successfully ran away!");
                ranAway = true;
            } else {
                printf("The enemy locked you in the arena..");
            }
        } else {
            printf("Invalid action or no potions left!\n");
        }

        // Entity retaliates
        if (enemy.health > 0 && ranAway == false) {
            player.health -= enemy.damage;
            printf("The %s attacks you for %d damage!\n", enemy.name, enemy.damage);
            sys_sleep(1); sys_clear();
        }

        sys_sleep(1);
    }

    if (player.health <= 0) {
        printf("You have been defeated!\n");
        clearInputBuffer();
        ui_wait();
        sys_clear();
    } else if (ranAway == true) {
        sys_sleep(1);
        sys_clear();
    } else {
        printf("You defeated the %s!\n", enemy.name);
        clearInputBuffer();
        ui_wait();
        sys_clear();
    }
}

//useless restrict but it looks cool lol
bool boolConfirmAction(const char* restrict text) {
    printf("\n %s (yes/no): ", text);
    char choice[10];
    getstring(choice, sizeof(choice));

    if (strcmp(choice, "yes") == 0) {
        return true;
    } else {
        return false;
    };
}


void interactWithNPC(Player player, const char* npcName, const char* item, const char* color) {
    sys_clear();
    char response[200];
    char message[200];

    snprintf(message, sizeof(message), "Hello %s! Take this..\n", player.name);  // Construct the message with the item name
    dialoguebox(message, npcName, color);
    sys_sleep(1);
    
    snprintf(message, sizeof(message), "Would you like to take the %s?\n", item);  // Construct the message with the item name for the next dialogue
    dialoguebox(message, npcName, color);
    
    printf("\nAccept this item? (yes/no): ");
    getstring(response, 200);

    if (strcmp(response, "yes") == 0 || strcmp(response, "y")) {
        addItem(player.inventory, item);
        printf("\n"); //the addItem() prints that item which you got, so we add \n to skip to next line
        sys_sleep(1);
        sys_clear();
    } else {
        dialoguebox("Maybe next time.\n", npcName, color);
        sys_sleep(1);
        sys_clear();
    }
}