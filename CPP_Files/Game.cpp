#include "../header/Game.h"
#include <sstream>

void Game::startGame() {
    std::string playerCommand; // This is a repeatedly used variable for the player's commands

    std::cout << "Game starting!" << std::endl; // Placeholder

    std::cout << "Please enter the name for your player character: ";
    std::string playerName;
    std::cin >> playerName;
    Character playerCharacter (playerName);

    // Giving player a default weapon
    int playerWeaponTypeInt; // We use an integer to input the player's weapon type, since that makes input validation easier
    Weapon::WeaponType playerWeaponType;
    std::cout << "What type of weapon would you like?" << std::endl
    << "Sword (1)" << std::endl
    << "Staff (2)" << std::endl
    << "Bow (3)" << std::endl
    << "Please enter A NUMBER: " << std::endl;
    std::cin >> playerWeaponTypeInt;
    while (playerWeaponType != 1 && playerWeaponType != 2 && playerWeaponType != 3) {
        std::cout << "Please enter a valid number: ";
        std::cin >> playerWeaponTypeInt;
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

    }

    std::cout << "Save game? (0 for no, 1 for yes)" << std::endl << "Please enter: ";

    int saveGame;
    cin >> saveGame;
    while (saveGame != 1 && saveGame != 2) {
        cin >> 

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
std::string Game::serialize() const {
    std::ostringstream oss;
    oss << character.serialize() << "\n"
        << map.serialize() << "\n"
        << inventory.serialize();
    return oss.str();
}

// Deserialize the game state from a string
bool Game::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string charData, mapData, invData;

    if (!std::getline(iss, charData) || 
        !std::getline(iss, mapData) ||
        !std::getline(iss, invData)) {
        return false;
    }

    return character.deserialize(charData) &&
           map.deserialize(mapData) &&
           inventory.deserialize(invData);
}
