#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>


using namespace std;

class Character {
public:
    Character(string n, int h, int a, int d) : name(n), health(h), attack(a), defense(d) {}
    // Konstruktor, der ein Character Objekt mit Namen, Leben, Angriff und Verteidigung initialisiert
    virtual ~Character() {} // Virtueller Destruktor für Speichermanagement
    string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    const vector<string>& getAbilities() const { return abilities; } // Konstante Referenz zu einem Vektor von Fähigkeiten
    virtual void ability1(Character* target) = 0;
    virtual void ability2(Character* target) = 0;
    virtual void ability3(Character* target) = 0;
    virtual void attackNormal(Character* target) {
        int damage = max(attack - target->getDefense(), 0); // Schaden von Angriff - Verteidigung
        target->takeDamage(damage);
        cout << name << " attacks " << target->getName() << " and deals " << damage << " damage." << endl;
        cout << "" << endl;
    }
    void takeDamage(int damage) {
        health = max(health - damage, 0);
    }
    bool isAlive() const { return health > 0; } // Überprüft ob Leben größer als 0 ist

protected:
    string name;
    int health;
    int attack;
    int defense;
    vector<string> abilities;
};

class SwordWarrior : public Character { // Klasse erbt Werte von Character
public:
    SwordWarrior(string n) : Character(n, 150, 20, 20) {
        // Fähigkeiten werden in den Vektor hinzugefügt
        abilities.push_back("Sword Slash");
        abilities.push_back("Power Strike");
        abilities.push_back("Whirlwind");
    }
    virtual void ability1(Character* target) {
        int damage = max(2 * attack - target->getDefense(), 0); // Angriff doppelt so groß wie die ATK
        target->takeDamage(damage);
        cout << name << " performs a Sword Slash on " << target->getName() << " and deals " << damage << " damage." << endl;
        cout << target->getName() << " has " << target->getHealth() << " health remaining." << endl;
        cout << "" << endl;
    }
    virtual void ability2(Character* target) {
        int damage = max(3 * attack - target->getDefense(), 0);
        target->takeDamage(damage);
        cout << name << " performs a Power Strike on " << target->getName() << " and deals " << damage << " damage." << endl;
        cout << target->getName() << " has " << target->getHealth() << " health remaining." << endl;
        cout << "" << endl;
    }
    virtual void ability3(Character* target) {
        int damage = max(attack - target->getDefense(), 0);
        target->takeDamage(damage);
        cout << name << " performs a Whirlwind attack and deals " << damage << " damage to " << target->getName() << "." << endl;
        cout << target->getName() << " has " << target->getHealth() << " health remaining." << endl;
        cout << "" << endl;
    }
};

class AxeWarrior : public Character {
public:
    AxeWarrior(string n) : Character(n, 150, 25, 10) {
        abilities.push_back("Axe Chop");
        abilities.push_back("Mighty Swing");
        abilities.push_back("Cleave");
    }
    virtual void ability1(Character* target) {
        int damage = max(2 * attack - target->getDefense(), 0);
        target->takeDamage(damage);
        cout << name << " performs an Axe Chop on " << target->getName() << " and deals " << damage << " damage." << endl;
        cout << target->getName() << " has " << target->getHealth() << " health remaining." << endl;
        cout << "" << endl;
    }
    virtual void ability2(Character* target) {
        int damage = max(3 * attack - target->getDefense(), 0);
        target->takeDamage(damage);
        cout << name << " performs a Mighty Swing on " << target->getName() << " and deals " << damage << " damage." << endl;
        cout << target->getName() << " has " << target->getHealth() << " health remaining." << endl;
        cout << "" << endl;
    }
    virtual void ability3(Character* target) {
        int damage = max(2 * attack - target->getDefense(), 0);
        target->takeDamage(damage);
        cout << name << " performs a Cleave attack and deals " << damage << " damage to " << target->getName() << "." << endl;
        cout << target->getName() << " has " << target->getHealth() << " health remaining." << endl;
        cout << "" << endl;
    }
};

class CustomWarrior : public Character {
public:
    CustomWarrior(string n, vector<string> chosenAbilities) : Character(n, 150, 20, 15) {
        for (string ability : chosenAbilities) {
            abilities.push_back(ability);   // jede Fähigkeit die ausgewählt wird kommt in den Vektor des Charakters
        }
    }

    virtual void ability1(Character* target) {
        if (abilities.size() > 0) { // Charakter hat mind. 1 Fähigkeit
            string ability = abilities[0];  // Fähigkeit wird erste im Vektor
            int damage = calculateDamage(ability, target);
            target->takeDamage(damage);
            cout << name << " performs " << ability << " on " << target->getName() << " and deals " << damage << " damage." << endl;
            cout << target->getName() << " has " << target->getHealth() << " health remaining." << endl;
            cout << "" << endl;
        }
    }

    virtual void ability2(Character* target) {
        if (abilities.size() > 1) {
            string ability = abilities[1];
            int damage = calculateDamage(ability, target);
            target->takeDamage(damage);
            cout << name << " performs " << ability << " on " << target->getName() << " and deals " << damage << " damage." << endl;
            cout << target->getName() << " has " << target->getHealth() << " health remaining." << endl;
            cout << "" << endl;
        }
    }

    virtual void ability3(Character* target) {
        if (abilities.size() > 2) {
            string ability = abilities[2];
            int damage = calculateDamage(ability, target);
            target->takeDamage(damage);
            cout << name << " performs " << ability << " on " << target->getName() << " and deals " << damage << " damage." << endl;
            cout << target->getName() << " has " << target->getHealth() << " health remaining." << endl;
            cout << "" << endl;
        }
    }

private:
    int calculateDamage(string ability, Character* target) {
        int damage = 0;
        int attackModifier = 0;
        // Fähigkeiten verursachen gleichen Schaden wie Knight und Barbarian
        if (ability == "Sword Slash") {
            damage = max(2 * attack - target->getDefense(), 0);
        } else if (ability == "Power Strike") {
            damage = max(3 * attack - target->getDefense(), 0);
        } else if (ability == "Whirlwind") {
            damage = max(attack - target->getDefense(), 0);
        } else if (ability == "Axe Chop") {
            damage = max(2 * attack - target->getDefense(), 0);
        } else if (ability == "Mighty Swing") {
            damage = max(3 * attack - target->getDefense(), 0);
        } else if (ability == "Cleave") {
            damage = max(2 * attack - target->getDefense(), 0);
        }

        return damage;
    }
};

class Stats {
public:
    void addWin(string name) {
        m_stats[name].first++;  // Gewinne++ für Namen in m_stats Map
    }

    void addLoss(string name) {
        m_stats[name].second++; // Verluste++ für Namen in m_stats Map
    }

    void printStats() {
        cout << "Stats:" << endl;
        for (auto& entry : m_stats) {
            cout << entry.first << ": " << entry.second.first << " wins, " << entry.second.second << " losses" << endl;
        }
    }

private:
    map<string, pair<int, int>> m_stats;
    // Map, die einem Namen als string einen Paar von Ganzzahlen zuordnet
};


void battle(Character* char1, Character* char2) {
    bool char1Turn = true;  // gibt an welcher Charakter dran ist
    while (char1->isAlive() && char2->isAlive()) {  // wenn beide noch Leben haben geht der Kampf weiter
        Character* attacker;
        Character* defender;
        if (char1Turn) {
            attacker = char1;
            defender = char2;
        } else {                // je  nachdem wer dran ist, wechselt Angreifer und Verteidiger
            attacker = char2;
            defender = char1;
        }
        cout << attacker->getName() << ", choose your action:" << endl;
        cout << "1. " << attacker->getAbilities()[0] << endl;
        cout << "2. " << attacker->getAbilities()[1] << endl;    //Fähigkeiten aus dem Vektor des jeweiligen Charakters
        cout << "3. " << attacker->getAbilities()[2] << endl;

        int choice;
        cin >> choice;
        // gewählte Angriff wird ausgeführt
        switch (choice) {
            case 1:
                attacker->ability1(defender);
                break;
            case 2:
                attacker->ability2(defender);
                break;
            case 3:
                attacker->ability3(defender);
                break;
            default:
                // falls Eingabe ungültig, nochmal auswählen
                cout << "Invalid choice. Please choose again." << endl;
                continue;
        }
        // wird der Verteidiger besiegt, wird Sieger angezeigt
        if (!defender->isAlive()) {
            cout << defender->getName() << " has been defeated!" << endl;
            cout << attacker->getName() << " wins the battle!" << endl;
            return;
        }
        // nächster Charakter ist an der Reihe anzugreifen
        char1Turn = !char1Turn;
    }
}

int main() {

    cout << "Welcome to Warriors Battle Game!" << endl;
    cout << "" << endl;
    Stats stats;    // Objekt für Gewinne und Verluste

    bool playAgain = true;  //bool um zu entscheiden ob nochmal gespielt werden soll
    while(playAgain) {
        // Introduction
        cout << "Player 1, please choose your warrior class:" << endl;
        cout << "1. Knight (HP: 150, ATK: 20, DEF: 20)" << endl;
        cout << "2. Barbarian (HP: 150, ATK: 25, DEF: 10)" << endl;
        cout << "3. Custom Warrior (HP: 150, ATK: 20, DEF: 15)" << endl;

        Character* player1; //Pointer für ausgewählte Warrior-Klasse
        int choice1;
        bool validChoice1 = false;  //überprüft auf gültige Eingaben
        while(!validChoice1) {
            cin >> choice1;

            // Erstellt Player 1 Charakter

            if (choice1 == 1) {
                player1 = new SwordWarrior("Player 1");
                validChoice1 = true;
            } else if (choice1 == 2) {
                player1 = new AxeWarrior("Player 1");
                validChoice1 = true;
            } else if (choice1 == 3) {
                vector<string> abilities;
                cout << "Please choose your 3 abilities (1. Sword Slash, 2. Power Strike, 3. Whirlwind, 4. Axe Chop, 5. Mighty Swing, 6. Cleave):" << endl;
                for (int i = 0; i < 3; i++) {
                    int abilityChoice;
                    cin >> abilityChoice;
                    switch (abilityChoice) {
                        case 1:
                            abilities.push_back("Sword Slash");
                        break;

                        case 2:
                            abilities.push_back("Power Strike");
                        break;

                        case 3:
                            abilities.push_back("Whirlwind");
                        break;

                        case 4:
                            abilities.push_back("Axe Chop");
                        break;

                        case 5:
                            abilities.push_back("Mighty Swing");
                        break;

                        case 6:
                            abilities.push_back("Cleave");
                        break;

                        default:
                            cout << "Invalid ability choice. Please choose again." << endl;
                        i--;
                        break;
                    }
                }
                player1 = new CustomWarrior("Player 1", abilities);
                validChoice1 = true;
            } else {
                cout << "Invalid choice. Please choose again." << endl;

            }
        }

        // Introduction for Player 2
        cout << "Player 2, please choose your warrior class:" << endl;
        cout << "1. Knight (HP: 150, ATK: 20, DEF: 20)" << endl;
        cout << "2. Barbarian (HP: 150, ATK: 25, DEF: 10)" << endl;
        cout << "3. Custom Warrior (HP: 150, ATK: 20, DEF: 15)" << endl;

        Character* player2;
        int choice2;
        bool validChoice2 = false;
        while(!validChoice2) {
            cin >> choice2;

            // Erstellt Player 2 Charakter

            if (choice2 == 1) {
                player2 = new SwordWarrior("Player 2");
                validChoice2 = true;
            } else if (choice2 == 2) {
                player2 = new AxeWarrior("Player 2");
                validChoice2 = true;
            } else if (choice2 == 3) {
                vector<string> abilities;
                cout << "Please choose your 3 abilities (choose from 1. Sword Slash, 2. Power Strike, 3. Whirlwind, 4. Axe Chop, 5. Mighty Swing, 6. Cleave):" << endl;
                for (int i = 0; i < 3; i++) {
                    int abilityChoice;
                    cin >> abilityChoice;
                    switch (abilityChoice) {
                        case 1:
                            abilities.push_back("Sword Slash");
                        break;

                        case 2:
                            abilities.push_back("Power Strike");
                        break;

                        case 3:
                            abilities.push_back("Whirlwind");
                        break;

                        case 4:
                            abilities.push_back("Axe Chop");
                        break;

                        case 5:
                            abilities.push_back("Mighty Swing");
                        break;

                        case 6:
                            abilities.push_back("Cleave");
                        break;

                        default:
                            cout << "Invalid ability choice. Please try again." << endl;
                        i--;
                        break;
                    }
                }
                player2 = new CustomWarrior("Player 2", abilities);
                validChoice2 = true;
            } else {
                cout << "Invalid choice. Please choose again." << endl;
            }
        }
        // Battle!
        battle(player1, player2);

        // Stats werden aktualisiert
        if (player1->isAlive()) {
            stats.addWin(player1->getName());
            stats.addLoss(player2->getName());
        } else {
            stats.addWin(player2->getName());
            stats.addLoss(player1->getName());
        }

        // Charaktere werden gelöscht falls nochmal gespielt wird
        delete player1;
        delete player2;

        // Spieler werden gefragt ob nochmal gespielt werden soll
        cout << "Do you want to play again? (y/n)" << endl;
        char playAgainChoice;
        cin >> playAgainChoice;
        playAgain = (playAgainChoice == 'y' || playAgainChoice == 'Y');
        cout << "" << endl;
    }
    // Stats werden angezeigt
    stats.printStats();
    return 0;
}
