#include "../header/Game.h"
#include "../header/combat.h"
#include <sstream>
#include <filesystem>
#include <limits>
#include <iostream>
#include <algorithm>

Game::Game()
    : currentState(GameState::MainMenu),
      player("Hero"),
      gameMap() // Default initialization for Map
{}

void Game::run() {
    while (currentState != GameState::GameOver) {
        switch (currentState) {
            case GameState::MainMenu:
                showMainMenu();
                break;
            case GameState::InGame:
                playGame();
                break;
            case GameState::GameOver:
                std::cout << "\nGame Over! Thanks for playing.\n";
                break;
        }
    }
}

void Game::newGame() {
    std::cout << "Starting a new game...\n";
    player = Character("Hero"); // Reset the player
    inventory = Inventory();    // Reset the inventory
    difficulty = Difficulty();  // Reset difficulty
    applyDifficulty();          // Apply difficulty modifiers

    // Allow the player to choose their weapon type
    std::cout << "Choose your weapon type (1 = Sword, 2 = Staff, 3 = Bow): ";
    int weaponChoice;
    std::cin >> weaponChoice;

    Weapon::WeaponType weaponType;
    switch (weaponChoice) {
        case 1:
            weaponType = Weapon::WeaponType::Sword;
            break;
        case 2:
            weaponType = Weapon::WeaponType::Staff;
            break;
        case 3:
            weaponType = Weapon::WeaponType::Bow;
            break;
        default:
            std::cout << "Invalid choice, defaulting to Sword.\n";
            weaponType = Weapon::WeaponType::Sword;
    }

    gameMap = Map(); // Initialize the map with the chosen weapon type
    gameMap.distributeEnemiesAndItems(weaponType);
    currentState = GameState::InGame; // Transition to the game state
}

bool Game::loadGame(const std::string& saveFile) {
    std::cout << "Loading game from " << saveFile << "...\n";
    LoadGame loader(saveFile);
    if (loader.load(*this)) {
        applyDifficulty();      // Apply difficulty after deserialization
        currentState = GameState::InGame; // Transition to the game state
        std::cout << "Game loaded successfully!\n";
        return true;
    }
    std::cout << "Failed to load the game.\n";
    return false;
}

void Game::saveGame(const std::string& saveFile) {
    std::cout << "Saving game to " << saveFile << "...\n";
    SaveGame saver(saveFile);
    if (saver.save(*this)) {
        std::cout << "Game saved successfully!\n";
    } else {
        std::cout << "Failed to save the game.\n";
    }
}

std::string Game::serialize() const {
    std::ostringstream oss;
    oss << player.serialize() << "\n"
        << difficulty.serialize() << "\n"
        << gameMap.serialize() << "\n"
        << inventory.serialize();
    return oss.str();
}

bool Game::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string playerData, difficultyData, mapData, inventoryData;

    if (!std::getline(iss, playerData) ||
        !std::getline(iss, difficultyData) ||
        !std::getline(iss, mapData) ||
        !std::getline(iss, inventoryData)) {
        return false;
    }

    return player.deserialize(playerData) &&
           difficulty.deserialize(difficultyData) &&
           gameMap.deserialize(mapData) &&
           inventory.deserialize(inventoryData);
}

void Game::applyDifficulty() {
    player.setDamage(player.getDamage() * difficulty.getAttackMultiplier());
    player.setHealth(player.getHealth() * difficulty.getHealthModifier());
}

void Game::showMainMenu() {
    menu.displayMenu();
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            newGame();
            break;
        case 2: {
            std::string saveFile;
            std::cout << "Enter the save file name: ";
            std::cin >> saveFile;
            if (!loadGame(saveFile)) {
                std::cout << "Returning to Main Menu...\n";
            }
            break;
        }
        case 3:
            exitGame();
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}

void Game::playGame() {
    std::cout << "\nWelcome to the game! Explore, battle, and survive.\n";
    std::string playerCommand;

    while (true) {
        std::cout << "\nWhat would you like to do?" << std::endl
                	<< "Save 	 - Save progress" << std::endl
									<< "Quit 	 - Quit game" << std::endl
									<< "Move 	 - Move rooms" << std::endl
									<< "Pickup - Pickup all items in the current room" << std::endl
									<< "Equip  - Equip item" << std::endl
									<< "Use 	 - Use potion" << std::endl
									<< "Print  - Print inventory" << std::endl
									<< "Enter your choice: ";
        std::cin >> playerCommand;

        std::transform(playerCommand.begin(), playerCommand.end(), playerCommand.begin(), ::tolower);

        if (playerCommand == "save") {
            while (true) {
                std::cout << "\nPress 1 to Save and Continue or Press 2 to Save and Return to the Main Menu: ";
                std::cin >> playerCommand;

                if (playerCommand == "1") {
                    saveGame("savefile.json");
                    std::cout << "Game saved! Continuing...\n";
                    break;
                } else if (playerCommand == "2") {
                    saveGame("savefile.json");
                    std::cout << "Game saved! Returning to the Main Menu...\n";
                    currentState = GameState::MainMenu;
                    return;
                } else {
                    std::cout << "Invalid choice! Please enter 1 or 2.\n";
                }
            }
        } 
				else if (playerCommand == "quit") {
            std::cout << "Exiting the game. Goodbye!\n";
            currentState = GameState::GameOver;
            return;
        } 
				else if (playerCommand == "move") {
            std::string direction;
            std::cout << "Enter a direction (up, down, left, right): ";
            std::cin >> direction;

            if (!gameMap.changeRoomBasedOnDirection(direction)) {
                std::cout << "Invalid direction. Try again.\n";
            } 
						else {
                std::cout << "Moved to a new room.\n";
								
								// COMBAT!!!
                if (gameMap.roomHasEnemies(gameMap.getPlayerIndex())) {
                    std::cout << "Enemies encountered! Prepare for battle.\n";
                    int currRoom = gameMap.getPlayerIndex();
										vector<Character*> fighters;
										fighters.push_back(&player);
										fighters.insert(fighters.end(), gameMap.returnEnemiesInRoom(currRoom).begin(), gameMap.returnEnemiesInRoom(currRoom).end());
										Combat playerCombat(fighters);

										// If the player is dead, print an ending message
										// run exitGame(), and break
										if (!player.isAlive()) {
											std::cout << player.getCharacterName() << "has died! Better skill next time." << std::endl;
											exitGame();
											break;
										}
										// All enemies have died, player is alive
										// Give experience, and run experience checks to increase 
										// health, damage, by 10%
										// storage capacity by 25%
										// if (experience > 100)
										else {
											int experienceToGive = gameMap.getRoomExperience(currRoom);
											player.setExperience(player.getExperience() + experienceToGive);
											gameMap.removeEnemies(currRoom);

											if (player.getExperience() > 100) {
												while (player.getExperience() > 100) {
													player.setHealth(player.getHealth() * 1.1);
													player.setDamage(player.getDamage() * 1.1);
													player.increaseStorageCapacity(player.getStorageCapacity() * 0.25);
													player.setExperience(player.getExperience() - 100);
												}
											}

											std::cout << "Congratulations! You won the battle!" << std::endl;
										}
                }
            }
        } 
				else if (playerCommand == "pickup") {
					int currRoom = gameMap.getPlayerIndex();
					vector<Item*> roomItems = gameMap.returnItemsInRoom(currRoom);
					if (roomItems.empty()) {
						std::cout << "This room has no items. Venture into the unknwon to find some......" << std::endl;
					}
					else {
						for (unsigned i = 0; i < roomItems.size(); i++) {
							std::cout << "Picked up " << roomItems.at(i)->getName() << "!" << std::endl;
							player.pickUpItem(roomItems.at(i));
						}
						gameMap.removeItems(currRoom);
					}

				}
				else if (playerCommand == "equip") {
					std::cout << "Which item would you like to equip?" << std::endl;

					player.outputWeapons(std::cout);
					player.outputArmour(std::cout);

					std::cout << "Enter name of weapon/armour (exact name): " << std::endl;
					std::string nameOfItemToEquip;
					std::getline(std::cin, nameOfItemToEquip);

					// Find where the player's desired item is in the inventory
					int itemIndex = player.itemFound(nameOfItemToEquip);
					// Have a pointer pointing to the item we want to equip
					Item* itemToEquip = player.getItem(itemIndex);

					if (itemToEquip->getType() == ItemType::WEAPON) {
						// I think this is how you use static casting?????
						// If not, uncomment this
						// Weapon* weaponToEquip = player.getItem(itemIndex);

						Weapon* weaponToEquip = static_cast<Weapon*> (itemToEquip);
						player.equipWeapon(weaponToEquip);
					}
					else if (itemToEquip->getType() == ItemType::ARMOUR) {
						Armour* armourToEquip = static_cast<Armour*> (itemToEquip);
						player.equipArmour(armourToEquip);
					}
					else {
						std::cout << "No weapon nor armour with this name exists in your inventory. Please try again." << std::endl;
					}
				}
				else if (playerCommand == "use") {
					std::cout << "Which potion would you like to use?" << std::endl;
					player.outputPotions(std::cout);

					std::cout << "Enter name of potion (exact name): " << std::endl;
					std::string nameOfPotionToUse;
					std::getline(std::cin, nameOfPotionToUse);

					int potionIndex = player.itemFound(nameOfPotionToUse);
					Item* itemToUse = player.getItem(potionIndex);

					if (itemToUse->getType() == ItemType::POTION) {
						Potion* potionToUse = static_cast<Potion*> (itemToUse);
						potionToUse->useItem(player);
						// This is easier 
						player.throwAwayItem(nameOfPotionToUse);
					}
					else {
						std::cout << "Item is either not a potion or does not exist. Please try again." << std::endl;
					}
				}
				else if (playerCommand == "print") {
					std::cout << "Inventory for " << player.getName() << std::endl;
					player.outputWeapons(std::cout);
					player.outputArmour(std::cout);
					player.outputPotions(std::cout);
					std::cout << std::endl;
				}
				else {
            std::cout << "Invalid command. Try again.\n";
        }
    }
}

void Game::exitGame() {
    currentState = GameState::GameOver;
}
