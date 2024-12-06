#include "../header/Game.h"
#include "../header/SaveGame.h"
#include "../header/GameState.h"
#include "../header/LoadGame.h"
#include "../header/combat.h"
#include <bits/stdc++.h>
#include <sstream>

using std::cout, std::cin, std::endl, std::string;

void Game::startGame() {
    string saveFileName = "savegame.txt";
    string playerCommand; // This is a repeatedly used variable for the player's commands

    cout << "Game starting!" << endl; // Placeholder

    cout << "Please enter the name for your player character: ";
    string playerName;
    cin >> playerName;
    Character playerCharacter (playerName);

    // Giving player a default weapon
    int playerWeaponTypeInt; // We use an integer to input the player's weapon type, since that makes input validation easier
    Weapon::WeaponType playerWeaponType;
    cout << "What type of weapon would you like?" << endl
    << "Sword (1)" << endl
    << "Staff (2)" << endl
    << "Bow (3)" << endl
    << "Please enter A NUMBER: " << endl;
    cin >> playerWeaponTypeInt;
    while (playerWeaponType != 1 && playerWeaponType != 2 && playerWeaponType != 3) {
        cout << "Please enter a valid number: ";
        cin >> playerWeaponTypeInt;
        cout << endl;
    }

    if (playerWeaponTypeInt == 1) {
        playerWeaponType = Weapon::WeaponType::Sword;
        playerCharacter.setAttackType(AttackType::Melee);
    }
    else if (playerWeaponTypeInt == 2) {
        playerWeaponType = Weapon::WeaponType::Staff;
        playerCharacter.setAttackType(AttackType::Ranged);
    }
    else {
        playerWeaponType = Weapon::WeaponType::Bow;
        playerCharacter.setAttackType(AttackType::Ranged);
    }
    
    Weapon* defaultWeapon = new Weapon(ItemType::WEAPON, "bronze sword", "player's default weapon", 10, playerWeaponType);
    playerCharacter.equipWeapon(defaultWeapon);

    Map gameMap(playerWeaponType);

    while (playerCommand != "quit") {

        cout << "You're currently in room " << gameMap.getPlayerIndex() << endl;

        cout << "Choose from the following (Enter one word): " << endl
        << "move (up/down/left/right) - Move across the map" << endl
        << "pickup (potion, weapon, armour) - Pickup the item from the current room, add it to your inventory" << endl
        << "use (potion) - Use a potion from your inventory" << endl
        << "equip (item name) - Equip the weapon or armour in your inventory" << endl
        << "print inventory - Print inventory" << endl
        << "sort (alphabetically, time) - Sort inventory items by name, or time collected" << endl
        << "throw (item name) - Throw item out of inventory" << endl
        << "save, Save the game to savegame.txt" << endl
        << "quit, End the program" << endl;

        std::transform(playerCommand.begin(), playerCommand.end(), playerCommand.begin(), ::tolower); // Now we only need one if condition

        if (playerCommand == "move") {
            string movementDirection;
            cout << "What direction would you like to move in (up/down/left/right)?" << endl << "Please enter a direction: ";
            cin >> movementDirection;
            cout << endl;
            while (!gameMap.changeRoomBasedOnDirection(movementDirection)) { // Run while false
                cout << "Enter a valid direction: ";
                cin >> movementDirection;
                cout << endl;
            }
            cout << "Moved to room " << gameMap.getPlayerIndex() << endl;

            // HERE IS WHERE WE INITIATE COMBAT
            // THE ONLY TIME WHEN WE START A BATTLE IS AFTER WE MOVE ROOMS
            // IT BELONGS IN THE "MOVE" SECTION, I PROMISE!!!!!!!

            if (gameMap.roomHasEnemies(gameMap.getPlayerIndex())) {
                cout << "Enemies encountered! Battle initiating." << endl;
                vector<Character*> fighters;
                fighters.push_back(&playerCharacter);
                vector <Character*> enemyFighters = gameMap.returnEnemiesInRoom(gameMap.getPlayerIndex());
                fighters.insert(fighters.end(), enemyFighters.begin(), enemyFighters.end());
                Combat battle(fighters);
                battle.startBattle();
                
                if (!playerCharacter.isAlive()) {
                    cout << playerCharacter.getCharacterName() << " is dead!" << endl;
                    cout << "Ending game..........." << endl;
                    return;
                }
            }

        }

        if (playerCommand == "pickup") {
            string typeOfItem;
            cout << "Pickup potion, weapon, or armour?" << endl << "Enter option: ";
            cin >> typeOfItem;
            cout << endl;

            for (unsigned i; i < typeOfItem.size(); i++) {
                std::transform(typeOfItem.begin(), typeOfItem.end(), typeOfItem.begin(), ::tolower); // Now we only need one if condition
            }
            while (typeOfItem != "potion" && typeOfItem != "weapon" && typeOfItem != "armour") {
                cout << "Please enter a valid item type (potion, weapon, armour)";
                cin >> typeOfItem;
                cout << endl;
            }

            if (typeOfItem == "potion") {
                playerCharacter.pickUpItem()
            }
        }
        string itemToThrowAway;
        cin >> itemToThrowAway;
        playerCharacter.throwAwayItem(itemToThrowAway);
    }

    cout << "Save game? (0 for no, 1 for yes)" << endl << "Please enter: ";

    int saveGame;
    cin >> saveGame;
    while (saveGame != 0 && saveGame != 1) {
        cout << "Please enter a valid number: ";
        cin >> saveGame;
        cout << endl;
    }
    

    // Once player moves to new Room (down or right), start a battle if there are enemies
    // If there are items, offer to move them into storage
    // If the player enters "save", call the save function
    // If the player enters "quit", offer to save or not with "yes" or "no", and end the startGame function
    // save, equip, use, move, pickup

    // For every 100 experience, call increase storage capacity, and increase damage and health by 10
    // throw [itemname] for throwing away item
    // "print inventory" for printing inventory
    // sort [method] for sorting inventory
}

Game::~Game() {

}

// Serialize the game state into a string
string Game::serialize() const {
    std::ostringstream oss;
    oss << character.serialize() << "\n"
        << map.serialize() << "\n"
        << inventory.serialize();
    return oss.str();
}

// Deserialize the game state from a string
bool Game::deserialize(const string& data) {
    std::istringstream iss(data);
    string charData, mapData, invData;

    if (!std::getline(iss, charData) || 
        !std::getline(iss, mapData) ||
        !std::getline(iss, invData)) {
        return false;
    }

    return character.deserialize(charData) &&
           map.deserialize(mapData) &&
           inventory.deserialize(invData);
}
