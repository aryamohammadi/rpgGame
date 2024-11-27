#include "../header/character.h"
#include "../header/armour.h"
#include "../header/inventory.h"
#include "../header/potion.h"
#include "../header/armour.h"
#include "../header/weapon.h"
#include <utility> // For std::swap
#include <sstream>
using std::string;
Character::Character(const std::string& name) : characterName(name), health(100),damage(0),defense(0), baseSpeed(20),currentSpeed(20), isDead(false), armour(nullptr), storage(new Inventory()), weapon(nullptr){} 

Character::~Character(){
    delete storage;
    delete armour;
    delete weapon;
}
// Copy operator
Character::Character(const Character& other)
    : characterName(other.characterName),
     // inventoryOfCharacter(other.inventoryOfCharacter), //  FIXME: this needs to be reviewd and fixed
      health(other.health),
      damage(other.damage),
      defense(other.defense),
      isDead(other.isDead),
      currentAttackType(other.currentAttackType) {
}


// Copy assignment operator
Character& Character::operator=(const Character& other) {
    if (this != &other) {
        Character temp(other); // Utilizing the copy constructor in the temporary instance
        swap(temp); // Swapping *this with temp
    }
    return *this;
}

// Swap function
void Character::swap(Character& other) noexcept {
    using std::swap;
    swap(characterName, other.characterName);
    swap(*storage, *other.storage); //FIXME: this needs to be reviewed and fixed
    swap(health, other.health);
    swap(damage, other.damage);
    swap(defense, other.defense);
    swap(isDead, other.isDead);
    swap(currentAttackType, other.currentAttackType);
}

void Character::equipArmour(Armour* newArmour){
    if(this->armour != nullptr){
        storage->addItem(this->armour);  
    }
    if(storage->itemFound(newArmour) != -1){
        storage->removeItem(*newArmour);
    }
    armour = newArmour;
    defense += armour->getArmourStat();
}

void Character::deEquipArmour() {
    if (armour != nullptr) {
        defense -= armour->getArmourStat();
        storage->addItem(armour);           
        armour = nullptr;                  
    }
}

void Character::equipWeapon(Weapon* newWeapon){
    if(newWeapon == nullptr){
        throw std::logic_error("equipWeapon : newWeapon is nullptr!");
    }
    if(weapon != nullptr){
        storage->addItem(weapon);  
    }
    if(storage->itemFound(newWeapon) != -1){
        storage->removeItem(*newWeapon);
    }
    weapon = newWeapon;
}

void Character::changeWeapon(int index){
    if(storage->itemFound(index) != -1){
        if(storage->getItem(index)->getType() != ItemType::WEAPON){
            throw std::invalid_argument("changeWeapon: Item at index " + std::to_string(index) + "is not a weapon!");
        }
        equipWeapon(dynamic_cast<Weapon*>(storage->getItem(index)));
    }
}

string Character::showInventory() const{
    std::ostringstream out;
    out << storage;

    return out.str();
    
}

string Character::outputWeapons() const{
    return storage->outputWeapons();
}

void pickUpItem(const Item& item){

}

bool Character::useItem(const string& itemName){
    int index = storage->itemFound(itemName);
    if(index == -1){
        return false;
    }
    ItemType type = storage->getItem(index)->getType();
    Item* currentItem = storage->getItem(index)->clone();
    Weapon* verifyWeapon = nullptr;
    Potion* verifyPotion = nullptr;
    Armour* verifyArmour = nullptr;
    switch(type){
        case ItemType::WEAPON:
            verifyWeapon = dynamic_cast<Weapon*>(currentItem);
            if(verifyWeapon == nullptr){
                delete currentItem;
                throw std::logic_error("Item contains invalid type!");
            }
            if(currentAttackType == AttackType::Melee){
                if(verifyWeapon->getWeaponType() != Weapon::WeaponType::Sword){
                    delete verifyWeapon;
                    throw std::logic_error("Inventory contains invalid weapon type!");
                }
            }
            else{
                if(verifyWeapon->getWeaponType() != Weapon::WeaponType::Bow && verifyWeapon->getWeaponType() != Weapon::WeaponType::Staff){
                    delete verifyWeapon;
                    throw std::logic_error("Inventory contains invalid weapon type!");
                }
            }
            equipWeapon(verifyWeapon);
            break;
        case ItemType::POTION:
            verifyPotion = dynamic_cast<Potion*>(currentItem);
            if(verifyPotion == nullptr){
                delete currentItem;
                throw std::logic_error("Item contains invalid type!");
            }
            verifyPotion->useItem(*this);
            storage->removeItem(*currentItem);

            delete verifyPotion;
            verifyPotion = nullptr;
            delete currentItem;
            currentItem = nullptr;

            break;
        case ItemType::ARMOUR:
            verifyArmour = dynamic_cast<Armour*>(currentItem);
            if(verifyArmour == nullptr){
                delete currentItem;
                throw std::logic_error("Item contains invalid type!");
            }
            equipArmour(verifyArmour);
            break;
        default:
            throw std::logic_error("Item had improper type!");
    }
    return true;
}

bool Character::useItem(const string& itemName, ItemType type){
    int index = storage->itemFound(itemName, type);
    if(index == -1){
        return false;
    }
    Item* currentItem = storage->getItem(index)->clone();
    Weapon* verifyWeapon = nullptr;
    Potion* verifyPotion = nullptr;
    Armour* verifyArmour = nullptr;
    switch(type){
        case ItemType::WEAPON:
            verifyWeapon = dynamic_cast<Weapon*>(currentItem);
            if(verifyWeapon == nullptr){
                delete currentItem;
                throw std::logic_error("Item contains invalid type!");
            }
            if(currentAttackType == AttackType::Melee){
                if(verifyWeapon->getWeaponType() != Weapon::WeaponType::Sword){
                    delete verifyWeapon;
                    throw std::logic_error("Inventory contains invalid weapon type!");
                }
            }
            else{
                if(verifyWeapon->getWeaponType() != Weapon::WeaponType::Bow && verifyWeapon->getWeaponType() != Weapon::WeaponType::Staff){
                    delete verifyWeapon;
                    throw std::logic_error("Inventory contains invalid weapon type!");
                }
            }
            equipWeapon(verifyWeapon);
            break;
        case ItemType::POTION:
            verifyPotion = dynamic_cast<Potion*>(currentItem);
            if(verifyPotion == nullptr){
                delete currentItem;
                throw std::logic_error("Item contains invalid type!");
            }
            verifyPotion->useItem(*this);
            storage->removeItem(*currentItem);

            delete verifyPotion;
            verifyPotion = nullptr;
            delete currentItem;
            currentItem = nullptr;

            break;
        case ItemType::ARMOUR:
            verifyArmour = dynamic_cast<Armour*>(currentItem);
            if(verifyArmour == nullptr){
                delete currentItem;
                throw std::logic_error("Item contains invalid type!");
            }
            equipArmour(verifyArmour);
            break;
        default:
            throw std::logic_error("Item had improper type!");
    }
    return true;
}

bool Character::useItem(int index){
    if(storage->itemFound(index) == -1){
        return false;
    }
    ItemType type = storage->getItem(index)->getType();
    Item* currentItem = storage->getItem(index)->clone();
    Weapon* verifyWeapon = nullptr;
    Potion* verifyPotion = nullptr;
    Armour* verifyArmour = nullptr;
    switch(type){
        case ItemType::WEAPON:
            verifyWeapon = dynamic_cast<Weapon*>(currentItem);
            if(verifyWeapon == nullptr){
                delete currentItem;
                throw std::logic_error("Item contains invalid type!");
            }
            if(currentAttackType == AttackType::Melee){
                if(verifyWeapon->getWeaponType() != Weapon::WeaponType::Sword){
                    delete verifyWeapon;
                    throw std::logic_error("Inventory contains invalid weapon type!");
                }
            }
            else{
                if(verifyWeapon->getWeaponType() != Weapon::WeaponType::Bow && verifyWeapon->getWeaponType() != Weapon::WeaponType::Staff){
                    delete verifyWeapon;
                    throw std::logic_error("Inventory contains invalid weapon type!");
                }
            }
            equipWeapon(verifyWeapon);
            break;
        case ItemType::POTION:
            verifyPotion = dynamic_cast<Potion*>(currentItem);
            if(verifyPotion == nullptr){
                delete currentItem;
                throw std::logic_error("Item contains invalid type!");
            }
            verifyPotion->useItem(*this);
            storage->removeItem(*currentItem);

            delete verifyPotion;
            verifyPotion = nullptr;
            delete currentItem;
            currentItem = nullptr;

            break;
        case ItemType::ARMOUR:
            verifyArmour = dynamic_cast<Armour*>(currentItem);
            if(verifyArmour == nullptr){
                delete currentItem;
                throw std::logic_error("Item contains invalid type!");
            }
            equipArmour(verifyArmour);
            break;
        default:
            throw std::logic_error("Item had improper type!");
    } 
    return true; 
}

bool Character::throwAwayItem(const string& name){
    if(storage->itemFound(name) == -1){
        return false;
    }
    storage->removeItem(name);
    return true;
}

bool Character::throwAwayItem(const string& name, ItemType type){
    if(storage->itemFound(name, type) == -1){
        return false;
    }
    storage->removeItem(name, type);
    return true;
}

bool Character::throwAwayItem(int index){
    if(storage->itemFound(index) == -1){
        return false;
    }
    storage->removeItem(*(storage->getItem(index)));
    return true;
}

void Character::attack(Character& target){
    weapon->useItem(target);
    // This will have been replaced by Jessy
}

std::string Character::getCharacterName() const {
    return characterName;
}