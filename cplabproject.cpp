#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cctype>
#include <algorithm>
using namespace std;

struct Player {
    string name;
    string playerClass;
    int originalHealth;
    int health;
    int experience;
    int level;
};

void CharacterInfo(const Player& player) {
    cout << "\nCharacter Info " << endl;
    cout << "Name: " << player.name << endl;
    cout << "Class: " << player.playerClass << endl;
    cout << "Health: " << player.originalHealth << endl;
    cout << "Experience Points: " << player.experience << endl;
    cout << "Level: " << player.level << endl;
    cout << endl;
}

int getUserInput() {
    int userInput;
    while (true) {
        cout << "Enter your choice: ";
        cin >> userInput;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a number.\n" << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    return userInput;
}

string chooseClass() {
    string chosenClass;
    while (true) {
        cout << "Choose a class; Warrior, Mage, Rogue (1-3): ";
        cin >> chosenClass;

        transform(chosenClass.begin(), chosenClass.end(), chosenClass.begin(), ::tolower);

        if (chosenClass == "warrior" || chosenClass == "1") {
            chosenClass = "Warrior";
            break;
        }
        else if (chosenClass == "mage" || chosenClass == "2") {
            chosenClass = "Mage";
            break;
        }
        else if (chosenClass == "rogue" || chosenClass == "3") {
            chosenClass = "Rogue";
            break;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid class. Please choose Warrior, Mage, Rogue (1-3)\n" << endl;
        }
    }

    return chosenClass;
}

string CorrectCharacterName() {
    string playerName;
    while (true) {
        cout << "Enter your character's name: ";
        cin >> playerName;

        if (playerName.length() >= 4 && playerName.length() <= 10 &&
            count_if(playerName.begin(), playerName.end(), [](char c) { return isalpha(c); }) >= 4 &&
            all_of(playerName.begin(), playerName.end(), [](char c) { return isalnum(c); })) {
            break;
        }
        else {
            cout << "\nInvalid name. Please enter a name with 4-10 characters (at least 4 alphabets, only alphabets and numbers)\n" << endl;
        }
    }

    return playerName;
}

int QuestSelection() {
    cout << "\n                                                                -------- Quest Options ---------\n" << endl;
    cout << "1. Easy Quest (Enemies: Goblins)" << endl;
    cout << "2. Medium Quest (Enemies: Orcs)" << endl;
    cout << "3. Hard Quest (Enemies: Dragons)" << endl;

    int questChoice;
    while (true) {
        questChoice = getUserInput();

        if (questChoice >= 1 && questChoice <= 3) {
            break;
        }
        else {
            cout << "\nInvalid choice. Please enter a number between 1 and 3.\n" << endl;
        }
    }

    return questChoice;
}

bool battle(int& playerHealth, int questDifficulty, const string& enemyType) {
    int enemyHealth = rand() % 51 + 50 * questDifficulty;

    while (playerHealth > 0 && enemyHealth > 0) {
        cout << "\n                                                               -------- Battle Options ---------\n" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Defend" << endl;
        cout << "3. Flee" << endl;

        int battleChoice;
        while (true) {
            battleChoice = getUserInput();

            if (battleChoice >= 1 && battleChoice <= 3) {
                break;
            }
            else {
                cout << "\nInvalid choice. Please enter a number between 1 and 3.\n" << endl;
            }
        }

        switch (battleChoice) {
        case 1: {
            int playerAttack = rand() % 11 + 10;
            int enemyAttack = rand() % 11 + 5;

            cout << "\nYou attack the " << enemyType << " and deal " << playerAttack << " damage." << endl;
            enemyHealth -= playerAttack;
            break;
        }
        case 2: {
            int playerDefense = rand() % 6 + 5;
            int enemyAttack = rand() % 11 + 5;

            cout << "\nYou defend against the " << enemyType << " and reduce incoming damage." << endl;
            playerHealth -= max(0, enemyAttack - playerDefense);
            break;
        }
        case 3: {
            cout << "\nYou attempt to flee from the " << enemyType << "." << endl;
            if (rand() % 2 == 0) {
                cout << "You successfully fled from the battle." << endl;
                return true;
            }
            else {
                cout << "Flee attempt failed. You must face the " << enemyType << " again.\n" << endl;
                break;
            }
        }
        default:
            break;
        }

        if (enemyHealth <= 0) {
            cout << "You defeated the " << enemyType << "!" << endl;
            return true;
        }

        int enemyAttack = rand() % 11 + 5;
        playerHealth -= max(0, enemyAttack);

        cout << "Your health: " << (playerHealth < 0 ? 0 : playerHealth) << endl;
        cout << "Enemy " << enemyType << " health: " << enemyHealth << endl;

        if (playerHealth <= 0) {
            cout << "You were defeated by the " << enemyType << "." << endl;
            return false;
        }
    }

    return true;
}

void levelUp(int& playerExperience, int& playerLevel, int& playerHealth) {
    if (playerExperience >= 100) {
        playerLevel++;
        playerHealth = 100;
        playerExperience = 0;
        cout << "\nCongratulations! You leveled up!" << endl;
    }
}

void Storyline(int& playerExperience, int questChoice) {
    if (questChoice == 1) {
        cout << "\nYou engage in an easy quest to defeat Goblins." << endl;
        playerExperience += 30;
    }
    else if (questChoice == 2) {
        cout << "\nYou engage in a medium quest to face Orcs." << endl;
        playerExperience += 50;
    }
    else if (questChoice == 3) {
        cout << "\nYou engage in a hard quest to confront Dragons." << endl;
        playerExperience += 80;
    }
}

void gameLoop() {
    cout << "\n                                                         --------- Welcome to The Veil of Dreams! ---------\n" << endl;

    while (true) {
        string playerName = CorrectCharacterName();
        string playerClass = chooseClass();

        int playerHealth = 100;
        int playerExperience = 0;
        int playerLevel = 1;

        while (true) {
            CharacterInfo({ playerName, playerClass, 100, playerHealth, playerExperience, playerLevel });
            int questChoice = QuestSelection();

            string enemyType;
            if (questChoice == 1) {
                enemyType = "Goblins";
            }
            else if (questChoice == 2) {
                enemyType = "Orcs";
            }
            else if (questChoice == 3) {
                enemyType = "Dragons";
            }

            Storyline(playerExperience, questChoice);

            playerHealth = 100;

            if (!battle(playerHealth, questChoice, enemyType)) {
                cout << "You can try again!" << endl;
            }

            levelUp(playerExperience, playerLevel, playerHealth);

            string QuestAgain;
            while (true) {
                cout << "\nDo you want to choose another quest? (yes/no): ";
                cin >> QuestAgain;

                transform(QuestAgain.begin(), QuestAgain.end(), QuestAgain.begin(), ::tolower);

                if (QuestAgain == "yes" || QuestAgain == "no") {
                    break;
                }
                else {
                    cout << "\nInvalid choice. Please enter 'yes' or 'no'.\n" << endl;
                }
            }

            if (QuestAgain != "yes") {
                cout << "\nThanks for playing!" << endl;
                break;
            }
        }

        string playAgain;
        while (true) {
            cout << "\nDo you want to play again? (yes/no): ";
            cin >> playAgain;

            transform(playAgain.begin(), playAgain.end(), playAgain.begin(), ::tolower);

            if (playAgain == "yes" || playAgain == "no") {
                break;
            }
            else {
                cout << "\nInvalid choice. Please enter 'yes' or 'no'.\n" << endl;
            }
        }

        if (playAgain != "yes") {
            cout << "\nThanks for playing! See you next time." << endl;
            break;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    gameLoop();

    return 0;
}