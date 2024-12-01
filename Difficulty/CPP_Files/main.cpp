#include <iostream>
#include "Difficulty.h"

using namespace std;

// Function to display enemy stats based on difficulty
void displayEnemyStats(const Difficulty& difficulty, double baseHealth, double baseAttack, double baseDefense) {
    double enemyAttack = baseAttack * difficulty.getAttackMultiplier();
    double enemyDefense = baseDefense * difficulty.getDefenseMultiplier();
    double enemyHealth = baseHealth * difficulty.getHealthModifier();

    cout << "\n=== Enemy Stats ===\n";
    cout << "Attack: " << enemyAttack << "\n";
    cout << "Defense: " << enemyDefense << "\n";
    cout << "Health: " << enemyHealth << "\n";
    cout << "===================\n";
}

int main() {
    Difficulty difficulty;

    cout << "=== Welcome to Battlestar ===\n\n";
    cout << "Select a difficulty level: Rookie, Elite, or Battlestar\n";

    string input;
    bool validDifficulty = false;

    do {
        cout << "Enter difficulty: ";
        cin >> input;

        try {
            difficulty.setDifficulty(input);
            validDifficulty = true;

            cout << "\nDifficulty successfully set to " << input << "!\n";
            cout << "Attack Multiplier: " << difficulty.getAttackMultiplier() << "\n";
            cout << "Defense Multiplier: " << difficulty.getDefenseMultiplier() << "\n";
            cout << "Health Modifier: " << difficulty.getHealthModifier() << "\n";

        } catch (const invalid_argument& e) {
            cerr << e.what() << "\n";
        }
    } while (!validDifficulty);

    double baseHealth = 1000.0;
    double baseAttack = 500.0;
    double baseDefense = 300.0;

    displayEnemyStats(difficulty, baseHealth, baseAttack, baseDefense);

    return 0;
}
