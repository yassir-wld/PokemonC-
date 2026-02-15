#include <iostream>
using namespace std;

class Pokemon {
protected:
    string name;
    int hp;
    int attack;
    string type;

public:
    Pokemon(string n, int h, int a, string t)
        : name(n), hp(h), attack(a), type(t) {}

    virtual void attackPokemon(Pokemon &enemy) = 0; // pure virtual

    void takeDamage(int dmg) {
        hp -= dmg;
        if (hp < 0) hp = 0;
    }

    bool isAlive() { return hp > 0; }

    string getType() { return type; }

    string getName() { return name; }

    void showStatus() {
        cout << name << " (" << type << ") HP: " << hp << endl;
    }
};

class FirePokemon : public Pokemon {
public:
    FirePokemon(string n) : Pokemon(n, 100, 20, "Fire") {}

    void attackPokemon(Pokemon &enemy) override {
        int damage = attack;

        if (enemy.getType() == "Grass")
            damage += 10;      // strong
        if (enemy.getType() == "Water")
            damage -= 5;       // weak

        cout << name << " uses Fire Attack!\n";
        enemy.takeDamage(damage);
    }
};

class WaterPokemon : public Pokemon {
public:
    WaterPokemon(string n) : Pokemon(n, 110, 18, "Water") {}

    void attackPokemon(Pokemon &enemy) override {
        int damage = attack;

        if (enemy.getType() == "Fire")
            damage += 10;
        if (enemy.getType() == "Electric")
            damage -= 5;

        cout << name << " uses Water Attack!\n";
        enemy.takeDamage(damage);
    }
};

class GrassPokemon : public Pokemon {
public:
    GrassPokemon(string n) : Pokemon(n, 120, 15, "Grass") {}

    void attackPokemon(Pokemon &enemy) override {
        int damage = attack;

        if (enemy.getType() == "Water")
            damage += 10;
        if (enemy.getType() == "Fire")
            damage -= 5;

        cout << name << " uses Grass Attack!\n";
        enemy.takeDamage(damage);
    }
};

class ElectricPokemon : public Pokemon {
public:
    ElectricPokemon(string n) : Pokemon(n, 90, 25, "Electric") {}

    void attackPokemon(Pokemon &enemy) override {
        int damage = attack;

        if (enemy.getType() == "Water")
            damage += 10;
        if (enemy.getType() == "Grass")
            damage -= 5;

        cout << name << " uses Electric Attack!\n";
        enemy.takeDamage(damage);
    }
};

int main() {

    FirePokemon charmander("Charmander");
    WaterPokemon squirtle("Squirtle");

    Pokemon* p1 = &charmander;
    Pokemon* p2 = &squirtle;

    while (p1->isAlive() && p2->isAlive()) {

        p1->attackPokemon(*p2);
        p2->showStatus();

        if (!p2->isAlive()) break;

        p2->attackPokemon(*p1);
        p1->showStatus();

        cout << "------------------\n";
    }

    cout << "Winner: ";
    if (p1->isAlive())
        cout << p1->getName();
    else
        cout << p2->getName();

    return 0;
}