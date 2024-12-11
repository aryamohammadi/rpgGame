#include "../header/combat.h"
#include "../header/character.h"
#include "gtest/gtest.h"
#include <vector>
#include "gmock/gmock.h"

using namespace std;

// Helper function to create a test enemy character
Character* createEnemy(const string& name, int health = 100, int defense = 10) {
    Character* enemy = new Character(name);
    enemy->setHealth(health);
    return enemy;
}

// Helper function to create a player character
Character* createPlayer(const string& name) {
    return new Character(name);
}

// Test Cases
TEST(CombatTest, EnemiesShouldBeAliveBeforeBattle) {//makes sure that before they even battle it out they should both be aliove
    Character* player = createPlayer("Player");
    Character* enemy = createEnemy("Enemy");

    player->equipWeapon(new Weapon());
    enemy->equipWeapon(new Weapon());
    vector<Character*> fighters{player, enemy};

    // Player should still be alive
    EXPECT_TRUE(player->isAlive());
    // Enemy should be dead
    EXPECT_TRUE(enemy->isAlive());

    delete player;
    delete enemy;
}

TEST(CombatTest, PlayerDecidesWhoToAttackValidChoice) {
    Character *player = createPlayer("Player");
    Character *enemy = createEnemy("Enemy");

    player->equipWeapon(new Weapon());
    enemy->equipWeapon(new Weapon());
    std::vector<Character *> fighters{player, enemy};
    Combat combat(fighters);

    std::stringstream input("1\n");
    std::cin.rdbuf(input.rdbuf());

    int choice = combat.playerDecidesWhoToAttack();

    EXPECT_EQ(choice, 1);

    delete player;
    delete enemy;
}
// Test Cases
TEST(CombatTest, StartBattleWithOneEnemy) {//makes sure that before they even battle it out they should both be aliove
    Character* player = createPlayer("Player");
    Character* enemy = createEnemy("Enemy");
    Character* enemy1 = createEnemy("Enemy");

    player->equipWeapon(new Weapon());
    enemy->equipWeapon(new Weapon());
    enemy1->equipWeapon(new Weapon());
    vector<Character*> fighters{player, enemy, enemy1};
    Combat combat(fighters);

    // Simulate battle
    combat.startBattle();

    // Player should still be alive
    EXPECT_TRUE(player->isAlive());
    // Enemy should be dead
    EXPECT_FALSE(enemy->isAlive());

    delete player;
    delete enemy;
}

TEST(CombatTest, PlayerDiesDuringCombat) {
    Character* player = createPlayer("Player");
    player->setHealth(50); // Set low health for the player
    Character *strongEnemy = createEnemy("Enemy", 100);

    player->equipWeapon(new Weapon());
    strongEnemy->equipWeapon(new Weapon());
    std::vector<Character *> fighters{player, strongEnemy};
    Combat combat(fighters);

    // Simulate battle
    combat.startBattle();

    // Player should be dead
    EXPECT_FALSE(player->isAlive());
    // Strong enemy should still be alive
    EXPECT_TRUE(strongEnemy->isAlive());

    delete player;
    delete strongEnemy;
}

TEST(CombatTest, PlayerAttacksAndChoosesTarget) {
    unique_ptr<Character> player = make_unique<Character>(Character("Player"));
    unique_ptr<Character> enemy1 = make_unique<Character>(Character("Enemy1"));
    enemy1->setHealth(80);
    unique_ptr<Character> enemy2 = make_unique<Character>(Character("Enemy2"));
    enemy2->setHealth(60);
    
    player->equipWeapon(new Weapon());
    enemy1->equipWeapon(new Weapon());
    enemy2->equipWeapon(new Weapon());
    std::vector<Character *> fighters{player.get(), enemy1.get(), enemy2.get()};
    Combat combat(fighters);

    combat.startBattle();

    // Ensure Enemy2 was attacked
    EXPECT_LT(enemy2->getHealth(), 60);
}


TEST(CombatTest, RemovePlayerFromHeap) {
    Character *player = createPlayer("Player");
    Character *enemy1 = createEnemy("Enemy1");
    Character *enemy2 = createEnemy("Enemy2");

    player->equipWeapon(new Weapon());
    enemy1->equipWeapon(new Weapon());
    enemy2->equipWeapon(new Weapon());
    
    std::vector<Character *> fighters{player, enemy1, enemy2};
    Combat combat(fighters);

    combat.removePlayerFromHeap("Enemy1");

    // Enemy1 should no longer be in the fightersAlive list
    auto it = find_if(fighters.begin(), fighters.end(), [](Character* c) { return c->getName() == "Enemy1"; });
    EXPECT_EQ(it, fighters.end());

    delete player;
    delete enemy2;
}



TEST(CombatTest, PlayerDecidesWhoToAttackInvalidChoice) {
    Character *player = createPlayer("Player");
    Character *enemy = createEnemy("Enemy");

    enemy->equipWeapon(new Weapon());
    std::vector<Character *> fighters{player, enemy};
    Combat combat(fighters);

    stringstream input("0 1");
    cin.rdbuf(input.rdbuf());

    int choice = combat.playerDecidesWhoToAttack();

    if (choice != 1) {
        cerr << "Test failed: Expected choice to be 1 but got " << choice << endl;
        FAIL();
    }

    delete player;
    delete enemy;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

