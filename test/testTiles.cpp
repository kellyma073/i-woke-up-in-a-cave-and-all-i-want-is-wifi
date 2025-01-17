#include "gtest/gtest.h"
#include "../lib/tiles/EmptyTile.h"
#include "../lib/tiles/SpawnTile.h"
#include "../lib/tiles/WeaponTile.h"
#include "../lib/tiles/FightTile.h"
#include "../lib/Potion.h"
#include "../lib/Weapon.h"
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

// All TESTS WITHIN EMPTYTILE SUITE ARE BASED ON RNG SO THE TEST CHECKS IF OUTPUT IS 1 OF 3 RANDOM VALUES
TEST(EmptyTile, EmptyTileTest1) {
    EmptyTile emptyTile;

    stringstream buffer;
    streambuf* oldCoutBuffer = cout.rdbuf(buffer.rdbuf());
    
    emptyTile.print();

    cout.rdbuf(oldCoutBuffer);
    string result = buffer.str();

    vector<string> firstPartOptions = {
        "Ah yes! Exactly what I needed! A whole lot of nothing. \n \n",
        "Great! An empty room. I always wanted a personal space for my existential dread. \n \n",
        "Well, it could be worse, I could be wandering in a cave with no memory and no way out… \n ... \n ... \n wait"
    };

    string secondPart = "Time to move along! \n \n";

    bool matches = false;
    for (const auto& firstPart : firstPartOptions) {
        if (result == firstPart + secondPart) {
            matches = true;
            break;
        }
    }
    EXPECT_TRUE(matches) << "Output was: " << result;
}
TEST(EmptyTile, EmptyTileTest2) {
    EmptyTile emptyTile;

    stringstream buffer;
    streambuf* oldCoutBuffer = cout.rdbuf(buffer.rdbuf());
    
    emptyTile.print();

    cout.rdbuf(oldCoutBuffer);
    string result = buffer.str();

    vector<string> firstPartOptions = {
        "Ah yes! Exactly what I needed! A whole lot of nothing. \n \n",
        "Great! An empty room. I always wanted a personal space for my existential dread. \n \n",
        "Well, it could be worse, I could be wandering in a cave with no memory and no way out… \n ... \n ... \n wait"
    };

    string secondPart = "Time to move along! \n \n";

    bool matches = false;
    for (const auto& firstPart : firstPartOptions) {
        if (result == firstPart + secondPart) {
            matches = true;
            break;
        }
    }
    EXPECT_TRUE(matches) << "Output was: " << result;
}

TEST(SpawnTile, SpawnTileFirstVisit){
    SpawnTile spawnTile;
    stringstream buffer;
    streambuf* oldCoutBuffer = cout.rdbuf(buffer.rdbuf());
    
    spawnTile.print();

    cout.rdbuf(oldCoutBuffer);
    string result = buffer.str();

    vector<string> dialogue = {
        "You wake up in a cave and you crave the internet…",
        ""
    };

    bool matches = false;
    if (result == dialogue[0]) matches = true;
    
    EXPECT_TRUE(matches);
}
TEST(SpawnTile, SpawnTileNotFirstVisit){
    SpawnTile spawnTile;
    stringstream buffer;
    streambuf* oldCoutBuffer = cout.rdbuf(buffer.rdbuf());
    
    spawnTile.setVisitStateFalse();
    spawnTile.print();

    cout.rdbuf(oldCoutBuffer);
    string result = buffer.str();

    vector<string> dialogue = {
        "You wake up in a cave and you crave the internet…",
        ""
    };

    bool matches = false;
    if (result == dialogue[1]) matches = true;
    
    EXPECT_TRUE(matches);
}

TEST(Tiles, isVisitedTest1){
    SpawnTile spawnTile;
    spawnTile.setVisited();
    EXPECT_TRUE(spawnTile.isVisited());
}

TEST(Tiles, isVisitedTest2){
    SpawnTile spawnTile;
    EXPECT_TRUE(spawnTile.isVisited());
}

TEST(WeaponTile, WeaponTile){
    Weapon testWeapon("Chain Mail", 0, 2, 0, 0, 0, 0);
    WeaponTile tile(testWeapon);

    const vector<string>& dialogue = tile.getDialogue();

    ASSERT_EQ(dialogue.size(), 5); // Check there are 5 dialogue options
    EXPECT_EQ(tile.getDialogue()[1], "Wow, something useful for once. Maybe once I get out of here I'll open a(n) Chain Mail shop! \n\n");
    EXPECT_EQ(tile.getDialogue()[4], "It is a(n) Chain Mail! You pick up this heavy tool and think to yourself that it will be useful in the near future... \n\n");
}

TEST(FightTile, Initialization) {
    shared_ptr<Item> testReward = make_shared<Weapon>("Excalibur", 2, 2, 2, 2, 2, 0);
    FightTile fightTile("BasicBoss", testReward);

    EXPECT_EQ(fightTile.getBoss(), "BasicBoss");
    EXPECT_EQ(fightTile.getReward(), testReward);
}

TEST(FightTile, RewardIsNotNull) {
    shared_ptr<Item> testReward = make_shared<Potion>("Epic Potion", 40);
    FightTile fightTile("EliteBoss", testReward);

    EXPECT_NE(fightTile.getReward(), nullptr);
}

TEST(FightTile, DifferentBosses) {
    shared_ptr<Item> testReward = make_shared<Weapon>("Excalibur", 2, 2, 2, 2, 2, 0);
    FightTile fightTile1("Dragon", testReward);
    FightTile fightTile2("Goblin", testReward);

    EXPECT_EQ(fightTile1.getBoss(), "Dragon");
    EXPECT_EQ(fightTile2.getBoss(), "Goblin");
    EXPECT_NE(fightTile1.getBoss(), fightTile2.getBoss());
}


TEST(FightTile, EliteWinDialogueTest) {
    shared_ptr<Item> testReward = make_shared<Weapon>("Excalibur", 2, 2, 2, 2, 2, 0);
    FightTile fightTile("Dragon", testReward);

    const auto& dialogue = fightTile.getEliteWinDialogue();

    EXPECT_EQ(dialogue.size(), 3); 
    cout << dialogue[0];
    cout << dialogue[1];
    cout << dialogue[2];
}

TEST(FightTile, NormalWinDialogueTest) {
    shared_ptr<Item> testReward = make_shared<Weapon>("Excalibur", 2, 2, 2, 2, 2, 0);
    FightTile fightTile("Goblin", testReward);

    const auto& dialogue = fightTile.getNormalWinDialogue();

    EXPECT_EQ(dialogue.size(), 3); // Check that there are 3 dialogue options

    cout << dialogue[0];
    cout << dialogue[1];
    cout << dialogue[2];
}

TEST(FightTile, FinalBossDialogue){
    shared_ptr<Item> testReward = make_shared<Weapon>("Excalibur", 2, 2, 2, 2, 2, 0);
    FightTile fightTile("Goblin", testReward);
    const auto& dialogue = fightTile.getPhaseDialogueFinalBoss();

    EXPECT_EQ(dialogue.size(), 4);
    cout << dialogue[0];
    cout << dialogue[1];
    cout << dialogue[2];
    cout << dialogue[3];
   
}

TEST(FightTile, Ending){
    shared_ptr<Item> testReward = make_shared<Weapon>("Freedom", 0, 0, 0, 0, 0, 0);
    FightTile fightTile("Dragon", testReward);
    const string& dialogue = fightTile.getFinalBossWin();

    cout << dialogue;
}