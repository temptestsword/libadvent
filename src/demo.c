#include "../lib/libadvent.c"

// --- Global Definitions --- //


int playerHealth = 80;
int playerAttack = 15;
char playerName[20] = "";

Item* g_inventory = NULL;  // Linked-list inventory root
Player player = {"player", &g_inventory, 80, 15};

Quest questList[] = {
    {"Speak to the Elder", "Visit the village elder to learn more.", true},
    {"Collect Herbs", "Gather 5 healing herbs in the forest.", false},
    {"Find the Sword", "Retrieve the ancient sword from the cave.", false}
};

int numberOfQuests = 3;


// --- Function Prototypes --- //

void gameLoop();

// --- Main --- //

int main() {
    printColor("Enter your name, adventurer: ", adv_grey);
    getstring(player.name, strlen(player.name));

    printColor("Ahh, welcome %s\n", player.name);
    gameLoop();

    printColor("\nGoodbye!\n", adv_grey);
    return 0;
}



//  GAME LOOP
void gameLoop() {
    int running = 1;

    while (running) {
        sys_clear();
        printColor("--- Demo - MAIN MENU ---\n", adv_cyan);
        printColor("1. Start\n", adv_green);
        printf("2. Inventory\n");
        printf("3. Quests\n");
        printf("0. Quit\n\n");

        printf("Choice: ");
        char choice = getchar();
        clearInputBuffer(); // Avoid a string passing as a char

        // Validate the choice
        if (choice < '0' || choice > '3') {
            printf("Invalid choice. Please enter a number between 0 and 6.\n");
            sys_sleep(1);
            continue;  // Retry input
        }

        switch (choice) {
            case '1': {
                printColor("Hello, adventurer!\n", adv_grey);
                ui_wait();
                // Start game logic or encounter here
                // You can implement various encounters with NPCs, battles, etc.
                break;
            }
            case '2': {
                sys_clear();
                printColor("---- Inventory ----\n", adv_yellow);
                displayInventory(player.inventory);
                ui_wait();
                break;
            }
            case '3': {
                sys_clear();
                displayQuests(questList, numberOfQuests, 0, numberOfQuests - 1);
                break;
            }
            case '0':
                running = 0;
                break;
        }
    }

    // Cleanup
    freeInventory(player.inventory);
}
