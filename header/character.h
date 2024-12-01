#pragma once
#include <string> // we need to include the string library to use the string data type
#include "inventory.h"  

#include "../header/AttackType.h"
#include <string>
using std::string;
class Inventory;
class Item;
class Armour;
class Weapon;
enum class ItemType;
class Character{
    private:
        std::string characterName;
        Inventory* storage;
        Armour* armour;
        Weapon* weapon;
        int health;
        int damage;
        int defense; 
        int baseSpeed;
        int currentSpeed;
        bool isDead;
        AttackType currentAttackType;
    public:
        Character(const std::string& name);
        void swap(Character& other) noexcept;/* noexcept is an exception specifier that tells the compiler 
                                                that this function will not throw any exceptions */
        Character(const Character& other);
        Character& operator=(const Character& other);
        ~Character();

        // Constructor
        Character(const std::string& name);

        // Copy constructor
        Character(const Character& other);

        // Copy assignment operator
        Character& operator=(const Character& other);

        void setHealth(int healthOfCharacter){ health = healthOfCharacter; }
        void setDamage(int damageOfCharacter){ damage = damageOfCharacter; }
        void takeDamage(int damageOnCharacter){ health-= damageOnCharacter; }

        int getSpeed()const{
            return speed;
        }

        friend void swap(Character* char1,Character* char2){
            Character* temp = char1;
            char1 = char2;
            char2 = temp;
        }

        // Consider having the combat class handle damage calculations based on the two Character parameters passed to it
        Character(const std::string& name) : characterName(name), health(100),damage(0),defense(0),isDead(false){} 
        void swap(Character& other) noexcept; // Added by Arya; swap function
                                              /* noexcept is an exception specifier that tells the compiler 
                                                 that this function will not throw any exceptions */
        
        void setHealth(int healthOfCharacter){ health = healthOfCharacter; }
        void increaseHealth(int amount){health += amount;}

        void setDamage(int damageOfCharacter){ damage = damageOfCharacter; }
        void takeDamage(int damageOnCharacter){ health-= damageOnCharacter; }
  
        void equipWeapon(Weapon* newWeapon);
        void changeWeapon(int index); 

        void modifySpeed(int delta);
        void resetSpeed(){currentSpeed = baseSpeed;}
        int getSpeed() const {return currentSpeed;}

        void setAttackType(AttackType attackType) {currentAttackType = attackType;}
        AttackType getAttackType() const {return currentAttackType;}

        void attack(Character& target);

        void pickUpItem(const Item& item);
        
        bool useItem(const string& itemName); //finds closest with name and returns if succesfull
        bool useItem(const string& itemName, ItemType type); //finds exact item with name and type and returns if successful
        bool useItem(int index); //uses index and returns if successful
        
        bool throwAwayItem(const string& name);
        bool throwAwayItem(const string& name, ItemType type);
        bool throwAwayItem(int index);

        std::string showInventory() const;
        std::string outputWeapons() const;
  
        void equipArmour(Armour* armour){
            if(this->armour == nullptr){
                this->armour = armour;
            }
            else{
                if(storage.itemFound(*armour) != -1){
                    storage.removeItem(*armour);
                }
                this->armour = armour;
            }
            defense += armour->getArmourStat();
        }
        void deEquipArmour(){
            
            storage.addItem(armour);
        }

        // These cause Character to be abstract, preventing me from declaring Character objects properly in Room.cpp, so I'm commenting them out before we delete them because Character is not an abstract class anymore
        // virtual void attack() = 0;
        // virtual void defend() = 0;
       
        // Destructor
        virtual ~Character();
       
        /* noexcept is an exception specifier that tells the compiler that this function will not throw any exceptions */
        void swap(Character& other) noexcept;
        
        // Setters
        void setHealth(int healthOfCharacter);
        void setDamage(int damageOfCharacter);
        void takeDamage(int damageOnCharacter);

        // Getters
        std::string getCharacterName() const;
        int getHealth() const;
        int getDamage() const;
        int getDefense() const;
        AttackType getAttackType() const;
        bool isAlive() const;
        std::string getCharacterName() const; // Returns the character's name


        // Combat virtual functions to be implemented by derived classes
        virtual void attack(Character& target) = 0;
        virtual void defend() = 0;

        // Additional methods related to character status
        void setAttackType(AttackType attackType);

        bool operator>(const Character& other)const {
            return speed > other.speed;
        }
};
