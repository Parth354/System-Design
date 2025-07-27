#include<iostream>
#include<string>
using namespace std;

class ICharacter {
    public:
        virtual string getAbilities() = 0;
        virtual ~ICharacter(){}
};

class Mario : public ICharacter {
    public:
        string getAbilities() override {
            return "Mario";
        }
};
class HeightUp : public ICharacter {
    ICharacter* character;
    public:
        HeightUp(ICharacter* character) : character(character) {}
        string getAbilities() override {
            return character->getAbilities() + " with Height Up";
        }
};
class FirePower : public ICharacter {
    ICharacter* character;
    public:
        FirePower(ICharacter* character) : character(character) {}
        string getAbilities() override {
            return character->getAbilities() + " with Fire Power";
        }
};
int main() {
    ICharacter* mario = new Mario();
    cout << "Character: " << mario->getAbilities() << endl;

    ICharacter* heightUpMario = new HeightUp(mario);
    cout << "Character: " << heightUpMario->getAbilities() << endl;

    ICharacter* firePowerMario = new FirePower(heightUpMario);
    cout << "Character: " << firePowerMario->getAbilities() << endl;

    delete mario;
    delete heightUpMario;
    delete firePowerMario;

    return 0;
}