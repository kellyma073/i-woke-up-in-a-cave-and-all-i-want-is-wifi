#pragma once
#include "Item.h"
#include <string>
using namespace std;

class Potion : public Item {
public:
    Potion(const string& potionName, int healAmount) : name(potionName), healingAmount(healAmount) {}

    void use(Player& target) override;

private:
    string name;
    int healingAmount;
};