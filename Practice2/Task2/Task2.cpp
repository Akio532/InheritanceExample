// Task2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class computerGame
{
private:
    string name;
public:
    computerGame(const string _name) :name(_name) {}
    computerGame(const computerGame& obj) : name(obj.name) {}
    ~computerGame() {}

    string get_name() const
    {
        return name;
    }

    explicit virtual operator string()
    {
        return string(typeid(*this).name()) + ": (" + _print() + ")";
    }

protected:

    virtual string _print()
    {
        return "name of the game: " + name;
    }
};

class character : public computerGame
{
private:
    int x, y, hp, mp, maxHealth, maxMana;
public:
    character(const string _name, const int _maxHealth, const int _maxMana) : computerGame(_name), x(0), y(0), hp(_maxHealth), mp(_maxMana) {}
    character(const string _name, const int _maxHealth, const int _maxMana, const int _x, const int _y) : computerGame(_name), x(_x), y(_y), hp(_maxHealth), maxHealth(_maxHealth), mp(_maxMana), maxMana(_maxMana) {}
    character(const character& obj) : computerGame(obj), x(obj.x), y(obj.y), hp(obj.maxHealth), mp(obj.maxMana), maxHealth(obj.maxHealth), maxMana(obj.maxMana) {}

    int getx() const
    {
        return x;
    }

    int gety() const
    {
        return y;
    }

    int gethp() const
    {
        return hp;
    }

    int getmp() const
    {
        return mp;
    }




    virtual void move(int dx, int dy) = 0;
    virtual void take_damage(int damage) = 0;
    virtual void mana_use(int mana_cost) = 0;

protected:

    void _move(const int dx, const int dy)
    {
        x += dx;
        y += dy;
    }

    void _take_damage(const int damage)
    {
        hp = max(0, hp - damage);
    }

    void _mana_use(const int manaCost)
    {
        mp = max(0, mp - manaCost);
    }



    std::string _print() override
    {
        return computerGame::_print() + ", x: " + to_string(x) + ", y: " + to_string(y) +
            ", health: " + to_string(hp) + ", max health: " + to_string(maxHealth) +
            ", mana: " + to_string(mp) + ", max mana: " + to_string(maxMana);
    }
};
class artifacts : public computerGame
{
private:
    int damage;
public:

    artifacts(const string _name, const int _damage) : computerGame(_name), damage(_damage) {}
    artifacts(const artifacts& obj) : computerGame(obj), damage(obj.damage) {}
    ~artifacts() {}

    int get_damage() const
    {
        return damage;
    }

protected:
    string _print() override
    {
        return computerGame::_print() + ", damage: " + to_string(damage);
    }
};
class magic_ring : virtual public artifacts
{
private:
    int magicdamage;
public:
    magic_ring(const string _name, const int _damage, const int _magicdamage) : artifacts(_name, _damage), magicdamage(_magicdamage) {}
    magic_ring(const magic_ring& obj) : artifacts(obj), magicdamage(obj.magicdamage) {}
    ~magic_ring() {}

    int get_magicdamage() const
    {
        return magicdamage;
    }

protected:
    string _print() override
    {
        return artifacts::_print() + ", magicdamage: " + to_string(magicdamage);
    }
};


class minotaur : virtual public character
{
private:
    string specialty;
public:
    minotaur(const string _name, const string _specialty, const int _maxhealth, const int _maxmana) : character(_name, _maxhealth, _maxmana), specialty(_specialty) {}
    minotaur(const string _name, const string _specialty, const int _maxhealth, const int _maxmana, const int _x, const int _y) : character(_name, _maxhealth, _maxmana, _x, _y), specialty(_specialty) {}
    minotaur(const minotaur& obj) : character(obj), specialty(obj.specialty) {}
    ~minotaur() {}

    void move(const int dx, const int dy) override
    {
        character::_move(dx, dy);
        cout << "minotaur " + get_name() + " goes to (" + to_string(getx()) + ", " + to_string(gety()) + ").\n";
    }

    void take_damage(const int damage) override
    {
        character::_take_damage(damage);
        cout << "minotaur " + get_name() + " hit by " + to_string(damage) + " damage.\n";
    }

    void mana_use(const int mana_cost) override
    {
        character::_mana_use(mana_cost);
        cout << "minotaur " + get_name() + " used " + to_string(mana_cost) + " manapoints.\n";
    }

protected:
    string _print() override
    {
        return character::_print() + ", specialty: " + specialty;
    }
};

class wizard : virtual public character
{
private:
    string kindofmagic;
public:
    wizard(const string _name, const int _maxhealth, const int _maxmana, const string _kindofmagic) : character(_name, _maxhealth, _maxmana), kindofmagic(_kindofmagic) {}
    wizard(const string _name, const int _maxhealth, const int _maxmana, const int _x, const int _y) : character(_name, _maxhealth, _maxmana, _x, _y) {}
    wizard(const string _name, const int _maxhealth, const int _maxmana, const string _kindofmagic) : character(_name, _maxhealth, _maxmana), kindofmagic(_kindofmagic) {}
    wizard(const string _name, const int _maxhealth, const int _maxmana, const int _x, const int _y, const string _kindofmagic) : character(_name, _maxhealth, _maxmana, _x, _y), kindofmagic(_kindofmagic) {}
    wizard(const wizard& obj) : character(obj), kindofmagic(obj.kindofmagic) {}
    ~wizard() {}

    void move(const int dx, const int dy) override
    {
        character::_move(dx, dy);
        cout << "wizard " + get_name() + " goes to (" + to_string(getx()) + ", " + to_string(gety()) + ").\n";
    }

    void take_damage(const int damage) override
    {
        character::_take_damage(damage);
        cout << "wizard " + get_name() + " hit by " + to_string(damage) + " damage.\n";
    }

    void mana_use(const int mana_cost) override
    {
        character::_mana_use(mana_cost);
        cout << "wizard " + get_name() + " used " + to_string(mana_cost) + " manapoints.\n";
    }

protected:
    string _print() override
    {
        return character::_print() + ", kind of magic: " + kindofmagic;
    }
};

class elf : virtual public character
{
public:
    elf(const string _name, const int _maxhealth, const int _maxmana) : character(_name, _maxhealth, _maxmana) {}
    elf(const string _name, const int _maxhealth, const int _maxmana, const int _x, const int _y) : character(_name, _maxhealth, _maxmana, _x, _y) {}
    elf(const elf& obj) : character(obj) {}
    ~elf() {}

    void move(const int dx, const int dy) override
    {
        character::_move(dx, dy);
        cout << "elf " + get_name() + " moved to (" + to_string(getx()) + ", " + to_string(gety()) + ").\n";
    }

    void take_damage(const int damage) override
    {
        character::_take_damage(damage);
        cout << "elf " + get_name() + " hit by " + to_string(damage) + " damage.\n";
    }

    void mana_use(const int mana_cost) override
    {
        character::_mana_use(mana_cost);
        cout << "elf " + get_name() + " used " + to_string(mana_cost) + " manapoints.\n";
    }

    void voice(const string str)
    {
        cout << get_name() + " shout \"" + str + "\"\n";
    }

};

int main()
{
    minotaur new_minotaur("John", "Undefined", 600, 1000, 10, 10);
    cout << string(new_minotaur) << endl;
    new_minotaur.move(10, -5);
    new_minotaur.take_damage(30);
    wizard new_wizard("Marilyn", 50, 50, "words_of_wisdom");
    cout << string(new_wizard) << endl;
    new_wizard.move(1, 20);
    new_wizard.mana_use(150);
    new_wizard.take_damage(10);
    cout << endl;
    magic_ring new_ring("ring of the void", 30, 30);
    cout << string(new_ring) << endl;
    elf new_elf("Dimka", 200, 500, 100, 200);
    new_elf.voice("For the king!!!");
}