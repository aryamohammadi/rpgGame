#include "../header/Room.h"
#include "../header/AttackType.h"
#include "../header/character.h"
#include <ctime>
#include <iostream>

void Room::removeEnemies() {
  
}

void Room::addEnemies(Character enemyToAdd) {

  // Add either one or two enemies to the room's given vector
  Character enemyToAdd("Enemy1");
  enemyToAdd.setAttackType(AttackType::Ranged);
  enemyToAdd.setDamage(5);
  enemyToAdd.setHealth(25);
  enemies.push_back(enemyToAdd);

  if (rand() % 2 == 0) {
    Character anotherEnemytoAdd("Enemy2");  
    anotherEnemytoAdd.setAttackType(AttackType::Melee);
    anotherEnemytoAdd.setDamage(7);
    anotherEnemytoAdd.setHealth(15);
    enemies.push_back(anotherEnemytoAdd);
  }
}

void Room::addItems() {
  srand(time(0));

 // Add one, two, or three to the room's given vector.
 // 8 rooms have 1 item
 // 4 rooms have 2 items
 // 2 rooms have 3 items

  Item* item1;
  std::cout << "WARNING: ADD ATTRIBUTES TO item1 IN Room.cpp" << std::endl;
  items.push_back(item1);

  if (rand() % 2 == 0) {
    Item* item2;
    std::cout << "WARNING: ADD ATTRIBUTES TO item2 IN Room.cpp" << std::endl;
    items.push_back(item2);

    if (rand() % 8 == 0) {
    Item* item3;
    std::cout << "WARNING: ADD ATTRIBUTES TO item3 IN Room.cpp" << std::endl;
    items.push_back(item3);
  }
  }
}