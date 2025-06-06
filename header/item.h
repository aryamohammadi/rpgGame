#pragma once

#include <iostream>
#include <ostream>
#include <vector>
#include <ctime>
#include <string>
#include <chrono>
#include "../header/itemType.h"
#include "../header/character.h"

class Character;
using std::string;
using std::ostream;
using std::vector;

static auto programStartTime = std::chrono::steady_clock::now();

class Item {
protected:
    string name;
    const vector<string> types{"WEAPON", "ARMOR", "POTION"};
    ItemType type;
    string description;
    double timeEarned;

public:
    Item(ItemType t = ItemType::WEAPON, const string& name = "", const string& descript = "", double timeElapsed = -1.0);
    Item(const Item& other) = delete;
    Item& operator=(const Item& other) = delete;
    virtual ~Item() = default;

    string getName() const{return name;}
    string getDescript() const{return description;}
    double getTime() const{return timeEarned;}
    ItemType getType() const{return type;}
    string determineType(ItemType type) const;

    virtual void useItem(Character&) = 0;
    virtual Item* clone() const = 0;
    virtual std::unique_ptr<Item> cloneUnique() const = 0;
    friend void swap(Item*& item1, Item*& item2);

    virtual std::string serialize() const;
    virtual bool deserialize(const string& data);
    friend ostream& operator<<(ostream& out, const Item& item);
};
class Potion : public Item {
private:
    int recoveryAmount = 0;

public:
    Potion():Item(ItemType::POTION, "Default Potion", ""){}
    Potion(ItemType t, const string& name, const string& descript, int amount, double timeElapsed = -1.0);
    Potion(const Potion& otherPotion){*this = otherPotion;}
    Potion& operator=(const Potion& otherPotion);
    ~Potion() override = default;
    void useItem(Character&) override;
    Item* clone() const override;
    std::unique_ptr<Item> cloneUnique() const override;
    int getRecoveryAmount() const{return recoveryAmount;}
    friend std::ostream& operator<<(std::ostream& out, const Potion& currentPotion);

    std::string serialize() const;
    bool deserialize(const std::string& data);
};

class Weapon : public Item {
public:
    enum WeaponType {
        Sword,
        Staff,
        Bow
    };

private:
    int damage =  0;
    WeaponType weaponType = WeaponType::Sword;
    int speedEffect = 0;

public:
    Weapon():Item(ItemType::WEAPON, "Default Weapon", ""){}
    Weapon(ItemType type, const std::string& name, const std::string& descript,
           int damage, WeaponType weaponType, double timeElapsed = -1.0);
    Weapon(const Weapon& otherWeapon){*this = otherWeapon;}
    Weapon& operator=(const Weapon& otherWeapon);
    ~Weapon() override = default;
    void useItem(Character& target) override;
    void setWeaponType(WeaponType newType){weaponType = newType;}
    Item* clone() const override;
    WeaponType getWeaponType() const{return weaponType;}
    int getSpeedEffect() const{return speedEffect;}
    int getDamage() const{return damage;}
    void increaseDamage(int amount){damage += amount;}
    void decreaseDamage(int amount){damage -= amount;}
    friend std::ostream& operator<<(std::ostream& out, const Weapon& currentWeapon);
    std::unique_ptr<Item> cloneUnique() const override;

    std::string serialize() const;
    bool deserialize(const std::string& data);
};

class Armour : public Item {
private:
    int armourStat = 0;

public:
    Armour():Item(ItemType::ARMOUR, "Default Armour",""){}
    Armour(ItemType t, const string& name, const string& descript, int stat, double timeElapsed = -1.0);
    Armour(const Armour& otherArmour){*this = otherArmour;}
    Armour& operator=(const Armour& otherArmour);
    ~Armour() override = default;
    void useItem(Character&) override;
    Item* clone() const override;
    std::unique_ptr<Item> cloneUnique() const override;
    int getArmourStat() const{return armourStat;}
    friend std::ostream& operator<<(std::ostream& out, const Armour& currentArmour);

    std::string serialize() const;
    bool deserialize(const std::string& data);
};

class MockItem : public Item{
    public:
        MockItem(ItemType t = ItemType::WEAPON, const string& name = "", const string& descript = "", double timeElapsed = -1.0):Item(t,name,descript, timeElapsed){}
        void useItem(Character& ) override{
            return;
        }
        std::unique_ptr<Item> cloneUnique() const override{
            return std::make_unique<MockItem>(type, name, description, timeEarned);  
        }
        Item* clone() const override{
            return new MockItem(type, name, description, timeEarned);
        }
        friend void swap(MockItem*& item1, MockItem*& item2){
            MockItem* item1Placeholder = item1;

            item1 = item2;

            item2 = item1Placeholder;
        }
        virtual bool deserialize(const string& data){
            return false;
        }
        virtual std::string serialize() const{
            return "";
        }

};
