#include "../header/combat.h"
#include "../header/character.h"
#include <../gtest/gtest.h>

TEST(combatTest, checkVector){
    Character character("player");
    
}

TEST(Combat_test, TestingIfPlayerIsDead) {
    
    Character* player = new Character("Player");
    Character* enemy1 = new Character("Enemy1");
    Character* enemy2 = new Character("Enemy2");;


    std::vector<Character*> fighters = {player, enemy1, enemy2};

    Combat combat(fighters);

    combat.startBattle();

    // Test if the player is dead
    EXPECT_FALSE(combat.isPlayerDead()) << "Player should not be dead at the start of the battle.";

    // Test if both enemies are dead
    EXPECT_FALSE(combat.areBothEnemiesDead()) << "Both enemies should not be dead at the start of the battle.";

    // Test if at least one enemy is still alive
    EXPECT_TRUE(combat.isAtLeast1EnemieAlive()) << "At least one enemy should be alive at the start of the battle.";

    delete player;
    delete enemy1;
    delete enemy2;
}

