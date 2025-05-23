#include "../header/character.h"
#include "../header/item.h"
#include "../header/inventory.h"
#include "../header/AttackType.h"
#include <utility>
#include <sstream>
using std::string;

Character::Character(const std::string& name) : characterName(name), health(100),defense(0), baseSpeed(20),currentSpeed(20), isDead(false){
    storage = make_unique<Inventory>();
    armour = nullptr;
    weapon = nullptr;
} 
Character::Character(): characterName("Warrior"), health(100), defense(0), baseSpeed(20), currentSpeed(20),isDead(false){
    storage = make_unique<Inventory>();
    armour = nullptr;
    weapon = nullptr;
}
Character::~Character(){}
// Copy operator
Character::Character(const Character& other){*this = other;}

// Copy assignment operator
Character& Character::operator=(const Character& other) {
    if (this != &other) {
        if(!other.isStorageEmpty()){
            storage = make_unique<Inventory>(*other.storage);
        }
        else{
            storage = make_unique<Inventory>();
        }
        if(other.weapon == nullptr){
            deEquipWeapon();
        }
        else{
            deEquipWeapon();
            weapon = make_unique<Weapon>(*other.weapon);
        }
        if(other.armour == nullptr){
            deEquipArmour();
        }
        else{
            deEquipArmour();
            armour = make_unique<Armour>(*other.armour);
        }
        setName(other.getName());
        setAttackType(other.getAttackType());
        setDamage(other.getDamage());
        setHealth(other.getHealth());
        currentSpeed = other.getSpeed();
        setExperience(other.experience);
        
    }
    return *this;
}

// Swap function
void Character::swap(Character& other) noexcept {
    using std::swap;
    swap(characterName, other.characterName);
    storage = make_unique<Inventory>(*other.storage);
    armour = make_unique<Armour>(*other.armour);
    weapon = make_unique<Weapon>(*other.weapon);
    swap(health, other.health);
    swap(defense, other.defense);
    swap(isDead, other.isDead);
    swap(currentAttackType, other.currentAttackType);
    swap(experience, other.experience);
    swap(currentSpeed, other.currentSpeed);
    swap(baseSpeed, other.baseSpeed);

}

std::string Character::getName() const {
    return characterName;
}

void Character::equipArmour(Armour* newArmour){
    if(armour != nullptr || newArmour == nullptr){
        deEquipArmour();
        if(newArmour == nullptr){
            armour.reset(newArmour);
        }
    }
    if(storage->itemFound(newArmour) != -1){ // If the armor you're trying to add exists in inventory, remove it from inventory. If it doesn't exist, hey you're all good
        storage->removeItem(*newArmour);
    }
    armour = make_unique<Armour>(*newArmour); // Equip this new armor
    defense += armour->getArmourStat();
}

void Character::deEquipArmour() {
    if (armour != nullptr) {
        defense -= armour->getArmourStat();
        storage->addItem(armour.get()->clone());           
        armour = nullptr;                  
    }
}

void Character::equipWeapon(Weapon* newWeapon){
    if(newWeapon == nullptr){
        resetSpeed();
        weapon.reset();  // Reset weapon if the newWeapon is nullptr
    } else{
        if(weapon != nullptr){
            // Only add the old weapon to storage if it exists
            storage->addItem(weapon->clone());
            resetSpeed();
        }

        // If the new weapon exists in storage, remove it
        if(storage->itemFound(newWeapon) != -1){
            storage->removeItem(*newWeapon);
        }

        // Now take ownership of the new weapon
        weapon.reset(newWeapon);  // Transfer ownership of the new weapon
        modifySpeed(weapon->getSpeedEffect());  // Update speed with the new weapon's effect
    }
}


void Character::deEquipWeapon() {
    if (weapon != nullptr) {
        resetSpeed();
        storage->addItem(weapon.get()->clone());
        weapon.reset();
    }
}


void Character::changeWeapon(int index){
    if(storage->itemFound(index) != -1){
        if(storage->getItem(index)->getType() != ItemType::WEAPON){
            throw std::invalid_argument("changeWeapon: Item at index " + std::to_string(index) + "is not a weapon!");
        }
        equipWeapon(dynamic_cast<Weapon*>(storage->getItem(index)));
    }
}

ostream& Character::showInventory(ostream& out) const{
    out << *storage;

    return out;
    
}

std::ostream& Character::outputWeapons(std::ostream& out) const{
    return storage->outputWeapons(out);
}

bool Character::pickUpItem(Item* item){
    if(storage->sizeGreaterThanOrEqualToCapacity() || item == nullptr){
        return false;
    }
    storage->addItem(item);
    return true;
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
    if(storage->itemFound(index) == -1 || isStorageEmpty()){
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
    if(storage->itemFound(name) == -1 || isStorageEmpty()){
        return false;
    }
    storage->removeItem(name);
    return true;
}

bool Character::throwAwayItem(const string& name, ItemType type){
    if(storage->itemFound(name, type) == -1 || isStorageEmpty()){
        return false;
    }
    storage->removeItem(name, type);
    return true;
}

bool Character::throwAwayItem(int index){
    if(storage->itemFound(index) == -1 || isStorageEmpty()){
        return false;
    }
    storage->removeItem(*(storage->getItem(index)));
    return true;
}

void Character::attack(Character& target){
    weapon->increaseDamage(damage);
    weapon->useItem(target);
    weapon->decreaseDamage(damage);
    // This will have been replaced by Jessy
}

std::string Character::getCharacterName() const {
    return characterName;
}

void Character::modifySpeed(int delta){
    currentSpeed += delta;
}

bool Character::isAlive() const{
    return !isDead;
}

std::ostream& operator<<(std::ostream& out, const Character& entity){
    out << "Name: " << entity.getCharacterName() << std::endl;
    out << "Current Health: " << entity.getHealth() << std::endl;
    out << "Current Speed: " << entity.getSpeed() << std::endl;
    out << "Current Defense: " << entity.getDefense() << std::endl;
    if(entity.weapon != nullptr){
        out << "Current Weapon: " << std::endl;
        out << *entity.weapon;
    }
    if(entity.armour != nullptr){
        out << "Current Armour: " << std::endl;
        out << *entity.armour;
    }
    return out;
}

int Character::itemsWithName(const string& name) const{
    return storage->itemsWithName(name);
}
void Character::increaseStorageCapacity(int amount){
    storage->increaseCapacity(amount);
}

bool Character::isStorageEmpty() const{
    return storage->isEmpty();
}
void Character::sortAlphabetically(){
    storage->sortAlphabetically();
}

void Character::makeLatestFirst(){
    storage->makeLatestFirst();
}
void Character::makeOldestFirst(){
    storage->makeOldestFirst();
}

// Serialize the Character
std::string Character::serialize() const {
    std::ostringstream oss;
    oss << characterName << "\n"
        << health << "\n"
        << defense << "\n"
        << baseSpeed << "\n"
        << currentSpeed << "\n"
        << isDead << "\n"
        << currentAttackType << "\n"
        << (armour ? armour->serialize() : "null") << "\n"
        << (weapon ? weapon->serialize() : "null") << "\n"
        << storage->serialize();
    return oss.str();
}

// Deserialize the Character
bool Character::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string armourData, weaponData, inventoryData;

    if (!(std::getline(iss, characterName) &&
          iss >> health >> defense >> baseSpeed >> currentSpeed >> isDead >> currentAttackType)) {
        return false;
    }

    // Deserialize Armour
    std::getline(iss >> std::ws, armourData);
    if (armourData != "null") {
        armour = make_unique<Armour>();
        if (!armour->deserialize(armourData)) {
            armour.reset();
            return false;
        }
    }

    // Deserialize Weapon
    std::getline(iss >> std::ws, weaponData);
    if (weaponData != "null") {
        weapon = make_unique<Weapon>();
        if (!weapon->deserialize(weaponData)) {
            weapon.reset();
            return false;
        }
    }

    // Deserialize Inventory
    std::getline(iss >> std::ws, inventoryData);
    return storage->deserialize(inventoryData);
}

void Character::setHealth(int healthOfCharacter){ 
    health = healthOfCharacter;
    isDead = health <= 0; 
}
void Character::takeDamage(int damageOnCharacter){ 
    health-= damageOnCharacter; 
    isDead = health <= 0;
}
void swap(Character*& char1,Character*& char2){
    Character* temp = char1;
    char1 = char2;
    char2 = temp;
}

std::ostream& operator<<(std::ostream& out, const AttackType& type){
    switch(type){
        case AttackType::Melee:
            out << "Melee";
            return out;
        case AttackType::Ranged:
            out << "Ranged";
            return out;
        default:
            out.setstate(std::ios::failbit);
            return out;
    }
}

std::istream& operator>>(std::istream& in, AttackType& type){
    std::string inString;
    in >> inString;
    const std::vector<std::string> possibleTypes{"Melee", "Manged"};
    if(inString.size() < 0){
        return in;
    }
    if(inString == possibleTypes.front()){
        type = AttackType::Melee;
        return in;
    }
    if(inString == possibleTypes[1]){
        type = AttackType::Ranged;
        return in;
    }
    in.setstate(std::ios::failbit);
    return in;
}   

std::ostream& Character::outputPotions(std::ostream& out) const{
    return storage->outPotions(out);
}
std::ostream& Character::outputArmour(std::ostream& out) const{
    return storage->outArmour(out);
}

void Character::increaseStorageCapacityByPercent(double percent){
    storage->increaseCapacityByPercent(percent);
}
